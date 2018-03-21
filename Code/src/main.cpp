/** ***************************************************************************\
 * SOIGNON Matthieu ; PASTOR Mickael 4ETI
 * Majeure Image, Modelisation et Informatique, module M2
 * --------------
 * Jeu qui casse des briques
\** ***************************************************************************/

#include <QApplication>

#include "window.hpp"
#include "vec2.hpp"
#include <vector>


int main(int argc,char *argv[])
{
  QApplication app(argc,argv);
  window win;
  win.show();
  return app.exec();
}
