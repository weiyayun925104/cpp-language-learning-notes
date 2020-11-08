#include <iostream>
#include "tv2.h"

int main()
{
    Tv tv;
    Remote remote;

    tv.onoff();
    std::cout << "Here are our original settings: " << std::endl;
    tv.settings();
    remote.settings();
    std::cout << std::endl;

    tv.toggleRemoteMode(remote);
    std::cout << "These are our new settings:" << std::endl;
    tv.settings();
    remote.settings();
    std::cout << std::endl;

    std::cout << "Done.\n";

    return 0;
}
