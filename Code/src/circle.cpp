
#include "circle.hpp"

#include <cmath>

circle::circle()
    :center(),radius(0.0f)
{}

circle::circle(vec2 const& center_param,float const radius_center)
    :center(center_param),radius(radius_center)
{}

bool point_inside_circle(vec2 const& p,circle const& c)
{
    vec2 const& u=p-c.center;

    float const n=norm(u);
    float const r=c.radius;

    if(n<=r)
        return true;
    else
        return false;
}

bool collision_circle(circle const& c1,circle const& c2)
{
    vec2 const& u=c1.center-c2.center;

    float const n=norm(u);
    float const r1=c1.radius;
    float const r2=c2.radius;

    if(n<=r1+r2)
        return true;
    else
        return false;
}
