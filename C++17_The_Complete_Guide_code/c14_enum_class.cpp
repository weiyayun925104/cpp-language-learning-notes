#include <iostream>
#include <type_traits>
 
enum e1 {};
enum class e2 {};
enum class e3: unsigned {};
enum class e4: int {};
 
int main() {
 
  constexpr bool e1_t = std::is_same_v< std::underlying_type_t<e1>, int >;
  constexpr bool e2_t = std::is_same_v< std::underlying_type_t<e2>, int >;
  constexpr bool e3_t = std::is_same_v< std::underlying_type_t<e3>, int >;
  constexpr bool e4_t = std::is_same_v< std::underlying_type_t<e4>, int >;
 
  std::cout
    << "underlying type for 'e1' is " << (e1_t ? "int" : "non-int") << '\n'
    << "underlying type for 'e2' is " << (e2_t ? "int" : "non-int") << '\n'
    << "underlying type for 'e3' is " << (e3_t ? "int" : "non-int") << '\n'
    << "underlying type for 'e4' is " << (e4_t ? "int" : "non-int") << '\n'
    ;
}
