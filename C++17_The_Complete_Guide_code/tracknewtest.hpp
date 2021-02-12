#include "tracknew.hpp"
	
#include <string>

class MyClass
{
    static inline std::string name = "initial name with 26 chars";
};

inline MyClass myGlobalObj; // OK since C++17 even if included by multiple CPP files
