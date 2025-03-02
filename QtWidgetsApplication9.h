#pragma once
#pragma once
#include <QtWidgets/QApplication>
#include <qwidget.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <qtableview.h>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QGroupBox>
#include <QListWidget>
#include <QRadioButton>
#include "service.h"
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include "model.h"
#include "ui_QtWidgetsApplication9.h"
#include "service.h"
using std::vector;
using std::string;

class My_Gui : public QWidget
{
  Q_OBJECT
  friend class CosWindow;
private:
  /*Ui::QtWidgetsApplication4Class ui;
  QListView* carsListView;
  QVBoxLayout* mainLayout;
  QPushButton* button;*/

  ServiceMasina& service_masina;
  vector<string>tipuri;
  //lista masini
  QHBoxLayout* lyMain = new QHBoxLayout;
  QHBoxLayout* lyMain2 = new QHBoxLayout;
  QLabel* lblNrInamtriculare = new QLabel("Numar Inmatriculare: ");
  QLabel* lblProducator = new QLabel("Producator: ");
  QLabel* lblModel = new QLabel("Model: ");
  QLabel* lblTip = new QLabel("Tip: ");
  QLineEdit* editareNumar;
  QLineEdit* editareProducator;
  QLineEdit* editareModel;
  QLineEdit* editareTip;

  //funct service 

  QPushButton* btn_adaugare;
  QPushButton* btn_sterge;
  QPushButton* btn_actualizare;
  QPushButton* btn_undo;
  QPushButton* btn_cautare;
  QPushButton* btn_filtrare_tip;
  QPushButton* btn_open_masini_spalat;
  QPushButton* btn_filtrare_producator;

  //QTableWidget* tabel_masini = new QTableWidget;
  QTableView* tabel_view = new QTableView;
  MyTableModel* model;
  QListWidget* lista_masini = new QListWidget;
  QTableWidget* tabel_masini_spalat = new QTableWidget;
  QListWidget* lista_masini_spalat = new QListWidget;
  QWidget* btn_dyn = new QWidget;
  QLayout* ly_leftleft;
  QLayout* new_thing;
  QLayout* ly_btn_dy;

  vector<QPushButton*> butoane_tipuri_masini;

  QGroupBox* groupBoxSortare = new QGroupBox(tr("Tip sortare"));
  QRadioButton* radio_sortare_Numar = new QRadioButton(QString::fromStdString("Numar Inmatriculare"));
  QRadioButton* radio_sortare_Tip = new QRadioButton(QString::fromStdString("Tip"));
  QRadioButton* radio_sortare_Model = new QRadioButton(QString::fromStdString("Model + Producator"));
  QPushButton* btn_sortare;

  // lista masini pentru spalat

  QLabel* lblNrMasiniSpalat = new QLabel{ "Numar Inmatriculare: " };
  QLabel* lblNumarMasiniDeAdaugatPtSpalat = new QLabel{ "Numar de masini de adaugat: " };
  QLabel* lblFisierMasiniSpalat = new QLabel{ "Fisier: " };
  QLineEdit* editare_numar_inamt;
  QLineEdit* editare_nuamr_adaugare_elemente;
  QLineEdit* editare_nume_fisier;

  QPushButton* btn_adaugare_masini_spalat;
  QPushButton* btn_golire_masini_spalat;
  QPushButton* btn_generare_masini_spalat;
  QPushButton* btn_export_masini_spalat;
  QPushButton* btn_exit_lista_masini_spalat;

  void initializeGUIComponents();
  void conectare_butoane();
  void incarcare_lista(vector<Masina> masini);
  void incarcare_masini_spalat(vector <Masina> masini_spalat);

public:
  ~My_Gui();
  My_Gui(ServiceMasina& service) :service_masina{ service }
  {
    initializeGUIComponents();
    conectare_butoane();
    incarcare_lista(service.getAll());
    incarcare_masini_spalat(service.getAllServiceMasiniSpalat());
  }
  void gui_adaugare();
  void gui_actualizare();
  void gui_stergere();
  void gui_undo();
  void gui_cautare();
  void gui_filtru_producator();
  void gui_filtru_Tip();
  void adaugaButoane(const std::vector<Masina>& masini);
  void optiune();

  void gui_adaugare_masini_spalat();
  void gui_generare_masini_spalat();
  void gui_golire_masini_spalat();
  void gui_export_masini_spalat();
public slots:
  void clearMasiniSpalatData();
};
