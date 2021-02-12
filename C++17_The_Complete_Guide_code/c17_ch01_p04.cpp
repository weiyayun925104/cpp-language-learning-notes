#include <iostream>
#include <string>
#include <utility>

class Transcript { /* ... */ };

class Student
{
public:
    const char* name;
    Transcript score;
    std::string getName() const { return name; }
    const Transcript& getScore() const { return score; }
    template<std::size_t I>
    decltype(auto) get() const
    {
        if constexpr (I == 0)
            return getName();
        else if constexpr (I == 1)
            return getScore();
        else
            static_assert(I < 2);
    }
};

namespace std
{
    template<>
    struct tuple_size<Student> : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, Student>
    {
        using type = decltype(std::declval<Student>().getName());
    };

    template<>
    struct tuple_element<1, Student>
    {
        using type = decltype(std::declval<Student>().getScore());
    };
}

int main()
{
    std::cout << std::boolalpha;
    Student s{ "Jerry", {} };
    const auto& [name, score] = s;
    std::cout << name << std::endl;
    std::cout << (&score == &s.score) << std::endl;
}
