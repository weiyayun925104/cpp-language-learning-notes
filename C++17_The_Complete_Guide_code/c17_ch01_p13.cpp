#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <atomic>

template <typename T, typename... Args>
T create(Args&&... args)
{
  //...
  return T{std::forward<Args>(args)...};
}

int main()
{
  int i = create<int>(42);
  std::unique_ptr<int> up = create<std::unique_ptr<int>>(new int{42});
  std::atomic<int> ai = create<std::atomic<int>>(42);
  std::cout << i << ", " << *up << ", " << ai << std::endl;
}
