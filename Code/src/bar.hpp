#pragma once

#include <iostream>

#include "vec2.hpp"

/** A structure containing parameter of a geometric rectangle */
struct bar
{
    /** center coordinate */
    vec2 center;
    /** width and height */
     int width; int height;

    /** Constructor bar (0,0) */
    bar();
    /** Constructor bar ({x,y},R) */
    bar(vec2 const& center_param,int width_param, int height_param);

};

/** Verifie si un point est dans la largeur de la barre/brique ou non ;
 * le parametre r permet d'ajouter une tolerence pour la collision avec
 * la barre, et evite de gerer les collisions avec les cotes de celles-ci*/
bool point_inside_bar_width(vec2 const& p, bar const& b, const int &r);

/** Verifie si un point est dans la longueur de la barre/brique ou non */
bool point_inside_bar_height(vec2 const& p,bar const& b);


