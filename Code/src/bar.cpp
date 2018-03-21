#include "bar.hpp"
#include <cmath>

bar::bar()
    :center(),width(0),height(0)
{}

bar::bar(const vec2 &center_param, int width_param, int height_param)
    :center(center_param),width(width_param),height(height_param)
{}

bool point_inside_bar_width(vec2 const& p,bar const& b, int const& r)
{
    if(p.x+r-b.center.x>=0 && p.x-r-b.center.x<=b.width)
        return true;
    return false;
}

bool point_inside_bar_height(vec2 const& p,bar const& b)
{
    if(p.y-b.center.y>=0 && p.y-b.center.y<=b.height)
        return true;
    return false;
}
