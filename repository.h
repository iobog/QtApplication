#pragma once
#pragma once
#include "domeniu.h"
#include "RepositoryInterface.h"
//#include "vector_dinamic.h"
#include<vector>
#include <fstream>
#include<string>
#include<ostream>
using std::vector;
using std::string;
using std::ostream;

class RepoMasini :public RepositoryInterface {
  vector<Masina>all;
protected:

public:
  bool exist(const Masina& p)const override;
  inline RepoMasini() = default;
  virtual ~RepoMasini() = default;
  RepoMasini(const RepoMasini& ot) = delete;
  virtual void adaugaEntitate(const Masina& a)override;
  virtual void adaugaAceeasiEntitate(const Masina& a)override;
  const Masina& find(int numar)const override;
  const vector<Masina>& getAll()const noexcept override;
  /// <summary>
  /// Functie care sterge
  /// </summary>
  /// <param name="numar"></param>
  virtual void stergeEntitate(const int numar) override;
  virtual void modificaEntitate(const Masina m)override;
};

class MasinaRepoException {
  string msg;
public:
  MasinaRepoException(string k) :msg{ k } {};
  friend ostream& operator <<(ostream& out, const MasinaRepoException& ex);
  string getMsg() { return this->msg; }

};
ostream& operator<<(ostream& out, const MasinaRepoException& ex);

void testrepo();



class MasinaRepoFile :public RepoMasini
{
  void loadFromFile();
  void savetofile();
  string fileName;
  void clearFile()
  {
    std::ofstream f(fileName);
  }
public:
  MasinaRepoFile() = default;
  MasinaRepoFile(std::string filename) :RepoMasini(), fileName{ filename } {
    loadFromFile();
  }
  void adaugaEntitate(const Masina& m) override {
    RepoMasini::adaugaEntitate(m);
    savetofile();
  }
  void stergeEntitate(const int numar)override {
    RepoMasini::stergeEntitate(numar);
    savetofile();
  }
  void modificaEntitate(const Masina m)override {
    RepoMasini::modificaEntitate(m);
    savetofile();
  }


};