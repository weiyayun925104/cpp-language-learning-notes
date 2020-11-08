#include <iostream>
#include "stonewt3.h"

Stonewt::Stonewt(double lbs)
{
    stone = int(lbs) / Lbs_per_stn;
    pds_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
    dpounds = lbs;
    ipounds = int(lbs);
    setmode();
}

Stonewt::Stonewt(int stn, double lbs)
{
    stone = stn;
    pds_left = lbs;
    dpounds = stn * Lbs_per_stn + lbs;
    ipounds = int(stn * Lbs_per_stn + lbs);
    setmode();
}

Stonewt::Stonewt()
{
    stone = dpounds = ipounds = pds_left = 0;
    setmode();
}

Stonewt::~Stonewt()
{

}
void Stonewt::setmode()
{
    if (pds_left == 0)
    {
        mode = STONE;
    }
    else if (pds_left > int(pds_left))
    {
        mode = dPOUND;
    }
    else
    {
        mode = iPOUND;
    }
}
void Stonewt::setmode(int m)
{
    if (m == 0)
    {
        mode = STONE;
    }
    else if (m == 1)
    {
        mode = iPOUND;
    }
    else if (m == 2)
    {
        mode = dPOUND;
    }
    else
    {
        std::cout << "Invalid argument to the setmode() function, The mode is set to STONE.\n";
        mode = STONE;
    }
}
Stonewt operator+(const Stonewt &stn1, const Stonewt &stn2)
{
    return Stonewt (stn1.dpounds + stn2.dpounds);
}
Stonewt operator-(const Stonewt &stn1, const Stonewt &stn2)
{
    return Stonewt (stn1.dpounds - stn2.dpounds);
}
Stonewt operator*(double n, const Stonewt &stn)
{
    return Stonewt (stn.dpounds * n);
}
Stonewt operator*(const Stonewt &stn, double n)
{
    return Stonewt (stn.dpounds * n);
}
bool operator > (const Stonewt &stn1, const Stonewt &stn2)
{
    return stn1.dpounds > stn2.dpounds;
}
bool operator < (const Stonewt &stn1, const Stonewt &stn2)
{
    return stn1.dpounds < stn2.dpounds;
}
bool operator >= (const Stonewt &stn1, const Stonewt &stn2)
{
    return stn1.dpounds >= stn2.dpounds;
}
bool operator <= (const Stonewt &stn1, const Stonewt &stn2)
{
    return stn1.dpounds <= stn2.dpounds;
}
bool operator == (const Stonewt &stn1, const Stonewt &stn2)
{
    return stn1.dpounds == stn2.dpounds;
}
bool operator != (const Stonewt &stn1, const Stonewt &stn2)
{
    return stn1.dpounds != stn2.dpounds;
}
std::ostream &operator<<(std::ostream &os, const Stonewt &stn)
{
    if (stn.mode == Stonewt::STONE)
    {
        os << stn.stone << " stone, " << stn.pds_left << " pounds.";
    }
    else if (stn.mode == Stonewt::iPOUND)
    {
        os << stn.ipounds << " pounds.";
    }
    else
    {
        os << stn.dpounds << " pounds.";
    }
    return os;
}
