#pragma once
#include "domeniu.h"
#include <vector>

using std::vector;


class RepositoryInterface {
protected:
  virtual bool exist(const Masina& p)const = 0;
public:
  RepositoryInterface() = default;
  virtual ~RepositoryInterface() = default;
  virtual void adaugaEntitate(const Masina& a) = 0;
  virtual void adaugaAceeasiEntitate(const Masina& a) = 0;
  virtual const Masina& find(int numar)const = 0;
  virtual const vector<Masina>& getAll()const noexcept = 0;
  virtual void stergeEntitate(const int numar) = 0;
  virtual void modificaEntitate(const Masina m) = 0;
};