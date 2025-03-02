#pragma once

#include <string>
#include<iostream>
using  std::string;
using std::cout;
class Masina {
private:
  //nr inmatriculare;
  //producator
  //model
  //tip
  int nrInmatriculare;
  string tip, model;
  string producator;
public:
  Masina() = default;
  Masina(const int nr, const string prod, const string mod,
    const string t) :nrInmatriculare{ nr }, producator{ prod }, model{ mod }, tip{ t } {};


  Masina(const Masina& m)
  {
    /*{
      std::cout << "se face copie\n";
    }*/
    nrInmatriculare = m.getNrInmatriculare();
    producator = m.getProducator();
    model = m.getModel();
    tip = m.getTip();

  }


  string getTip()const {
    return this->tip;
  }

  string getModel()const {
    return this->model;
  }

  string getProducator()const {
    return this->producator;
  }

  int getNrInmatriculare()const noexcept {
    return this->nrInmatriculare;
  }


  void setTip(const string tip_nou) {
    this->tip = tip_nou;
  }
  void setProducator(const string producator_nou) {
    this->producator = producator_nou;
  }
  void setNrInmatirculare(const int numar_nou)  noexcept {
    this->nrInmatriculare = numar_nou;
  }
  void setModel(const string model_nou) {
    this->model = model_nou;
  }

};
bool cmpNrInmatirculare(const Masina& p1, const Masina& p2) noexcept;
bool cmpTip(const Masina& p1, const  Masina& p2);
void testDomeniu();
