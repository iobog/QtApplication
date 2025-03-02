#pragma once
#include "repository.h"
#include "domeniu.h"

class UndoAction {
public:
  virtual void executeUndo() = 0;
  virtual ~UndoAction() = default;

};

class undoAdauga :public UndoAction {
  Masina masina_adaugare;
  RepositoryInterface& repomasini;
public:
  undoAdauga(RepositoryInterface& repo, Masina masina) :repomasini{ repo }, masina_adaugare{ masina } {}
  void executeUndo() override {
    repomasini.stergeEntitate(masina_adaugare.getNrInmatriculare());
  }
};

class undoSterge :public UndoAction {
  Masina masina_adaugare;
  RepositoryInterface& repomasini;
public:
  undoSterge(RepositoryInterface& repo, Masina masina) :repomasini{ repo }, masina_adaugare{ masina } {}
  void executeUndo() override {
    repomasini.adaugaEntitate(masina_adaugare);
  }
};

class undoModifica :public UndoAction {
  Masina masina_adaugare;
  RepositoryInterface& repomasini;
public:
  undoModifica(RepositoryInterface& repo, Masina masina) :repomasini{ repo }, masina_adaugare{ masina } {}
  void executeUndo() override {
    repomasini.modificaEntitate(masina_adaugare);
  }
};