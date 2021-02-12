#include <iostream>
#include <vector>
#include <string>
#include <memory_resource>

class Tracker : public std::pmr::memory_resource
{
private:
    std::pmr::memory_resource *upstream;  // wrapped memory resource
    std::string prefix{};
public:
    // we wrap the passed or default resource:
    explicit Tracker(std::pmr::memory_resource *us
                     = std::pmr::get_default_resource())
        : upstream{us}
    {
    }
    explicit Tracker(std::string p,
                     std::pmr::memory_resource *us
                     = std::pmr::get_default_resource())
        : prefix{std::move(p)}, upstream{us}
    {
    }
private:
    void *do_allocate(size_t bytes, size_t alignment) override
    {
        std::cout << prefix << "allocate " << bytes << " Bytes\n";
        void *ret = upstream->allocate(bytes, alignment);
        return ret;
    }
    void do_deallocate(void *ptr, size_t bytes, size_t alignment) override
    {
        std::cout << prefix << "deallocate " << bytes << " Bytes\n";
        upstream->deallocate(ptr, bytes, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override
    {
        // same object?:
        if (this == &other) return true;
        // same type and prefix and equal upstream?:
        auto op = dynamic_cast<const Tracker *>(&other);
        return op != nullptr && op->prefix == prefix
               && upstream->is_equal(other);
    }
};

class PmrCustomer
{
private:
    std::pmr::string name;  // also used to store the allocator
public:
    using allocator_type = std::pmr::polymorphic_allocator<char>;

    // initializing constructor(s):
    PmrCustomer(std::pmr::string n, allocator_type alloc = {})
        : name{std::move(n), alloc}
    {
    }

    // copy/move with allocators:
    PmrCustomer(const PmrCustomer &c, allocator_type alloc)
        : name{c.name, alloc}
    {
    }
    PmrCustomer(PmrCustomer &&c, allocator_type alloc)
        : name{std::move(c.name), alloc}
    {
    }

    // setters/getters:
    void setName(std::pmr::string s)
    {
        name = std::move(s);
    }
    std::pmr::string getName() const
    {
        return name;
    }
    std::string getNameAsString() const
    {
        return std::string{name};
    }
};


int main()
{
    Tracker tracker;
    std::pmr::vector<PmrCustomer> coll(&tracker);
    coll.reserve(100);                     // allocates with tracker

    PmrCustomer c1{"Peter, Paul & Mary"};  // allocates with get_default_resource()
    coll.push_back(c1);                    // allocates with vector allocator (tracker)
    coll.push_back(std::move(c1));         // copies (allocators not interchangeable)

    for (const auto &cust : coll)
    {
        std::cout << cust.getName() << '\n';
    }
}
