#pragma once
#include <QWidget.h>
#include "ListaMasiniSpalat.h"
#include "QtWidgetsApplication9.h"
#include <QListWidget.h>
#include <QLayout.h>
#include <QtWidgets/QApplication>
#include <qwidget.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include "Observer.h"
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

class ListaGUI : public QWidget,public Observer {
private:
	MasiniPentruSapalat& data;
	ServiceMasina& s;
	void initGUIcmps();

	void connectSignalsSlots();
	void reloadList(const std::vector<Masina>& masini);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	QListWidget* lst = new QListWidget;

	QPushButton* btn_adaugare_masini_spalat = new QPushButton("Adaugare masina in lista masini spalat");
	QPushButton* btn_golire_masini_spalat=new QPushButton("Golire lista masini spalat");
	QPushButton* btn_generare_masini_spalat= new QPushButton("Generare lista masini spalat");
	QPushButton* btn_export_masini_spalat= new QPushButton("Export lista masini spalat");
	QPushButton* btn_exit_lista_masini_spalat= new QPushButton("Exitlista masini spalat");

	QLabel* lblNrMasiniSpalat = new QLabel{ "Numar Inmatriculare: " };
	QLabel* lblNumarMasiniDeAdaugatPtSpalat = new QLabel{ "Numar de masini de adaugat: " };
	QLabel* lblFisierMasiniSpalat = new QLabel{ "Fisier: " };
	QLineEdit* editare_numar_inamt;
	QLineEdit* editare_nuamr_adaugare_elemente;
	QLineEdit* editare_nume_fisier;

	void update()override {
		reloadList(data.lista());
	}

public:
	ListaGUI(MasiniPentruSapalat& s, ServiceMasina& j) : data{ s }, s{j} {
		s.addObserver(this);
		initGUIcmps();
		connectSignalsSlots();
		reloadList(data.lista());
	}
};