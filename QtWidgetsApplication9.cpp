#include "QtWidgetsApplication9.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qlistview.h>
#include <QVBoxLayout>
#include <qpushbutton.h>
using namespace std;
//QtWidgetsApplication4::QtWidgetsApplication4(QWidget *parent)
//    : QWidget(parent)
//{
//    /*ui.setupUi(this);
//    this->carsListView = new QListView();
//    this->mainLayout = new QVBoxLayout(this);
//    this->button = new QPushButton("apasa");
//    this->mainLayout->addWidget(this->button);
//    this->setLayout(mainLayout);*/
//    //this->setCentralWidget(button);
//}

My_Gui::~My_Gui()
{}

void clearLayout(QLayout* layout)
{
	if (layout) {
		while (layout->count() > 0) {
			QLayoutItem* item = layout->takeAt(0);
			QWidget* widget = item->widget();
			if (widget)
				delete widget;
			delete item;
		}
	}
}

void My_Gui::initializeGUIComponents()
{
	
	setLayout(lyMain);
	QWidget* fereastra_lista = new QWidget;
	//QHBoxLayout* lyMain = new QHBoxLayout;
	fereastra_lista->setLayout(lyMain);

	//left part

	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;

	QWidget* leftleft = new QWidget;
	QVBoxLayout* lyLeftLeft = new QVBoxLayout;
	QVBoxLayout* lyLeftNewWidget = new QVBoxLayout;
	QVBoxLayout* lyLeftLeftNewWidget = new QVBoxLayout;

	left->setLayout(lyLeft);

	leftleft->setLayout(this->ly_leftleft);

	int nr_linii = 10;
	int nr_coloane = 4;
	//tabel_masini = new QTableWidget{ nr_linii, nr_coloane };
	tabel_view = new QTableView;
	model = new MyTableModel(service_masina.getAll());
	tabel_view->setModel(model);
	QStringList HeaderTabel;
	HeaderTabel << "Numar Inmatriculare" << "Producator" << "Model" << "Tip";
	//tabel_view->setHorizontalHeaderLabels(HeaderTabel);
	//tabel_view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	btn_adaugare = new QPushButton("Adaugare masina");
	btn_actualizare = new QPushButton("Actualizare masina");
	btn_sterge = new QPushButton("Stergere masina");
	btn_cautare = new QPushButton("Cautare masina");
	btn_filtrare_tip = new QPushButton("Filtrare masini dupa Tip");
	btn_filtrare_producator = new QPushButton("Filtrare masini dupa Producator");
	btn_undo = new QPushButton("Undo");
	btn_open_masini_spalat = new QPushButton("Lista Masini Spalat");


	//formular adaugare

	QWidget* form = new QWidget;
	QFormLayout* ly_form = new QFormLayout;
	form->setLayout(ly_form);
	editareNumar = new QLineEdit;
	editareProducator = new QLineEdit;
	editareModel = new QLineEdit;
	editareTip = new QLineEdit;

	ly_form->addRow(lblNrInamtriculare, editareNumar);
	ly_form->addRow(lblProducator, editareProducator);
	ly_form->addRow(lblModel, editareModel);
	ly_form->addRow(lblTip, editareTip);


	QWidget* left_center1 = new QWidget;

	QVBoxLayout* lyLeft_center1 = new QVBoxLayout;

	left_center1->setLayout(lyLeft_center1);
	lyLeft_center1->addWidget(form);



	//ly_right_right->insertLayout();


	QWidget* left_center2 = new QWidget;
	QHBoxLayout* lyLeft_center2 = new QHBoxLayout;
	left_center2->setLayout(lyLeft_center2);
	lyLeft_center2->addWidget(btn_adaugare);
	lyLeft_center2->addWidget(btn_actualizare);
	lyLeft_center2->addWidget(btn_sterge);
	lyLeft_center2->addWidget(btn_cautare);
	lyLeft_center2->addWidget(btn_open_masini_spalat);

	QWidget* left_center3 = new QWidget;
	QHBoxLayout* lyLeft_center3 = new QHBoxLayout;
	left_center3->setLayout(lyLeft_center3);
	lyLeft_center3->addWidget(btn_undo);

	QVBoxLayout* lyRadioBoxSortare = new QVBoxLayout;
	this->groupBoxSortare->setLayout(lyRadioBoxSortare);
	lyRadioBoxSortare->addWidget(radio_sortare_Numar);
	lyRadioBoxSortare->addWidget(radio_sortare_Model);
	lyRadioBoxSortare->addWidget(radio_sortare_Tip);
	btn_sortare = new QPushButton("Sortare");
	lyRadioBoxSortare->addWidget(btn_sortare);

	QWidget* left_center4 = new QWidget;
	QVBoxLayout* lyLeft_center4 = new QVBoxLayout;
	left_center4->setLayout(lyLeft_center4);
	lyLeft_center4->addWidget(btn_filtrare_producator);
	lyLeft_center4->addWidget(btn_filtrare_tip);

	QWidget* left_center5 = new QWidget;
	QHBoxLayout* lyLeft_center5 = new QHBoxLayout;
	left_center5->setLayout(lyLeft_center5);
	lyLeft_center5->addWidget(groupBoxSortare);
	lyLeft_center5->addWidget(left_center4);

	lyLeft->addWidget(tabel_view);
	lyLeft->addWidget(left_center1);
	lyLeft->addWidget(left_center2);
	lyLeft->addWidget(left_center3);
	lyLeft->addWidget(left_center5);

	lyMain->addWidget(left);

	ly_btn_dy = new QVBoxLayout;
	btn_dyn->setLayout(ly_btn_dy);
	lyMain->addWidget(btn_dyn);

	fereastra_lista->show();

	/// partea de lsita masini spalat





	QWidget* fereastra_masini_spalat = new QWidget;

	//QHBoxLayout* lyMain2 = new QHBoxLayout;
	fereastra_masini_spalat->setLayout(lyMain2);

	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int nr_linii_cos = 10;
	int nr_coloane_cos = 4;
	//tabel_masini_spalat = new QTableWidget{ nr_linii_cos, nr_coloane_cos };

	//QStringList HeaderTabelCos;
	//HeaderTabelCos << "Numar inmatriculare" << "Producator" << "Model" << "Tip";
	//tabel_masini_spalat->setHorizontalHeaderLabels(HeaderTabelCos);
	//tabel_masini_spalat->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//adaugare formular

	QWidget* formCos = new QWidget;
	QFormLayout* lyFormCos = new QFormLayout;
	formCos->setLayout(lyFormCos);
	editare_numar_inamt = new QLineEdit;
	editare_nuamr_adaugare_elemente = new QLineEdit;
	editare_nume_fisier = new QLineEdit;

	lyFormCos->addRow(lblNrMasiniSpalat, editare_numar_inamt);
	lyFormCos->addRow(lblNumarMasiniDeAdaugatPtSpalat, editare_nuamr_adaugare_elemente);

	lyFormCos->addRow(lblFisierMasiniSpalat, editare_nume_fisier);

	btn_adaugare_masini_spalat = new QPushButton("Adaugare masina in lista masini spalat");
	btn_golire_masini_spalat = new QPushButton("Golire lista masini spalat");
	btn_generare_masini_spalat = new QPushButton("Generare lista masini spalat");
	btn_export_masini_spalat = new QPushButton("Export lista masini spalat");
	btn_exit_lista_masini_spalat = new QPushButton("Exitlista masini spalat");

	QWidget* right_center1 = new QWidget;
	QVBoxLayout* lyRight_center1 = new QVBoxLayout;
	right_center1->setLayout(lyRight_center1);
	lyRight_center1->addWidget(formCos);
	lyRight_center1->addWidget(btn_adaugare_masini_spalat);
	lyRight_center1->addWidget(btn_generare_masini_spalat);
	lyRight_center1->addWidget(btn_golire_masini_spalat);
	lyRight_center1->addWidget(btn_export_masini_spalat);
	lyRight_center1->addWidget(btn_exit_lista_masini_spalat);

	//lyRight->addWidget(tabel_masini_spalat);
	lyRight->addWidget(lista_masini_spalat);
	lyRight->addWidget(right_center1);

	//lyMain2->addWidget(left);
	lyMain2->addWidget(right);

	//fereastra_masini_spalat->show();
	QObject::connect(btn_open_masini_spalat, &QPushButton::clicked, [=]() {
		fereastra_masini_spalat->show();
		
		});
	QObject::connect(btn_exit_lista_masini_spalat, &QPushButton::clicked, [=]() {
		clearMasiniSpalatData();
		fereastra_masini_spalat->close();
		});



}

void My_Gui::conectare_butoane()
{
	QObject::connect(btn_adaugare, &QPushButton::clicked, this, &My_Gui::gui_adaugare);
	QObject::connect(btn_actualizare, &QPushButton::clicked, this, &My_Gui::gui_actualizare);
	QObject::connect(btn_sterge, &QPushButton::clicked, this, &My_Gui::gui_stergere);
	QObject::connect(btn_undo, &QPushButton::clicked, this, &My_Gui::gui_undo);
	QObject::connect(btn_cautare, &QPushButton::clicked, this, &My_Gui::gui_cautare);
	QObject::connect(btn_filtrare_tip, &QPushButton::clicked, this, &My_Gui::gui_filtru_Tip);
	QObject::connect(btn_filtrare_producator, &QPushButton::clicked, this, &My_Gui::gui_filtru_producator);
	QObject::connect(btn_sortare, &QPushButton::clicked, [&]()
		{
			if (radio_sortare_Numar->isChecked())
				incarcare_lista(service_masina.sortByNrInmatirculare());
			if (radio_sortare_Model->isChecked())
				incarcare_lista(service_masina.sortByProducatorSiModel());
			if (radio_sortare_Tip->isChecked())
				incarcare_lista(service_masina.sortByType());
		});
	QObject::connect(btn_adaugare_masini_spalat, &QPushButton::clicked, this, &My_Gui::gui_adaugare_masini_spalat);
	QObject::connect(btn_golire_masini_spalat, &QPushButton::clicked, this, &My_Gui::gui_golire_masini_spalat);
	QObject::connect(btn_generare_masini_spalat, &QPushButton::clicked, this, &My_Gui::gui_generare_masini_spalat);
	QObject::connect(btn_export_masini_spalat, &QPushButton::clicked, this, &My_Gui::gui_export_masini_spalat);
	//QObject::connect(btn_exit_lista_masini_spalat, &QPushButton::clicked, this, &My_Gui::clearMasiniSpalatData);

}

void My_Gui::incarcare_lista(vector<Masina> masini)
{
	/*tabel_masini->clearContents();
	tabel_masini->setRowCount(masini.size());

	int linie = 0;
	for (auto& m : masini)
	{
		tabel_masini->setItem(linie, 0, new QTableWidgetItem(QString::number(m.getNrInmatriculare())));
		tabel_masini->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(m.getProducator())));
		tabel_masini->setItem(linie, 2, new QTableWidgetItem(QString::fromStdString(m.getModel())));
		tabel_masini->setItem(linie, 3, new QTableWidgetItem(QString::fromStdString(m.getTip())));
		linie++;
	}*/
	model->seteazaLocatari(masini);
	adaugaButoane(masini);
}

void My_Gui::incarcare_masini_spalat(vector<Masina> masini_spalat)
{
	tabel_masini_spalat->clearContents();
	tabel_masini_spalat->setRowCount(masini_spalat.size());
	int linie = 0;
	for (auto& m : masini_spalat)
	{
		tabel_masini_spalat->setItem(linie, 0, new QTableWidgetItem(QString::number(m.getNrInmatriculare())));
		tabel_masini_spalat->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(m.getProducator())));
		tabel_masini_spalat->setItem(linie, 2, new QTableWidgetItem(QString::fromStdString(m.getModel())));
		tabel_masini_spalat->setItem(linie, 3, new QTableWidgetItem(QString::fromStdString(m.getTip())));
		linie++;
	}

	tabel_masini_spalat->clear();
	lista_masini_spalat->clear();
	for (auto& m : masini_spalat)
	{
		string masina = to_string(m.getNrInmatriculare()) + " | " + m.getProducator() + " | " + m.getModel() + " | " + m.getTip();
		QListWidgetItem* it = new QListWidgetItem{ QString::fromStdString(masina) };
		lista_masini_spalat->addItem(it);
	}
}

void My_Gui::gui_adaugare()
{
	try
	{
		int numar = editareNumar->text().toInt();
		string producator = editareProducator->text().toStdString();
		string model = editareModel->text().toStdString();
		string tip = editareTip->text().toStdString();

		editareProducator->clear();
		editareNumar->clear();
		editareModel->clear();
		editareTip->clear();

		service_masina.serviceAdaugaMasina(numar, producator, model, tip);
		incarcare_lista(service_masina.getAll());

		QMessageBox::information(this, "info", QString::fromStdString("Masina adaugata cu succes!"));

	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
	catch (ValidateException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
}

void My_Gui::gui_actualizare()
{
	try
	{
		int numar = editareNumar->text().toInt();
		string producator = editareProducator->text().toStdString();
		string model = editareModel->text().toStdString();
		string tip = editareTip->text().toStdString();

		editareProducator->clear();
		editareNumar->clear();
		editareModel->clear();
		editareTip->clear();

		service_masina.serviceModificaMasina(numar, producator, model, tip);
		incarcare_lista(service_masina.getAll());

		QMessageBox::information(this, "info", QString::fromStdString("Masina actualizata cu succes!"));

	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
	catch (ValidateException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
}

void My_Gui::gui_stergere()
{
	try
	{
		int numar = editareNumar->text().toInt();

		editareNumar->clear();

		service_masina.serviceStergeMasina(numar);
		incarcare_lista(service_masina.getAll());

		QMessageBox::information(this, "info", QString::fromStdString("Masina stearsa cu succes!"));

	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
	catch (ValidateException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
}

void My_Gui::gui_undo()
{
	try {
		service_masina.undo();
		incarcare_lista(service_masina.getAll());
		QMessageBox::information(this, "info", QString::fromStdString("Undo efectuat cu succes!"));

	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}

}

void My_Gui::gui_cautare()
{
	try
	{
		int numar = editareNumar->text().toInt();

		editareNumar->clear();
		Masina m = service_masina.cautaEntitate(numar);
		string masina;
		masina = "Numar Inmatriculare:";
		masina.append(to_string(m.getNrInmatriculare()));
		masina.append("; ");
		masina.append("Producator:");
		masina.append(m.getProducator());
		masina.append("; ");
		masina.append("Model:");
		masina.append(m.getModel());
		masina.append("; ");
		masina.append("Tip: ");
		masina.append(m.getTip());
		QMessageBox::information(this, "info", QString::fromStdString(masina));
	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
	catch (ValidateException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
}

void My_Gui::gui_filtru_producator()
{
	string masina;
	string producator = editareProducator->text().toStdString();
	editareProducator->clear();
	QListWidget* lista_auxiliara_masini = new QListWidget;
	vector <Masina> filtrare_producator = service_masina.filtrareProducator(producator);
	if (filtrare_producator.empty())
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString("Nu exista nicio masina de la acest producator"), lista_auxiliara_masini);
	for (auto m : filtrare_producator)
	{
		string masina;
		masina = "Numar Inmatriculare:";
		masina.append(to_string(m.getNrInmatriculare()));
		masina.append("; ");
		masina.append("Producator:");
		masina.append(m.getProducator());
		masina.append("; ");
		masina.append("Model:");
		masina.append(m.getModel());
		masina.append("; ");
		masina.append("Tip: ");
		masina.append(m.getTip());
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(masina), lista_auxiliara_masini);
	}
	lista_auxiliara_masini->show();
}

void My_Gui::gui_filtru_Tip()
{
	string masina;
	string tip = editareTip->text().toStdString();
	editareTip->clear();
	QListWidget* lista_auxiliara_masini = new QListWidget;
	vector <Masina> filtrare_tip = service_masina.filtrareTip(tip);
	if (filtrare_tip.empty())
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString("Nu exista nicio masina de la acest producator"), lista_auxiliara_masini);
	for (auto m : filtrare_tip)
	{
		string masina;
		masina = "Numar Inmatriculare:";
		masina.append(to_string(m.getNrInmatriculare()));
		masina.append("; ");
		masina.append("Producator:");
		masina.append(m.getProducator());
		masina.append("; ");
		masina.append("Model:");
		masina.append(m.getModel());
		masina.append("; ");
		masina.append("Tip: ");
		masina.append(m.getTip());
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(masina), lista_auxiliara_masini);
	}
	lista_auxiliara_masini->show();
}

void My_Gui::adaugaButoane(const std::vector<Masina>& masini)
{

	//sterge
	clearLayout(this->ly_btn_dy);

	//reconstruieste
	std::set <string> tipuri_unice;
	vector<Masina> vec = service_masina.getAll();
	for (size_t i = 0; i < vec.size(); i++)
		tipuri_unice.insert(vec[i].getTip());

	std::set<string>::iterator it;
	butoane_tipuri_masini.clear();
	for (it = tipuri_unice.begin(); it != tipuri_unice.end(); ++it) {
		QPushButton* ctr = new QPushButton(QString::fromStdString(*it));
		butoane_tipuri_masini.push_back(ctr);
	}
	for (auto button : butoane_tipuri_masini) {
		ly_btn_dy->addWidget(button);
	}
	for (auto button : butoane_tipuri_masini) {
		QObject::connect(button, &QPushButton::clicked, this, &My_Gui::optiune);
	}
}

void My_Gui::optiune()
{
	try {
		QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // se retine butonul apasat
		QString buttonText = buttonSender->text(); // extragere text din buton
		vector <Masina> masini;
		masini = service_masina.getAll();
		vector <Masina> un_singur_gen;
		for (auto& masina : masini)
		{
			if (QString::fromStdString(masina.getTip()) == buttonText)
				un_singur_gen.push_back(masina);
		}
		string mesaj = "Numarul Masinilor de tipul selectat este: ";
		string message = std::to_string(un_singur_gen.size());
		mesaj.append(message);
		QMessageBox::information(this, "Info", QString::fromStdString(mesaj));
	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
	catch (ValidateException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
}

void My_Gui::gui_adaugare_masini_spalat()
{
	try
	{
		int numar = editare_numar_inamt->text().toInt();

		editare_numar_inamt->clear();

		service_masina.addToLista(numar);
		incarcare_masini_spalat(service_masina.getAllServiceMasiniSpalat());

		QMessageBox::information(this, "info", QString::fromStdString("Masina a fost adaugata in Lista cu masini pentru spalat cu succes!"));

	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
	catch (ValidateException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
}

void My_Gui::gui_generare_masini_spalat()
{
	try
	{
		int nr = editare_nuamr_adaugare_elemente->text().toInt();
		editare_nuamr_adaugare_elemente->clear();
		/*if (nr > service_masina.getAll().size())
			QMessageBox::warning(this, "warning", QString::fromStdString("Numarul depaseste lungimea listei!"));*/
		/*else
		{*/
			service_masina.addRandom(nr);
			incarcare_masini_spalat(service_masina.getAllServiceMasiniSpalat());
			QMessageBox::information(this, "info", QString::fromStdString("Lista de Masini pentru spalat a fost generat cu succes!"));
		//}
	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
}

void My_Gui::gui_golire_masini_spalat()
{
	try
	{
		service_masina.golesteLista();
		incarcare_masini_spalat(service_masina.getAllServiceMasiniSpalat());

		QMessageBox::information(this, "info", QString::fromStdString("Lista de masini pentru spalat  a fost golita cu succes!"));

	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
}

void My_Gui::gui_export_masini_spalat()
{
	try
	{
		string nume_fisier = editare_nume_fisier->text().toStdString();
		editare_nume_fisier->clear();

		service_masina.exportaListaCVS(nume_fisier);
		QMessageBox::information(this, "info", QString::fromStdString("Lista cu masini pentru spalat a fost exportat cu succes!"));
	}
	catch (MasinaRepoException& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMsg()));
	}
}

void My_Gui::clearMasiniSpalatData() {
	// Clear any data stored in lista_masini_spalat or tabel_masini_spalat
	lista_masini_spalat->clear();
	service_masina.golesteLista();
	// Clear any other data structures or widgets containing data in fereastra_masini_spalat
}