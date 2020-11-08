#include <iostream>
#include "tv2.h"

bool Tv::volup()
{
    if (volume < MaxVal)
    {
        volume++;
        return true;
    }
    else
    {
        return false;
    }
}

bool Tv::voldown()
{
    if (volume > MinVal)
    {
        volume--;
        return true;
    }
    else
    {
        return false;
    }
}

void Tv::chanup()
{
    if (channel < maxchannel)
    {
        channel++;
    }
    else
    {
        channel = 1;
    }
}

void Tv::chandown()
{
    if (channel > 1)
    {
        channel--;
    }
    else
    {
        channel = maxchannel;
    }
}

void Tv::settings() const
{
    std::cout << "TV is " << (state == Off ? "Off" : "On") << std::endl;

    if (state == On)
    {
        std::cout << "Volume setting = " << volume << std::endl;
        std::cout << "Channel setting = " << channel << std::endl;
        std::cout << "Mode = " << (mode == Antenna ? "antenna" : "cable") << std::endl;
        std::cout << "Input = " << (input == TV ? "TV" : "DVD") << std::endl;
    }
}

void Tv::toggleRemoteMode(Remote &r)
{
    if (On == state && r.mode_i == Remote::Interactive)
    {
        r.mode_i = Remote::Normal;
    }
    else if (On == state && r.mode_i == Remote::Normal)
    {
        r.mode_i = Remote::Interactive;
    }
    else
    {
        return;
    }
}
void Remote::settings() const
{
    std::cout << "Remote is set to the " << (mode_d == Tv::TV ? "TV" : "VCR");
    std::cout << " and is in ";
    std::cout << (mode_i == Normal ? "Normal" : "Interactive") << " mode" << std::endl;
}
