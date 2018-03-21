#pragma once
#ifndef NIVEAU_H
#define NIVEAU_H

#include "bar.hpp"
#include "vec2.hpp"
#include <vector>
#include "circle.hpp"

/** cette structure sert a construire les niveaux*/
struct niveau
{
    niveau();
    niveau(int lvl);

    /** Renvoi true s'il n'y a plus de briques sur le terrain de jeu*/
    bool checkVictory();

    /** Tableau comportant les coordonnées 2D de chaque brique */
    std::vector<bar> briques;
    /** Tableau d'entier permettant d'assurer s'il y a eu ou non collision de la balle avec une brique */
    std::vector<int> collisionBriques;
    /** Niveau en cours*/
    int level;
    /** Tableau contenant les bonus du niveau*/
    std::vector<circle> bonus;
    /** Tableau de booleen permettant d'assurer s'il y a eu collision ou non avec un bonus */
    /** Le chiffre indique de plus le type de bonus dont il s'agit */
    std::vector<int> collisionBonus;
};

#endif // NIVEAU_H
