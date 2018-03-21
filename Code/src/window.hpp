#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QMainWindow>

//forward declaration
namespace Ui{
class MainWindow;
}
class render_area;
class myWidgetGL;

/** Declaration of the window class */
class window: public QMainWindow
{
    Q_OBJECT

public:

    window(QWidget *parent=nullptr);
    ~window();

private slots:

    void action_quit();

    /** Appellé pour changer de niveau lorsque l'utilisateur choisi un niveau*/
    void change_level(int value);

    /** Appelé pour recommencer un niveau*/
    void restart();

private:

    Ui::MainWindow *ui;
    render_area *render;
    myWidgetGL *glWidget;

};

#endif
