#include <iostream>
#include <string>
#include <thread>

struct MyData
{
    inline static std::string gName = "global"; // unique in program
    inline static thread_local std::string tName = "tls"; // unique per thread
    std::string lName = "local"; // for each object

    void print(const std::string &msg) const
    {
        std::cout << msg << '\n';
        std::cout << "- gName: " << gName << '\n';
        std::cout << "- tName: " << tName << '\n';
        std::cout << "- lName: " << lName << '\n';
    }
};

inline thread_local MyData myThreadData; // one object per thread

void foo();

int main()
{
    myThreadData.print("main() begin:");
    myThreadData.gName = "thread1 name";
    myThreadData.tName = "thread1 name";
    myThreadData.lName = "thread1 name";
    myThreadData.print("main() later:");
    std::thread t(foo);
    t.join();
    myThreadData.print("main() end:");
}
