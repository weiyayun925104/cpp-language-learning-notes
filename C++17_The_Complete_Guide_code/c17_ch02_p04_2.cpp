#include <iostream>
#include <array>

template<typename T, auto N> std::array<T,N> arr{};

void printArr();

void printArr()
{
  std::cout << "arr<int,5>:  ";
  for (const auto& elem : arr<int,5>) {
    std::cout << elem << ' ';
  }
  std::cout << "\narr<int,5u>: ";
  for (const auto& elem : arr<int,5u>) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}
