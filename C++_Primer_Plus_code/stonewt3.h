#pragma once
#ifndef STONEWT3_H_
#define STONEWT3_H_

class Stonewt
{
private:
    enum { Lbs_per_stn = 14 };
    enum Mode { STONE, iPOUND, dPOUND };
    int stone;
    double pds_left;
    double dpounds;
    int ipounds;
    Mode mode;
    void setmode();
public:
    Stonewt(double lbs);
    Stonewt(int stn, double lbs);
    Stonewt();
    ~Stonewt();
    void setmode(int m);
    friend Stonewt operator+(const Stonewt &stn1, const Stonewt &stn2);
    friend Stonewt operator-(const Stonewt &stn1, const Stonewt &stn2);
    friend Stonewt operator*(double n, const Stonewt &stn);
    friend Stonewt operator*(const Stonewt &stn, double n);
    friend bool operator > (const Stonewt &stn1, const Stonewt &stn2);
    friend bool operator < (const Stonewt &stn1, const Stonewt &stn2);
    friend bool operator >= (const Stonewt &stn1, const Stonewt &stn2);
    friend bool operator <= (const Stonewt &stn1, const Stonewt &stn2);
    friend bool operator == (const Stonewt &stn1, const Stonewt &stn2);
    friend bool operator != (const Stonewt &stn1, const Stonewt &stn2);
    friend std::ostream &operator<<(std::ostream &os, const Stonewt &stn);
};

#endif
