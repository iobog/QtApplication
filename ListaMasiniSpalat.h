#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Observer.h"
#include "domeniu.h"
#include "repository.h"
#include <QWidget>
#include <QPainter>

class MasiniPentruSapalat : public Observable {
private:
  std::vector<Masina> ListaMasiniPentruSpalat;
  RepositoryInterface& repo;

public:
  MasiniPentruSapalat(RepositoryInterface& repo) : repo{ repo } {}
  MasiniPentruSapalat() = default;

  void adauga(const int m) {
    ListaMasiniPentruSpalat.push_back(repo.find(m));
    this->notify();
  }

  void goleste() {
    ListaMasiniPentruSpalat.clear();
    this->notify();
  }

  void umple(size_t cate) {
    std::vector<Masina> k = repo.getAll();
    std::shuffle(k.begin(), k.end(), std::default_random_engine(std::random_device{}())); // Shuffle the vector
    while (cate > 0) {
      if (k.empty()) {
        k = repo.getAll();
        std::shuffle(k.begin(), k.end(), std::default_random_engine(std::random_device{}())); // Shuffle again if necessary
      }
      ListaMasiniPentruSpalat.push_back(k.back());
      k.pop_back();
      cate--;
    }
    this->notify();
  }

  const std::vector<Masina>& lista() const {
    return ListaMasiniPentruSpalat;
  }
};

class MasiniSpalatDesen : public QWidget, public Observer {
private:
  MasiniPentruSapalat& masini;

public:
  MasiniSpalatDesen(MasiniPentruSapalat& masini) : masini{ masini } {
    masini.addObserver(this);
    setFixedSize(650, 650);
  }
  void paintEvent(QPaintEvent* ev) override {
    QPainter p{ this };
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, 600);
    std::uniform_int_distribution<int> colorDist(0, 255);
    for (const auto& masina : masini.lista())
    {
      int x = dist(mt);
      int y = dist(mt);
      int r = colorDist(mt);
      int g = colorDist(mt);
      int b = colorDist(mt);

      p.setBrush(QColor{ r, g, b });
      p.drawRect(x, y, 20, 20);
    
    }
  }

  void update() override {
    repaint();
  }
};
