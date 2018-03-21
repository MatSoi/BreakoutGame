#include "window.hpp"
#include "render_area.hpp"
#include "ui_mainwindow.h"

#include <iostream>

window::window(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow),render(new render_area)
{
    ui->setupUi(this);
    ui->layout_scene->addWidget(render);
    render->setFocusPolicy(Qt::StrongFocus);        //Les deux lignes servent a declencher l'ecoute
    render->setFocus();                             //du clavier pour le QWidget render
    render->setup_progress_bar(ui->progressBar);    //Permet de manipuler la progressBar dans render

    //Connection with signals
    connect(ui->quit,SIGNAL(clicked()),this,SLOT(action_quit()));   //connexion du bouton quitter avec l'action de fermer la fenetre
    connect(ui->level_select,SIGNAL(currentIndexChanged(int)),this,SLOT(change_level(int))); //connexion du menu deroulant avec le changement de niveau
    connect(ui->restart_level,SIGNAL(clicked()),this,SLOT(restart()));  //connexion du bouton restart avec le recommencement du niveau
}


window::~window()
{}

//Gestion du changement de niveau
void window::change_level(int value)
{
    render->set_level(value+1);                 //l'indexation du menu deroulant est decale par rapport a la numerotation des niveaux
    render->setFocusPolicy(Qt::StrongFocus);    //le fait de cliquer sur un bouton desactive l'ecoute du clavier pour render
    render->setFocus();
}

void window::action_quit()
{
    close();
}

void window::restart()
{
    render->restart_level();                    //appelle de la fonction membre de render de recommencer de niveau
    render->setFocusPolicy(Qt::StrongFocus);
    render->setFocus();
}
