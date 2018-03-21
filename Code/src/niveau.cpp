#include "niveau.hpp"
#include <iostream>

niveau::niveau() {}

niveau::niveau(int lvl) :level(lvl)
{
    int width=0;
    int height=0;
    float position;

    if(level==1)
    {
        //On crée le niveau 1 en définissant l'ensemble des briques ainsi que leurs largeur et hauteur
        width=50;
        height=20;

        for(int j=0; j<=14; j++)
        {
            position=static_cast<float>(j);
            briques.push_back(bar({50*position,40},width,height));
            collisionBriques.push_back(level);
        }
        for(int j=0; j<=14; j++)
        {
            position=static_cast<float>(j);
            briques.push_back(bar({50*position,65},width,height));
            collisionBriques.push_back(level);
        }
        for(int j=0; j<=14; j++)
        {
            position=static_cast<float>(j);
            briques.push_back(bar({50*position,90},width,height));
            collisionBriques.push_back(level);
        }
    }
    if(level==2)
    {
        //On crée le niveau 2
        width=60;
        height=30;

        briques.push_back(bar({350,10},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({315,45},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({385,45},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({280,80},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({350,80},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({420,80},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({315,115},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({385,115},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({350,150},width,height));
        collisionBriques.push_back(level);
        for(int j=0; j<=9; j++)
        {
            position=static_cast<float>(j);
            briques.push_back(bar({20+70*position,200},width,height));
            collisionBriques.push_back(level);
        }
        briques.push_back(bar({0,10},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({70,10},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({0,45},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({640,10},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({570,10},width,height));
        collisionBriques.push_back(level);
        briques.push_back(bar({640,45},width,height));
        collisionBriques.push_back(level);
    }

    if(level==3)
    {
        //le niveau 3 correspond en quelque sorte a un niveau bonus, c'est le seul a comporter deux bonus
        width=60;
        height=30;
        briques.push_back(bar({30,310},width,height));
        collisionBriques.push_back(3);
        briques.push_back(bar({110,310},width,height));
        collisionBriques.push_back(3);
        briques.push_back(bar({190,310},width,height));
        collisionBriques.push_back(3);
        briques.push_back(bar({270,310},width,height));
        collisionBriques.push_back(3);
        briques.push_back(bar({350,310},width,height));
        collisionBriques.push_back(3);
        briques.push_back(bar({430,310},width,height));
        collisionBriques.push_back(3);
        briques.push_back(bar({510,310},width,height));
        collisionBriques.push_back(3);
        briques.push_back(bar({590,310},width,height));
        collisionBriques.push_back(3);
        briques.push_back(bar({670,310},width,height));
        collisionBriques.push_back(3);

        width=70;
        height=20;
        briques.push_back(bar({130,100},width,height));
        collisionBriques.push_back(2);
        briques.push_back(bar({130,170},width,height));
        collisionBriques.push_back(2);
        width=20;
        height=70;
        briques.push_back(bar({105,105},width,height));
        collisionBriques.push_back(2);
        briques.push_back(bar({205,105},width,height));
        collisionBriques.push_back(2);

        width=70;
        height=20;
        briques.push_back(bar({550,100},width,height));
        collisionBriques.push_back(2);
        briques.push_back(bar({550,170},width,height));
        collisionBriques.push_back(2);
        width=20;
        height=70;
        briques.push_back(bar({525,105},width,height));
        collisionBriques.push_back(2);
        briques.push_back(bar({625,105},width,height));
        collisionBriques.push_back(2);

        width=50;
        height=50;
        briques.push_back(bar({350,145},width,height));
        collisionBriques.push_back(1);
        briques.push_back(bar({320,215},width,height));
        collisionBriques.push_back(1);
        briques.push_back(bar({380,215},width,height));
        collisionBriques.push_back(1);

        width=80;
        height=10;
        briques.push_back(bar({545,80},width,height));
        collisionBriques.push_back(1);
        briques.push_back(bar({125,80},width,height));
        collisionBriques.push_back(1);

        bonus.push_back(circle({165,145},12.0f));
        collisionBonus.push_back(1);

        bonus.push_back(circle({585,145},12.0f));
        collisionBonus.push_back(1);
    }

}

bool niveau::checkVictory()
{
    int nbr_briques_total=0;
    for(int brique_restante : collisionBriques)
        nbr_briques_total+=brique_restante;
    if (nbr_briques_total==0)
        return true;
    else
        return false;
}
