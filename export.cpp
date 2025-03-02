#include "export.h"

void exportToCVS(const std::string& fName, const std::vector<Masina>& pets) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {
		throw MasinaRepoException("Unable to open file ");
	}
	for (const auto& p : pets) {
		out << p.getNrInmatriculare() << ",";
		out << p.getProducator() << ",";
		out << p.getModel() << ",";
		out << p.getTip() << std::endl;
	}
	out.close();
}

void exportToHTML(const std::string& fName, const std::vector<Masina>& pets)
{
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {
		throw MasinaRepoException("Unable to open file:" + fName);
	}
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& p : pets) {
		out << "<tr>" << std::endl;
		out << "<td>" << p.getNrInmatriculare() << "</td>" << std::endl;
		out << "<td>" << p.getProducator() << "</td>" << std::endl;
		out << "<td>" << p.getModel() << "</td>" << std::endl;
		out << "<td>" << p.getTip() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}
