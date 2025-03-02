#include "service.h"
#include <functional>
#include <algorithm>
#include <assert.h>


//vect_propriu<Masina> Service::generalSort(bool(*maiMicF)(const Masina&, const Masina&)) {
//  vect_propriu<Masina> v{ rep.getAll() }; // fac o copie
//
//  //// Using std::sort with custom comparison function
//  //std::sort(v.begin(), v.end(), maiMicF);
//
//  return v;
//}


vector<Masina> ServiceMasina::generalSort(bool(*maiMicF)(const Masina&, const Masina&)) {
  vector<Masina>v{ rep.getAll() };
  std::sort(v.begin(), v.end(), maiMicF);
  return v;
}
vector<Masina> ServiceMasina::sortByType() {
  return generalSort(cmpTip);
}
vector<Masina> ServiceMasina::sortByNrInmatirculare() {
  return generalSort(cmpNrInmatirculare);
}
vector<Masina> ServiceMasina::sortByProducatorSiModel() {
  return generalSort([](const Masina& p1, const Masina& p2)
    {
      if (p1.getProducator() == p2.getProducator()) {
        return p1.getModel() < p2.getModel();
      }
      return p1.getProducator() < p2.getProducator();
    });
}

vector<Masina> ServiceMasina::filtreaza(std::function<bool(const Masina&)> fct) {
  std::vector<Masina> stlVec = rep.getAll();
  std::vector<Masina> rez;
  rez.reserve(stlVec.size()); // Reserve space to avoid unnecessary reallocations

  std::copy_if(stlVec.begin(), stlVec.end(), std::back_inserter(rez), fct);

  return (rez);
}

vector<Masina> ServiceMasina::filtrareProducator(string producator) {
  return filtreaza([producator](const Masina& p) {
    return p.getProducator() == producator;
    });
}

vector<Masina> ServiceMasina::filtrareTip(string Tip) {
  return filtreaza([=](const Masina& p) {
    return p.getTip() == Tip;
    });
}

//void ServiceMasina::adaugaMasinaIn(int numarInmatiruclarePentruAdaugare)
//{
//
//  Masina p = { rep.find(numarInmatiruclarePentruAdaugare) };
//  repoMasiniSpalat.adaugaEntitate(p);
//
//}
//
//void ServiceMasina::golesteListaMasini()
//{
//  for (auto& p : repoMasiniSpalat.getAll())
//    repoMasiniSpalat.stergeEntitate(p.getNrInmatriculare());
//
//
//}
void ServiceMasina::exportaListaCVS(std::string fName) const {
  exportToCVS(fName, repoMasiniSpalat.lista());
}

void ServiceMasina::exportaListaHTML(std::string fName) const {
  exportToHTML(fName, repoMasiniSpalat.lista());
}

//void ServiceMasina::clearListaMasiniSpalat()
//{
//  for (auto& c : repoMasiniSpalat.getAll()) {
//    repoMasiniSpalat.stergeEntitate(c.getNrInmatriculare());
//  }
//}

void ServiceMasina::undo()
{
  if (undoActions.empty())
  {
    throw MasinaRepoException{ "nu mai exista operatii " };
  }
  undoActions.back()->executeUndo();

  undoActions.pop_back();
}

const std::vector<Masina>& ServiceMasina::addToLista(const int nr)
{
  const Masina& p = rep.find(nr);
  repoMasiniSpalat.adauga(p.getNrInmatriculare());
  //this->notify();
  return repoMasiniSpalat.lista();
}

const std::vector<Masina>& ServiceMasina::addRandom(int cate)
{
  repoMasiniSpalat.umple(cate);
  //this->notify();
  return repoMasiniSpalat.lista();
}

const std::vector<Masina>& ServiceMasina::golesteLista()
{
  repoMasiniSpalat.goleste();
  //this->notify();
  return repoMasiniSpalat.lista();
}

const std::vector<Masina>& ServiceMasina::toateDinLista()
{
  return repoMasiniSpalat.lista();
}


//void ServiceMasina::fillRandomEntitati(int numarDeEntitatiNoi)
//{
//  vector<Masina> ListaMasiniExistente = rep.getAll();
//
//  // Shuffle the ListaMasiniExistente vector
//  std::shuffle(ListaMasiniExistente.begin(), ListaMasiniExistente.end(), std::default_random_engine(std::random_device{}()));
//
//  // Fill the ListaMasiniSpalat vector with random entities
//  int k = 0;
//  while ((k < numarDeEntitatiNoi) && (!ListaMasiniExistente.empty())) {
//    repoMasiniSpalat.adaugaAceeasiEntitate(ListaMasiniExistente.back());
//    ListaMasiniExistente.pop_back();
//
//    // If ListaMasiniExistente is empty and ListaMasiniSpalat vector still needs to be filled, refill it with all elements
//    if (ListaMasiniExistente.empty() && k < numarDeEntitatiNoi) {
//      ListaMasiniExistente = rep.getAll();
//      std::shuffle(ListaMasiniExistente.begin(), ListaMasiniExistente.end(), std::default_random_engine(std::random_device{}()));
//    }
//    k++;
//  }
//

//}

map<string, vector<Masina> > ServiceMasina::raportTip()
{
  map < string, vector<Masina> >raport;
  for (const auto& masina : rep.getAll())
  {
    raport[masina.getTip()].push_back(masina);
  }
  return raport;
}




void ServiceMasina::serviceAdaugaMasina(int nrInmatirculare, const string& producator, const string& model, const string& tip)
{
  Masina m{ nrInmatirculare,producator,model,tip };
  val.validate(m);
  rep.adaugaEntitate(m);
  undoActions.push_back(std::make_unique<undoAdauga>(rep, m));
}

void ServiceMasina::serviceStergeMasina(int nrInmatriculare)
{
  auto p = rep.find(nrInmatriculare);
  Masina m{ p.getNrInmatriculare(),p.getProducator(),p.getModel(),p.getTip() };
  rep.stergeEntitate(nrInmatriculare);
  undoActions.push_back(std::make_unique<undoSterge>(rep, m));
}

void ServiceMasina::serviceModificaMasina(int nrInmatirculare, const string& producator, const string& model, const string& tip)
{
  Masina m{ nrInmatirculare,producator,model,tip };
  val.validate(m);
  rep.modificaEntitate(m);
  undoActions.push_back(std::make_unique<undoModifica>(rep, m));
}

const Masina& ServiceMasina::cautaEntitate(int numar) const
{
  return rep.find(numar);
}

//void testServiceSterge()
//{
//  RepoMasini r;
//
//  ValidatorMasina v;
//  ServiceMasina s{ r,v };
//  s.serviceAdaugaMasina(1, "BMW", "S", "sedan");
//  s.serviceAdaugaMasina(2, "Renault", "Megane", "sedan");
//  s.serviceAdaugaMasina(3, "Volvo", "XC90", "SUV");
//  assert(s.getAll().size() == 3);
//  s.serviceStergeMasina(2);
//  assert(s.getAll().size() == 2);
//  try {
//    s.serviceStergeMasina(2);
//    //assert(false);
//  }
//  catch (MasinaRepoException&)
//  {
//    assert(true);
//  }
//}
//
//void testServiceModifica() {
//  RepoMasini r;
//
//  ValidatorMasina v;
//  ServiceMasina s{ r,v };
//  s.serviceAdaugaMasina(1, "BMW", "S", "sedan");
//  s.serviceAdaugaMasina(2, "Renault", "Megane", "sedan");
//  s.serviceAdaugaMasina(3, "Volvo", "XC90", "SUV");
//  assert(s.getAll().size() == 3);
//  s.serviceModificaMasina(2, "Mercedes", "GClass", "SUV");
//  assert(s.cautaEntitate(2).getModel() == "GClass");
//  assert(s.cautaEntitate(2).getTip() == "SUV");
//  assert(s.cautaEntitate(2).getProducator() == "Mercedes");
//  try {
//    s.serviceModificaMasina(2, "", "", "");
//    //assert(false);
//  }
//  catch (ValidateException&)
//  {
//    assert(true);
//  }
//  try {
//    s.serviceModificaMasina(4, "Mercedes", "GClass", "SUV");
//    //assert(false);
//  }
//  catch (MasinaRepoException&)
//  {
//    assert(true);
//  }
//}
//
//void testServiceAdauga() {
//  RepoMasini r;
//  ValidatorMasina v;
//  ServiceMasina s{ r,v };
//  s.serviceAdaugaMasina(1, "BMW", "S", "sedan");
//  assert(s.getAll().size() == 1);
//  try {
//    s.serviceAdaugaMasina(2, "", "", "");
//    //assert(false);
//  }
//  catch (ValidateException&)
//  {
//    assert(true);
//  }
//  try {
//    s.serviceAdaugaMasina(1, "BMW", "S", "sedan");
//    //assert(false);
//  }
//  catch (MasinaRepoException&)
//  {
//    assert(true);
//  }
//
//
//
//
//
//}
//
//void testFiltrare() {
//  RepoMasini r;
//  //RepoMasini r2;
//  ValidatorMasina v;
//  ServiceMasina s{ r,v };
//  s.serviceAdaugaMasina(1, "BMW", "S", "sedan");
//  s.serviceAdaugaMasina(2, "Renault", "Megane", "sedan");
//  s.serviceAdaugaMasina(3, "Volvo", "XC90", "SUV");
//  assert(s.getAll().size() == 3);
//  assert(s.filtrareTip("sedan").size() == 2);
//  assert(s.filtrareTip("SUV").size() == 1);
//  assert(s.filtrareProducator("Renault").size() == 1);
//  assert(s.filtrareProducator("BMW").size() == 1);
//  assert(s.filtrareProducator("Volvo").size() == 1);
//}
//
//void testSortare() {
//  RepoMasini r;
//  //RepoMasini r2;
//  ValidatorMasina v;
//  ServiceMasina s{ r,v };
//  s.serviceAdaugaMasina(4, "BMW", "S", "sedan");
//  s.serviceAdaugaMasina(2, "Renault", "Megane", "sedan");
//  s.serviceAdaugaMasina(3, "Volvo", "XC90", "SUV");
//
//  Masina firstP = s.sortByType().at(0);
//
//  assert(firstP.getTip() == "SUV");
//
//  firstP = s.sortByNrInmatirculare().at(0);
//  assert(firstP.getNrInmatriculare() == 2);
//
//  firstP = s.sortByProducatorSiModel().at(0);
//  assert(firstP.getProducator() == "BMW");
//  assert(firstP.getModel() == "S");
//
//}
//
//void testFunctinalitatiNoi()
//{
//  RepoMasini r;
//  //RepoMasini r2;
//  ValidatorMasina v;
//  ServiceMasina s{ r,v };
//  s.serviceAdaugaMasina(4, "BMW", "S", "sedan");
//  s.serviceAdaugaMasina(2, "Renault", "Megane", "sedan");
//  s.serviceAdaugaMasina(3, "Volvo", "XC90", "SUV");
//  
//  assert(s.getAllServiceMasiniSpalat().size() == 1);
//  s.golesteLista();
//  assert(s.getAllServiceMasiniSpalat().size() == 0);
//  s.addRandom(4);
//  assert(s.getAllServiceMasiniSpalat().size() == 4);
//
//
//}
//
//void testRaport()
//{
//  RepoMasini r;
//  ValidatorMasina v;
//  ServiceMasina s{ r,v };
//  s.serviceAdaugaMasina(4, "BMW", "S", "sedan");
//  s.serviceAdaugaMasina(2, "Renault", "Megane", "sedan");
//  s.serviceAdaugaMasina(3, "Volvo", "XC90", "SUV");
//  map<string, vector<Masina> >data = s.raportTip();
//
//  assert(data.size() == 2);
//
//}
//
//
//
//void testExporta() {
//  RepoMasini r;
//
//  ValidatorMasina v;
//  ServiceMasina crt{ r,v };
//  crt.serviceAdaugaMasina(1, "a", "a", "a");
//  crt.serviceAdaugaMasina(2, "b", "b", "b");
//  crt.addToLista(1);
//  crt.addToLista(2);
//  crt.addRandom(3);
//  crt.exportaListaCVS("testExport.cvs");
//  std::ifstream in("testExport.cvs");
//  assert(in.is_open());
//  int countLines = 0;
//  while (!in.eof()) {
//    string line;
//    in >> line;
//    countLines++;
//  }
//  in.close();
//  assert(countLines == 6);//avem o linie pentru fiecare pet + o linie goala
//  crt.exportaListaHTML("testExport.html");
//  in.open("testExport.html");
//  assert(in.is_open());
//
//  //daca se da un nume de fisier invalid se arunca exceptie
//  try {
//    crt.exportaListaCVS("test/Export.cvs");
//    assert(false);
//  }
//  catch (MasinaRepoException&) {
//    assert(true);
//  }
//  try {
//    crt.exportaListaHTML("a/b/c/Export.html");
//    assert(false);
//  }
//  catch (MasinaRepoException&) {
//    assert(true);
//  }
//}
//
//
//void testUndoAdauga() {
//  RepoMasini r;
//  ValidatorMasina v;
//  ServiceMasina s{ r,v };
//  s.serviceAdaugaMasina(4, "BMW", "S", "sedan");
//  s.serviceAdaugaMasina(2, "Renault", "Megane", "sedan");
//  s.serviceAdaugaMasina(3, "Volvo", "XC90", "SUV");
//  s.undo();
//  assert(s.getAll().size() == 2);
//  s.undo();
//  s.undo();
//  assert(s.getAll().size() == 0);
//  try {
//    s.undo();
//    assert(false);
//  }
//  catch (MasinaRepoException& ex) {
//    assert(ex.getMsg() == "nu mai exista operatii ");
//  }
//}
//void testUndoStergeSiModifica() {
//  RepoMasini r;
//
//  ValidatorMasina v;
//  ServiceMasina s{ r,v };
//  s.serviceAdaugaMasina(4, "BMW", "S", "sedan");
//  s.serviceAdaugaMasina(2, "Renault", "Megane", "sedan");
//  s.serviceAdaugaMasina(3, "Volvo", "XC90", "SUV");
//  s.serviceStergeMasina(3);
//  s.undo();
//  assert(s.getAll().size() == 3);
//  auto before = s.cautaEntitate(4);
//  s.serviceModificaMasina(4, "a", "a", "a");
//  s.undo();
//  auto after = s.cautaEntitate(4);
//  assert("a" == after.getModel());
//  assert("a" == after.getTip());
//  assert("a" == after.getProducator());
//
//}



void testService() {
 /* testServiceAdauga();
  testServiceSterge();
  testServiceModifica();
  testFiltrare();
  testSortare();
  testFunctinalitatiNoi();
  testRaport();
  testExporta();
  testUndoAdauga();
  testUndoStergeSiModifica();*/
}

