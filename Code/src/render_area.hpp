#pragma once

#ifndef RENDER_AREA_HPP
#define RENDER_AREA_HPP

#include "circle.hpp"
#include "bar.hpp"
#include "niveau.hpp"

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <list>
#include <QProgressBar>

/** Cette classe herite de la classe QWidget et correspond a la zone de jeu*/
class render_area : public QWidget
{
    Q_OBJECT
public:

    render_area(QWidget *parent = 0);
    ~render_area();

    /** Change de niveau */
    void set_level(int value);
    /** Recommence le niveau */
    void restart_level();
    /** Fonction inspiré de setup_bounce_number qui utilise un jeu de pointeur pour transférer le
     *  QProgressBar de window dans render_area en transférant la zone mémoire */
    void setup_progress_bar(QProgressBar* progress_bar_window);

protected:
    /** Actual drawing function */
    void paintEvent(QPaintEvent *event);
    /** Function called when the mouse is pressed */
    void mousePressEvent(QMouseEvent *event);
    /** Function called when the mouse is moved */
    void mouseMoveEvent(QMouseEvent *event);
    /** Fonction d'ecoute pour l'appui des touches du clavier */
    void keyPressEvent(QKeyEvent *event);
    /** Fonction d'ecoute pour le relachement des touches du clavier */
    void keyReleaseEvent(QKeyEvent *event);

private slots:

    /** Function called periodically at constant time interval by a timer */
    void update_timer();

private: //functions

    /** Deal with collision */
    vec2 collision_handling(vec2& p);

    /** Move forward in time */
    void numerical_integration();

    /** Deplace la barre et lance le jeu au clavier*/
    void bar_clavier_mvt();

    /** Initialise la barre de progression (progress_bar) (maximum et minimum)*/
    void init_progess_bar();

private: //attributes

    /** The circle */
    circle circ;
    /** The speed of the circle */
    vec2 speed;
    /** The time integration step */
    float dt;

    /** Timer for periodic time iteration */
    QTimer timer;
    /** Time accessor */
    QTime time;

    /** The bar */
    bar bar_p;
    /** The level (Bricks) */
    niveau niveau_p;

    /** Click pour lancer le debut d'un niveau */
    bool first_click;

    /** Image de victoire*/
    QImage* victory;

    /** Image de game over*/
    QImage* game_over;
    /** Booleen indiquant un game over*/
    bool loose;

    /** Touche du clavier*/
    long int clavier;
    /** Booleen mis a true lorsque l'on appuie sur une touche du clavier, remis a false lorsque l'on relache*/
    bool touche;

    /** Pointeur sur la QProgressBar de la window*/
    QProgressBar* progress_bar;
    /** Nombre de collisions : correspond à la valeur que l'on met dans la progress_bar*/
    int nbr_collisions;
};

#endif
