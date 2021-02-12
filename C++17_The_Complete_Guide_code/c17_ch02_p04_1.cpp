#include <array>

template<typename T, auto N> std::array<T,N> arr{};

void printArr();

int main()
{
  arr<int,5>[0] = 17;
  arr<int,5>[3] = 42;
  arr<int,5u>[1] = 11;
  arr<int,5u>[3] = 33;
  printArr();
}
