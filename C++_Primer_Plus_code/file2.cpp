#include <iostream>
#include <cmath>
#include "coordin.h"

polar rect_to_polar(rect xypos)
{
    polar answer;
    answer.distance = sqrt(xypos.x * xypos.x + xypos.y * xypos.y);
    answer.angle = atan2(xypos.y, xypos.x);
    return answer;
}
void show_polar(polar dapos)
{
    const double Rad_to_deg = 57.29577951;
    std::cout << "distance = " << dapos.distance << ", angle = " << dapos.angle *Rad_to_deg << " degrees\n";
}
