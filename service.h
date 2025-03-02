#pragma once
#include "domeniu.h"
#include "validator.h"
#include "repository.h"
#include "export.h"
#include "undoaction.h"
#include <string>
#include <vector>
#include <functional>
#include <random>
#include <algorithm>
#include <chrono>
#include<map>
#include "ListaMasiniSpalat.h"

using std::vector;
using std::function;
using std::shuffle;
using std::map;
using std::unique_ptr;

class ServiceMasina{
  RepositoryInterface& rep;
  MasiniPentruSapalat repoMasiniSpalat{rep};
  ValidatorMasina& val;

  std::vector<std::unique_ptr<UndoAction> >undoActions;

  vector<Masina> generalSort(bool (*maiMicF)(const Masina&, const  Masina&));
  vector<Masina> filtreaza(function<bool(const Masina&)> fct);
  //vector& Lista;

public:
  ServiceMasina(RepositoryInterface& rep,  ValidatorMasina& val) :rep{ rep },  val { val } {
   
  }
  MasiniPentruSapalat& getcos()
  {
    return repoMasiniSpalat;
  }
  //ServiceMasina() = default;
  //ServiceMasina(const ServiceMasina& ot) = delete;
  //ServiceMasina(const ServiceMasina& t) = delete;
  void operator=(const ServiceMasina& t) = delete;
  const vector<Masina>& getAll()noexcept {
    return rep.getAll();
  }
  const vector<Masina>& getAllServiceMasiniSpalat()noexcept {
    return repoMasiniSpalat.lista();
  }


  void serviceAdaugaMasina(int nrInmatirculare, const string& producator, const string& model, const string& tip);

  void serviceStergeMasina(int nrInmatriculare);

  void serviceModificaMasina(int nrInmatirculare, const string& producator, const string& model, const string& tip);

  const Masina& cautaEntitate(int numar)const;

  vector<Masina> sortByType();

  vector<Masina> sortByNrInmatirculare();

  vector<Masina>sortByProducatorSiModel();

  vector<Masina> filtrareProducator(string producator);

  vector<Masina> filtrareTip(string tip);

  //void adaugaMasinaIn(int numarInmatiruclarePentruAdaugare);

  //void golesteListaMasini();

  //void fillRandomEntitati(int numarDeEntitatiNoi);

  map<string, vector<Masina> > raportTip();


  void exportaListaCVS(std::string fName) const;

  void exportaListaHTML(std::string fName)const;

  //void clearListaMasiniSpalat();

  void undo();

  const std::vector<Masina>& addToLista(const int nr);

  const std::vector<Masina>& addRandom(int cate);

  const std::vector<Masina>& golesteLista();

  const std::vector<Masina>& toateDinLista();

  MasiniPentruSapalat& getMasiniPentruSapalat(){
    return repoMasiniSpalat;
  }

  RepositoryInterface& getr()
  {
    return rep;
  }
};


void testService();
