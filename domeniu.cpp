#include "domeniu.h"
#include <cassert>


bool cmpTip(const Masina& p1, const Masina& p2) {
  return p1.getTip() < p2.getTip();
}

bool cmpNrInmatirculare(const Masina& p1, const Masina& p2) noexcept {
  return p1.getNrInmatriculare() < p2.getNrInmatriculare();
}

//bool cmpNrInmatirculare(const Masina& p1, const Masina& p2) {
//  return p1.getNrInmatirculare() < p2.getNrInmatirculare();
//}




void testGet() {
  Masina t{ 12,"Volvo","XC90","SUV" };
  assert(t.getModel() == "XC90");
  assert(t.getNrInmatriculare() == 12);
  assert(t.getTip() == "SUV");
  assert(t.getProducator() == "Volvo");

}
void testSet() {
  Masina t{ 12,"Volvo","XC90","SUV" };
  t.setModel("S");
  t.setNrInmatirculare(1);
  t.setProducator("Mercedes");
  t.setTip("Sedan");
  assert(t.getModel() == "S");
  assert(t.getNrInmatriculare() == 1);
  assert(t.getTip() == "Sedan");
  assert(t.getProducator() == "Mercedes");
}



void testDomeniu()
{
  testGet();
  testSet();
}