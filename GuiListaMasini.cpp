#include "GuiListaMasini.h"

void ListaGUI::initGUIcmps()
{
  setLayout(mainLayout);
  QWidget* widdreapta = new QWidget;
  QVBoxLayout* v1 = new QVBoxLayout;
  widdreapta->setLayout(v1);
  lst = new QListWidget;
  v1->addWidget(lst);

  QWidget* formCos = new QWidget;
  QFormLayout* lyFormCos = new QFormLayout;
  formCos->setLayout(lyFormCos);
  editare_numar_inamt = new QLineEdit;
  editare_nuamr_adaugare_elemente = new QLineEdit;
  editare_nume_fisier = new QLineEdit;

  lyFormCos->addRow(lblNrMasiniSpalat, editare_numar_inamt);
  lyFormCos->addRow(lblNumarMasiniDeAdaugatPtSpalat, editare_nuamr_adaugare_elemente);

  lyFormCos->addRow(lblFisierMasiniSpalat, editare_nume_fisier);

  QWidget* widBtnD = new QWidget;
  QVBoxLayout* lyBtnsDr = new QVBoxLayout;
  widBtnD->setLayout(lyBtnsDr);
  lyBtnsDr->addWidget(formCos);

  btn_adaugare_masini_spalat = new QPushButton("Adaugare masina in lista masini spalat");
  btn_golire_masini_spalat = new QPushButton("Golire lista masini spalat");
  btn_generare_masini_spalat = new QPushButton("Generare lista masini spalat");
  btn_export_masini_spalat = new QPushButton("Export lista masini spalat");
  
  lyBtnsDr->addWidget(btn_adaugare_masini_spalat);
  lyBtnsDr->addWidget(btn_generare_masini_spalat);
  lyBtnsDr->addWidget(btn_golire_masini_spalat);
  lyBtnsDr->addWidget(btn_export_masini_spalat);
  
  mainLayout->addWidget(widdreapta);
  mainLayout->addWidget(widBtnD);
	



}

void ListaGUI::connectSignalsSlots()
{
  QObject::connect(btn_adaugare_masini_spalat, &QPushButton::clicked, [this]() {
    try
    {
      int numar = editare_numar_inamt->text().toInt();

      editare_numar_inamt->clear();

      data.adauga(numar);
      reloadList(data.lista());

    }
    catch (MasinaRepoException& e)
    {
      QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
    }
    catch (ValidateException& e)
    {
      QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
    }
    });
  //QObject::connect(btn_golire_masini_spalat, &QPushButton::clicked, this, &My_Gui::gui_golire_masini_spalat);
  QObject::connect(btn_generare_masini_spalat, &QPushButton::clicked, [&]() {
    try
    {
      int nr = editare_nuamr_adaugare_elemente->text().toInt();
      editare_nuamr_adaugare_elemente->clear();
      /*if (nr > service_masina.getAll().size())
        QMessageBox::warning(this, "warning", QString::fromStdString("Numarul depaseste lungimea listei!"));*/
        /*else
        {*/
      data.umple(nr);
      reloadList(data.lista());
     // QMessageBox::information(this, "info", QString::fromStdString("Lista de Masini pentru spalat a fost generat cu succes!"));
      //}
    }
    catch (MasinaRepoException& e)
    {
      QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
    }
    });
  QObject::connect(btn_golire_masini_spalat, &QPushButton::clicked, [&]() {
    try
    {
      data.goleste();
      reloadList(data.lista());

      //QMessageBox::information(this, "info", QString::fromStdString("Lista de masini pentru spalat  a fost golita cu succes!"));

    }
    catch (MasinaRepoException& e)
    {
      QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
    }
    });
  //QObject::connect(btn_export_masini_spalat, &QPushButton::clicked, this, &My_Gui::gui_export_masini_spalat);
}

void ListaGUI::reloadList(const std::vector<Masina>& masini)
{
  lst->clear();
  int k = 0;
  for (auto&m : masini) {
    k++;
    string masina = std::to_string(k)+"       "+ std::to_string(m.getNrInmatriculare()) + "       " + m.getProducator() + "       " + m.getModel() + "        " + m.getTip();
    QListWidgetItem* it = new QListWidgetItem{ QString::fromStdString(masina) };
    if (m.getNrInmatriculare()>4) {
      //it->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
    }
    lst->addItem(it);

  }
}
