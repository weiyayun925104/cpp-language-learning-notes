#include "tracknew.hpp"
#include "tracknewtest.hpp"
#include <iostream>
#include <string>

int main()
{
    TrackNew::status();
    TrackNew::trace(true);
    std::string s = "an string value with 29 chars";
    TrackNew::status();
}
