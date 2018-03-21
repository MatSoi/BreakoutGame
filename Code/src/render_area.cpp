
#include "render_area.hpp"
#include <QtGui>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

#include <iostream>
#include <cassert>

render_area::render_area(QWidget *parent)
    :QWidget(parent),
      circ({340,490},10),
      speed(0.0f,0.0f),
      dt(1/3.0f),
      timer(),
      time(),
      bar_p({300,500},80,10),
      niveau_p(1),
      first_click(false),
      victory(new QImage("victory.jpg")),
      game_over(new QImage("gameover")),
      loose(false),
      clavier(Qt::Key_0),
      touche(false),
      progress_bar(nullptr),
      nbr_collisions(0)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    //timer calling the function update_timer periodicaly
    connect(&timer, SIGNAL(timeout()), this, SLOT(update_timer()));
    setMouseTracking(true); //permet de bouger la barre sans avoir à cliquer

    timer.start(15);        //rafraichissement du jeu tous les 15ms (environ 60 FPS)
}

render_area::~render_area()
{}

//Fonction de changement du niveau afin de conserver le niveau en attribut private
void render_area::set_level(int value)
{
    niveau_p=niveau(value);  //on le construction du niveau pour le nouveau niveau selectionne
    first_click=false;       //remise a false des bolleen de debut et de fin de jeu
    loose=false;
    bar_p.width=80;          //utile pour le niveau 3 (mais on le fait toujours pour eviter un if), permet de remettre la barre a sa taille de depart
    nbr_collisions=0;        //remise a zero du nombre de collision
    init_progess_bar();      //reinitialisation de la barre de progression obligatoire au changement de niveau
}

//Fonction pour recommencer un niveau
void render_area::restart_level()
{
    niveau_p=niveau(niveau_p.level); //de meme que pour la selection d'un nouveau niveau
    first_click=false;
    loose=false;
    bar_p.width=80;
    nbr_collisions=0;
    init_progess_bar();
}

void render_area::paintEvent(QPaintEvent*)
{  
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen;
    pen.setWidth(1.0);
    pen.setColor(Qt::gray);
    painter.setPen(pen);

    QBrush brush = painter.brush();
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    //the actual drawing of the circle
    if(!first_click)
        circ.center=bar_p.center+vec2(40,-10);  //la balle reste collee a la barre tant que le joueur n'a pas clique

    vec2 const& p=circ.center;
    float const r=circ.radius;
    painter.drawEllipse(p.x-r,p.y-r,2*r,2*r);

    //Affichage des bonus
    pen.setColor(Qt::black);
    painter.setPen(pen);
    brush.setColor(Qt::blue);
    painter.setBrush(brush);
    int i=0; //indice pour l'acces au std::vector collisionBonus
    for(auto bonus : niveau_p.bonus) //boucle for each compacte
    {
        if(niveau_p.collisionBonus[i]!=0) //on dessine les deux bonus du niveau 3
            painter.drawEllipse(bonus.center.x-bonus.radius,bonus.center.y-bonus.radius,2*bonus.radius,2*bonus.radius);
        i++; //incrementation de l'indice. On aurait pu directement faire une boucle sur h, mais la for each est compacte (nottament pour l'appel des attributs de bonus) et cela permet de s'entrainer
    }

    //Dessine la bar
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    brush.setColor(Qt::blue);
    painter.setBrush(brush);

    painter.drawRect(bar_p.center.x,bar_p.center.y,bar_p.width,bar_p.height);

    pen.setColor(Qt::darkRed);
    painter.setPen(pen);

    i=0;
    //Boucle pour dessiner chaque bricks
    for(bar brique : niveau_p.briques)  //meme logique d'utilisation de la boucle for each
    {
        if(niveau_p.collisionBriques[i]==3) //les briques changent de couleur suivant le nombre de coup qu'elle subisse
        {
            brush.setColor(Qt::darkRed);
            painter.setBrush(brush);
            painter.drawRect(brique.center.x,brique.center.y, brique.width, brique.height);
        }
        if(niveau_p.collisionBriques[i]==2)
        {
            brush.setColor(Qt::red);
            painter.setBrush(brush);
            painter.drawRect(brique.center.x,brique.center.y, brique.width, brique.height);
        }
        if(niveau_p.collisionBriques[i]==1)
        {
            brush.setColor(Qt::yellow);
            painter.setBrush(brush);
            painter.drawRect(brique.center.x,brique.center.y, brique.width, brique.height);
        }
        i++;
    }

    if(niveau_p.checkVictory())
    {
        pen.setColor(Qt::white);
        painter.setPen(pen);
        brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(0,0,width(),height()); //on dessine un fond blanc pour cacher le jeu
        painter.drawImage(width()/2-victory->width()/2,0,*victory);
    }
    else if(loose)
    {
        pen.setColor(Qt::white);
        painter.setPen(pen);
        brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(0,0,width(),height());
        painter.drawImage(width()/2-game_over->width()/2,height()/2-game_over->height()/2,*game_over);
    }
}

void render_area::mousePressEvent(QMouseEvent *event)
{
    int anti_warning=0; //cette variable sert a eviter un declenchement de variable a cause de event (event est necessaire sinon la fonction soit n'herite pas, soit ne fait rien)
    anti_warning+=event->x();
    if(!first_click)
    {
        speed=vec2(0,-15); //lancement de la balle
        first_click=true;
    }
}

void render_area::mouseMoveEvent(QMouseEvent *event)
{
    vec2 const click=vec2(event->x(),event->y());

    //la barre se déplace en suivant la souris
    bar_p.center.x=click.x-bar_p.width/2;
    repaint();
}

void render_area::keyPressEvent(QKeyEvent *event)
{
    clavier=event->key();
    touche=true;

    switch (clavier) {
    case Qt::Key_R:
        restart_level();
        break;
    case Qt::Key_1:
        set_level(1);
        break;
    case Qt::Key_2:
        set_level(2);
        break;
    case Qt::Key_3:
        set_level(3);
        break;
    default:
        break;
    }

}

void render_area::keyReleaseEvent(QKeyEvent *event)
{
    clavier=event->key(); //utile uniquement pour eviter le warning
    touche=false;
}

void render_area::update_timer()
{
    //called periodically
    numerical_integration();
    bar_clavier_mvt();
    repaint();
}

void render_area::numerical_integration()
{
    //numerical integration using Forward Euler method
    vec2& p=circ.center;
    p      = p+dt*speed;          //integrate position

    //collision handling (set new position, and return a new speed value)
    speed=collision_handling(p);
}

void render_area::bar_clavier_mvt()
{
    if(touche)                  //tant que l'on n'a pas relache la touche, la barre se deplace ;
        switch (clavier) {      //cette façon de faire permet d'eviter que la barre debute un mouvement, s'arrete, puis reparte
        case Qt::Key_Right:
            bar_p.center.x+=15;
            break;
        case Qt::Key_Left:
            bar_p.center.x-=15;
            break;
        case Qt::Key_Space:
            if(!first_click)
            {
                speed=vec2(0,-15);
                first_click=true;
            }
            break;
        default:
            break;
        }
}

vec2 render_area::collision_handling(vec2& p)
{
    vec2 new_speed=speed;

    //size of the window
    float const w=width();
    float const h=height();

    //radius of the sphere
    float const r=circ.radius;

    //collision with the left wall
    if(p.x-r<0)
    {
        p.x=r;
        new_speed.x *= -1;
    }
    //collision with the right wall
    if(p.x+r>w)
    {
        p.x=w-r;
        new_speed.x *= -1;
    }
    //collision with the top wall
    if(p.y-r<0)
    {
        p.y=r;
        new_speed.y *= -1;
    }
    if(first_click)
        if(p.y+r>h)
            loose=true;

    //GESTION DE LA COLLISION DE LA BALLE AVEC LA BARRE
    if(point_inside_bar_width(p,bar_p,r))
    {
        if(p.y+r>bar_p.center.y && p.y-r<bar_p.center.y) //collision avec le haut de la barre
        {
            p.y=bar_p.center.y-r;
            new_speed.y *= -1;

            if(p.x<bar_p.center.x+bar_p.width/2-10 && new_speed.x>=0) //frappe du cote gauche de la barre fait partir la balle a gauche
                new_speed.x=-10;
            else if(p.x>bar_p.center.x+bar_p.width/2+10 && new_speed.x<=0) //frappe du cote droit de la barre fait partir la balle a droite
                new_speed.x=10;
            else if(new_speed.x!=0)                               //collision avec le centre de la barre ralentit la vitesse en x
            {
                if(new_speed.x>0)
                    new_speed.x-=5;
                if(new_speed.x<0)
                    new_speed.x+=5;
            }
        }
    }

    //GESTION DE LA COLLISION DE LA BALLE AVEC UN BONUS
    for(unsigned int j=0;j<niveau_p.bonus.size();j++)
    {
        if(collision_circle(circ,niveau_p.bonus[j])==true)
        {
            if(niveau_p.collisionBonus[j]==1)
                bar_p.width*=1.5;               //les deux bonus aggrandissent la barre dans le niveau 3
            niveau_p.collisionBonus[j]=0;
        }
    }

    int i=0;
    //GESTION DE LA COLLISION DE LA BALLE AVEC CHAQUE BRIQUE
    for(bar brique : niveau_p.briques)
    {
        if(point_inside_bar_width(p,brique,0) && niveau_p.collisionBriques[i]>0)
        {
            if(p.y+r>brique.center.y && p.y-r<brique.center.y) //collision avec le haut de la brick
            {
                p.y=brique.center.y-r;
                new_speed.y *= -1;
                niveau_p.collisionBriques[i]-=1;
                nbr_collisions+=1;
            }
            if(p.y-r<brique.center.y+brique.height && p.y+r>brique.center.y+brique.height) //collision avec le bas de la brick
            {
                p.y=brique.center.y+brique.height+r;
                new_speed.y *= -1;
                niveau_p.collisionBriques[i]-=1;
                nbr_collisions+=1;
            }
        }
        else if(point_inside_bar_height(p,brique) && niveau_p.collisionBriques[i]>0)
        {
            if(p.x+r>brique.center.x && p.x-r<brique.center.x) //collision avec la gauche de la brick
            {
                p.x=brique.center.x-r;
                new_speed.x *= -1;
                niveau_p.collisionBriques[i]-=1;
                nbr_collisions+=1;
            }
            else if(p.x-r<brique.center.x+brique.width && p.x+r>brique.center.x+brique.width) //collision avec la droite de la brick
            {
                p.x=brique.center.x+brique.width+r;
                new_speed.x *= -1;
                niveau_p.collisionBriques[i]-=1;
                nbr_collisions+=1;
            }
        }
        else if (point_inside_bar_width(p,brique,r) && niveau_p.collisionBriques[i]>0)
        {
            if(p.y+r>brique.center.y && p.y-r<brique.center.y) //collision avec le coin haut de la brick
            {
                p.y=brique.center.y-r;
                new_speed.y=-std::abs(new_speed.y); //touché un coin haut fait monter la balle

                //tapé dans les coins des briques fait partir sur les cotes
                if(p.x-brique.center.x<=0)  //balle sur le coin gauche
                    new_speed.x = -10;
                else                        //balle sur le coin droit
                    new_speed.x=10;

                niveau_p.collisionBriques[i]-=1;
                nbr_collisions+=1;
            }
            if(p.y-r<brique.center.y+brique.height && p.y+r>brique.center.y+brique.height) //collision avec le coin bas de la brick
            {
                p.y=brique.center.y+brique.height+r;
                new_speed.y=std::abs(new_speed.y); //touché un coin bas fait descendre la balle
                if(p.x-brique.center.x<=0)  //balle sur le coin gauche
                    new_speed.x = -10;
                else                        //balle sur le coin droit
                    new_speed.x=10;
                niveau_p.collisionBriques[i]-=1;
                nbr_collisions+=1;
            }
        }
        i++;
    }
    progress_bar->setValue(nbr_collisions);
    return new_speed;
}

void render_area::init_progess_bar()
{
    int max=0;
    for (int nbr_colli : niveau_p.collisionBriques)
        max+=nbr_colli;
    progress_bar->setMinimum(0);
    progress_bar->setMaximum(max);
    progress_bar->setValue(0);
}

void render_area::setup_progress_bar(QProgressBar *progress_bar_window)
{
    progress_bar=progress_bar_window;
    init_progess_bar();
}
