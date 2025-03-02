#include "QtWidgetsApplication9.h"
#include "GuiListaMasini.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MasinaRepoFile masini_repository("data.txt");

  ValidatorMasina validator;
 // MasiniPentruSapalat(masini_repository);
  ServiceMasina service(masini_repository, validator);

  My_Gui t(service);

  ListaGUI* k = new ListaGUI{ service.getMasiniPentruSapalat(),service};
  ListaGUI* k1 = new ListaGUI{ service.getMasiniPentruSapalat(),service };
  MasiniSpalatDesen* p = new MasiniSpalatDesen{ service.getcos() };
  //ListaGUI* k2 = new ListaGUI{ service.getMasiniPentruSapalat(),service };
  k->show();
  k1->show();
  p->show();
  //k2->show();
  
  return a.exec();
}
