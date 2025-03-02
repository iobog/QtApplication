#pragma once
#include <qwidget.h>
#include <qtableview.h>
#include "domeniu.h"
#include <vector>
#include <string>
#include <QAbstractTableModel>

using std::vector;
using std::string;
using std::to_string;

class MyTableModel : public QAbstractTableModel {
  vector<Masina> masini;
public:
  explicit MyTableModel(const vector<Masina>& f) : masini{ f } {}

  int rowCount(const QModelIndex& parent = QModelIndex()) const override {
    return masini.size();
  }

  int columnCount(const QModelIndex& parent = QModelIndex()) const override {
    return 4;
  }

  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
    if (role == Qt::BackgroundRole) {
      switch (index.row() % 3) {
      case 0: return QBrush{ QColor{249, 236, 126} }; 
      case 1: return QBrush{ QColor{227, 204, 178} }; 
      case 2: return QBrush{ QColor{226, 98, 116} };  
      default: break;
      }
    }

    if (role == Qt::ForegroundRole) {
      return QBrush{ QColor{0, 0, 0} }; 
    }

    if (role == Qt::DisplayRole) {
      Masina  l = masini[index.row()];
      switch (index.column()) {
      case 0: return QString::number(l.getNrInmatriculare()); break;
      case 1: return QString::fromStdString(l.getProducator()); break;
      case 2: return QString::fromStdString(l.getModel()); break;
      case 3: return QString::fromStdString(l.getTip()); break;
      default: break;
      }
    }

    if (role == Qt::FontRole) {
      int rand = index.row();
      switch (rand % 3) {
      case 0: { QFont f("Arial", 10); f.setUnderline(true); return f;  break; }
      case 1: { QFont f("Comic Sans MS", 10); f.setBold(true); return f;  break; }
      case 2: { QFont f("Palatino Linotype", 10); f.setItalic(true); return f;  break; }
      default: break;
      }
    }
    return QVariant{};
  }

  QVariant headerData(int section, Qt::Orientation orientation, int role) const override
  {
    if (orientation == Qt::Horizontal) {
      if (role == Qt::DisplayRole) {
        switch (section) {
        case 0: return "Numar Inmatriculare"; break;
        case 1: return "Producator"; break;
        case 2: return "Mode"; break;
        case 3: return "Tipul"; break;
        default: break;
        }
      }
    }

    if (orientation == Qt::Vertical) {
      if (role == Qt::DisplayRole) {
        return section + 1;
      }
    }

    return QVariant();
  }

  void seteazaLocatari(vector<Masina>& ma) {
    this->masini = ma;
    QModelIndex topLeft = createIndex(0, 0);
    QModelIndex bottomRight = createIndex(rowCount(), columnCount());
    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
  }
};