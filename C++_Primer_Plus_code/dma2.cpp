#include "dma2.h"

abcDMA::abcDMA(const char *l, int r)
{
    label = new char[std:: strlen(l) + 1];
    std::strcpy(label, l);
    rating = r;
}

abcDMA::abcDMA(const abcDMA &rs)
{
    label = new char[std:: strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = rs.rating;
}

void abcDMA::View() const
{
    std::cout << "Label: " << label << std::endl;
    std::cout << "Rating: " << rating << std::endl;
}

abcDMA::~abcDMA()
{
    delete[] label;
}

abcDMA   &abcDMA::operator = (const abcDMA &rs)
{
    if (this == &rs)
    {
        return *this;
    }
    else
    {
        delete[] label;
        label = new char[std:: strlen(rs.label) + 1];
        std::strcpy(label, rs.label);
        rating = rs.rating;
        return *this;
    }
}

std::ostream &operator << (std::ostream &os, const abcDMA &rs)
{
    os << "Label: " << rs.label << std::endl;
    os << "Rating: " << rs.rating << std::endl;
    return os;
}

baseDMA::baseDMA(const char *l, int r) : abcDMA(l, r) { }

baseDMA::baseDMA(const baseDMA &rs) : abcDMA(rs) { }

baseDMA::~baseDMA() { }

baseDMA &baseDMA::operator = (const baseDMA &rs)
{
    if (this == &rs)
    {
        return *this;
    }
    abcDMA::operator=(rs);
    return *this;
}
void baseDMA::View() const
{
    std::cout << "baseDMA object" << std::endl;
    std::cout << "Label: " << showLabel() << std::endl;
    std::cout << "Rating: " << showRating() << std::endl;
}
std::ostream &operator << (std::ostream &os, const baseDMA &rs)
{
    os << (const abcDMA &)rs;
    return os;
}

lacksDMA::lacksDMA(const char *c, const char *l, int r) : abcDMA(l, r)
{
    std::strncpy(color, c, COL_LEN - 1);
    color[COL_LEN - 1] = '\0';
}
lacksDMA::lacksDMA(const char *c, const abcDMA &rs) : abcDMA(rs)
{
    std::strncpy(color, c, COL_LEN - 1);
    color[COL_LEN - 1] = '\0';
}

void lacksDMA::View() const
{
    std::cout << "lacksDMA object" << std::endl;
    abcDMA::View();
    std::cout << "Color: " << color << std::endl;
}

std::ostream &operator << (std::ostream &os, const lacksDMA &Is)
{
    os << (const abcDMA &) Is;
    os << "Color: " << Is.color << std::endl;
    return os;
}
hasDMA::hasDMA(const char *s, const char *l, int r) : abcDMA(l, r)
{
    style = new char[std::strlen(s) + 1];
    std::strcpy(style, s);
}
hasDMA::hasDMA(const char *s, const abcDMA &rs) : abcDMA(rs)
{
    style = new char[std::strlen(s) + 1];
    std::strcpy(style, s);
}
hasDMA::hasDMA(const hasDMA &hs) : abcDMA(hs)
{
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);
}

hasDMA::~hasDMA()
{
    delete[] style;
}

hasDMA &hasDMA::operator = (const hasDMA &hs)
{
    if (this == &hs)
    {
        return *this;
    }
    else
    {
        abcDMA::operator=(hs);
        delete[] style;
        style = new char[std::strlen(hs.style) + 1];
        std::strcpy(style, hs.style);
        return *this;
    }
}

void hasDMA::View() const
{
    std::cout << "hasDMA object" << std::endl;
    abcDMA::View();
    std::cout << "Style: " << style << std::endl;
}

std::ostream &operator << (std::ostream &os, const hasDMA &hs)
{
    os << (const abcDMA &) hs;
    os << "Style: " << hs.style << std::endl;
    return os;
}
