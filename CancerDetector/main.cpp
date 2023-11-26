/*!	\file	main.cpp
	\brief	main application.
	\author	Ethan Rivers
	\date	2023-11-22
*/
#include "binarytree.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
using namespace std;

void loadFromCsv(const string& filename, Patient::PatientList& list) {

	ifstream sourceFile(filename);
	if (!sourceFile) {
		cerr << "Error \"" << filename << "\" not loaded! [\033[31mFAILED\033[0m]"; //red color for cool looks
		exit(EXIT_FAILURE);
	}

	string line;

	while (getline(sourceFile, line)) {
		Patient p;
		stringstream ss(line);
		string columnData;
		int counter{ -1 };

		while (getline(ss, columnData, ',')) {
			++counter;
			switch (counter) {
			case 0:
				p.setcodenumber(stoi(columnData));
				break;
			case 1:
				if (columnData != "?") { p.setclumpthickness(stoi(columnData)); }
				else { p.setclumpthickness(-1); }
				break;
			case 2:
				if (columnData != "?") { p.setcellsizeunif(stoi(columnData)); }
				else { p.setcellsizeunif(-1); }
				break;
			case 3:
				if (columnData != "?") { p.setcellshapeunif(stoi(columnData)); }
				else { p.setcellshapeunif(-1); }
				break;
			case 4:
				if (columnData != "?") { p.setadhesion(stoi(columnData)); }
				else { p.setadhesion(-1); }
				break;
			case 5:
				if (columnData != "?") { p.setepithelialcellsize(stoi(columnData)); }
				else { p.setepithelialcellsize(-1); }
				break;
			case 6:
				if (columnData != "?") { p.setbarenuclei(stoi(columnData)); }
				else { p.setbarenuclei(-1); }
				break;
			case 7:
				if (columnData != "?") { p.setblandchromatin(stoi(columnData)); }
				else { p.setblandchromatin(-1); }
				break;
			case 8:
				if (columnData != "?") { p.setnormalnucleoli(stoi(columnData)); }
				else { p.setnormalnucleoli(-1); }
				break;
			case 9:
				if (columnData != "?") { p.setmitoses(stoi(columnData)); }
				else { p.setmitoses(-1); }
				break;
			case 10:
				p.setseverity(stoi(columnData));
				break;

			} // switch
		} // inner loop

		list.push_back(p);
	} // outer loop



	std::cout << "Patients loaded from '" << filename << "' [\033[32mSUCCESS\033[0m]\n"; //green color for cool looks

	sourceFile.close();
}

/* gets patient counts based on default values contained for invalid patients */
void declassifyInvalid(Patient::PatientList& list, int* iCount, int* bCount, int* mCount) {
	// check if we are dealing with an invalid patient.
	for (auto& p : list) {

		bool isInvalid = false;

		if (p.clumpthickness() == -1) { isInvalid = true; }
		if (p.cellsizeunif() == -1) { isInvalid = true; }
		if (p.cellshapeunif() == -1) { isInvalid = true; }
		if (p.adhesion() == -1) { isInvalid = true; }
		if (p.epithelialcellsize() == -1) { isInvalid = true; }
		if (p.barenuclei() == -1) { isInvalid = true; }
		if (p.blandchromatin() == -1) { isInvalid = true; }
		if (p.normalnucleoli() == -1) { isInvalid = true; }
		if (p.mitoses() == -1) { isInvalid = true; }


		if (isInvalid) {
			p.setseverity(0);
			++(*iCount); // Invalid count
		}
		else {

			if (p.severity() == 2)
				++(*bCount); // Benign count
			else if (p.severity() == 4)
				++(*mCount); // Malignant count
		}

	}
}


void saveToCsv(const string& filename, Patient::PatientList const& list) {
	ofstream ofile(filename);
	if (!ofile) {
		std::cerr << "Error: Could not open \"" << filename << "\" for writing! [\033[31mFAILED\033[0m]\n"; //red for cool looks
		exit(EXIT_FAILURE);
	}

	for (const auto& p : list) 
		ofile << p;
	
	cout << "Patients saved to '" << filename << "' [\033[32mSUCCESS\033[0m]\n";

	ofile.close();
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	BinaryDecisionTree<Patient> dataMiner;
	Patient::PatientList patientList;

	string inputFile = "unformatted_data_v1.0.0.csv";
	string outputFile = "results.csv";

	int benignCount{ 0 }, malignantCount{ 0 }, invalidCount{ 0 };

	loadFromCsv(inputFile, patientList);

	/* process each patient through decision tree */
	for (auto& p : patientList) {
		int i = dataMiner.getTypeOfCancer(p);
		p.setseverity(i);
	}

	declassifyInvalid(patientList, &invalidCount, &benignCount, &malignantCount);

	saveToCsv(outputFile, patientList);


	cout << "Total patients processed: " << patientList.size() << endl;
	cout << "Total Benign: " << benignCount << endl;
	cout << "Total Malignant: " << malignantCount << endl;
	cout << "Total Invalid: " << invalidCount << endl;

}