#pragma once
#include <string>
#include "domeniu.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	string msgs;
public:
	ValidateException(const string errors) :msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
	string getMsg() { return this->msgs; }
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class ValidatorMasina {
public:
	void validate(const Masina& p);
};

void testValidator(); 