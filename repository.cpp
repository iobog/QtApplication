#include "repository.h"
#include <cassert>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

bool RepoMasini::exist(const Masina& p) const
{
  try {
    find(p.getNrInmatriculare());
    return true;
  }
  catch (MasinaRepoException&) {
    return false;
  }
}


void RepoMasini::adaugaEntitate(const Masina& a)
{
  if (exist(a))
  {
    throw MasinaRepoException("Exista deja aceasta masina cu nr de intamtriculare");

  }
  all.push_back(a);
}

void RepoMasini::adaugaAceeasiEntitate(const Masina& a)
{
  all.push_back(a);
}

const Masina& RepoMasini::find(int numar) const
{
  auto it = std::find_if(all.begin(), all.end(), [numar](const Masina& m) {
    return m.getNrInmatriculare() == numar;
    });

  if (it != all.end())
  {
    return *it;
  }
  else
  {
    throw MasinaRepoException("Nu exista: ");
  }
}


//const Masina& RepoMasini::find(int numar) const
//{
//  // TODO: insert return statement here
// /* std::find_if()*/
//  for (const auto& p : all)
//  {
//    if (p.getNrInmatriculare() == numar)
//      return p;
//  }
//  throw MasinaRepoException("Nu exista masina cu numarul de inmatriculare: ");
//}

const vector<Masina>& RepoMasini::getAll() const noexcept
{
  return all;
}

void RepoMasini::stergeEntitate(const int id)
{
  auto it = std::find_if(all.begin(), all.end(), [id](const Masina& m) {
    return m.getNrInmatriculare() == id;
    });

  if (it != all.end()) {
    // If found, erase it from the vector
    all.erase(it);
  }
  else {
    // If not found, throw an exception
    throw MasinaRepoException("Nu exista in repository");
  }
}

void RepoMasini::modificaEntitate(const Masina m)
{

  if (!exist(m))
    throw MasinaRepoException("Nu exista aceasta masina");
  for (auto& masina : all)
  {
    if (masina.getNrInmatriculare() == m.getNrInmatriculare())
    {
      masina.setModel(m.getModel());
      masina.setProducator(m.getProducator());
      masina.setTip(m.getTip());
      break;
    }
  }
}



ostream& operator<<(ostream& out, const MasinaRepoException& ex)
{
  out << ex.msg;
  return out;
}

void MasinaRepoFile::savetofile()
{
  std::ofstream f(fileName);
  if (!f.is_open()) { //verify if the stream is opened
    std::string msg("Unable to open file:");
    throw MasinaRepoException(msg);
  }
  for (auto& m : RepoMasini::getAll()) {
    f << m.getNrInmatriculare();
    f << std::endl;
    f << m.getProducator();
    f << std::endl;
    f << m.getModel();
    f << std::endl;
    f << m.getTip();
    f << std::endl;
  }
  f.close();
}
void MasinaRepoFile::loadFromFile() {
  std::ifstream f(fileName);
  if (!f.is_open()) { throw MasinaRepoException("Unable to open file:"); }
  while (!f.eof()) {
    int numarInamtriculare;
    string model_r, tip_r, producator_r;
    f >> numarInamtriculare;
    if (f.eof()) {
      break;
    }
    f >> producator_r >> model_r >> tip_r;
    Masina m{ numarInamtriculare,producator_r,model_r,tip_r };

    RepoMasini::adaugaEntitate(m);
  }
  f.close();
}

void testDelete()
{
  RepoMasini repo;
  repo.adaugaEntitate(Masina{ 12,"Volvo","XC90","SUV" });
  repo.adaugaEntitate(Masina{ 1,"Mercedes","S","Sedan" });
  repo.adaugaEntitate(Masina{ 2,"Mercedes","S","Sedan" });
  repo.adaugaEntitate(Masina{ 3,"Mercedes","S","Sedan" });
  assert(repo.getAll().size() == 4);
  repo.stergeEntitate(1);
  assert(repo.getAll().size() == 3);
  try
  {
    repo.stergeEntitate(1);
    //assert (false);
  }
  catch (const MasinaRepoException&) {
    assert(true);
  }

}

void testModifica()
{
  RepoMasini repo;
  repo.adaugaEntitate(Masina{ 12,"Volvo","XC90","SUV" });
  repo.adaugaEntitate(Masina{ 1,"Mercedes","S","Sedan" });
  repo.adaugaEntitate(Masina{ 2,"Mercedes","S","Sedan" });
  repo.adaugaEntitate(Masina{ 3,"Mercedes","S","Sedan" });
  auto newCar = Masina{ 1,"BMW","X6","SUV" };
  assert(repo.getAll().size() == 4);
  repo.modificaEntitate(newCar);
  assert(repo.find(1).getProducator() == "BMW");
  assert(repo.find(1).getModel() == "X6");
  assert(repo.find(1).getTip() == "SUV");
  try {
    auto newCarTest = Masina{ 99,"BMW","X6","SUV" };
    repo.modificaEntitate(newCarTest);
    //assert(false);
  }
  catch (const MasinaRepoException&)
  {
    assert(true);
  }

}






void testAdauga()
{
  RepoMasini repo;
  repo.adaugaEntitate(Masina{ 12,"Volvo","XC90","SUV" });

  assert(repo.find(12).getNrInmatriculare() == 12);
  assert(repo.find(12).getProducator() == "Volvo");
  assert(repo.find(12).getModel() == "XC90");
  assert(repo.find(12).getTip() == "SUV");


  repo.adaugaEntitate(Masina{ 1,"Mercedes","S","Sedan" });

  assert(repo.getAll().size() == 2);
  repo.adaugaAceeasiEntitate(Masina{ 12,"Volvo","XC90","SUV" });
  assert(repo.getAll().size() == 3);
  try {
    repo.adaugaEntitate(Masina{ 1,"Mercedes","S","Sedan" });
    //assert(false);
  }
  catch (const MasinaRepoException&) {
    assert(true);
  }

  try {
    repo.find(2);
    //assert(false);
  }
  catch (const MasinaRepoException& e) {
    std::stringstream os;
    os << e;
    assert(os.str().find("exista") >= 0);
  }

}

void testCauta()
{
  RepoMasini repo;
  repo.adaugaEntitate(Masina{ 12,"Volvo","XC90","SUV" });
  repo.adaugaEntitate(Masina{ 1,"Mercedes","S","Sedan" });

  auto& p = repo.find(1);
  assert(p.getModel() == "S");
  assert(p.getProducator() == "Mercedes");
  assert(p.getTip() == "Sedan");
  try {
    repo.find(3);
    //assert(false);
  }
  catch (MasinaRepoException&) {
    assert(true);
  }
}
void testFileRepo() {
  std::ofstream g("testMasina.txt", std::ios::trunc);
  g.close();
  MasinaRepoFile repositoryFile("testMasina.txt");
  repositoryFile.adaugaEntitate(Masina{ 1,"a","a","a" });

  MasinaRepoFile secondRepositoryFile("testMasina.txt");
  auto p = secondRepositoryFile.find(1);
  assert(p.getNrInmatriculare() == 1);
  try {
    secondRepositoryFile.find(2);
    //assert(false);
  }
  catch (MasinaRepoException&) {
    assert(true);
  }

  Masina k{ 1,"k","k" ,"k" };
  secondRepositoryFile.modificaEntitate(k);
  p = secondRepositoryFile.find(1);
  assert(p.getModel() == "k");
  assert(p.getProducator() == "k");
  assert("k" == p.getTip());
  try {
    Masina k2{ 2,"k","k" ,"k" };
    secondRepositoryFile.modificaEntitate(k2);
    //assert(false);
  }
  catch (MasinaRepoException&) {
    assert(true);
  }



  secondRepositoryFile.stergeEntitate(1);
  assert(secondRepositoryFile.getAll().size() == 0);
  try {
    secondRepositoryFile.stergeEntitate(1);
    //assert(false);
  }
  catch (MasinaRepoException&) {
    assert(true);
  }




}

void testrepo()
{
  testAdauga();
  testCauta();
  testDelete();
  testModifica();
  testFileRepo();
}


