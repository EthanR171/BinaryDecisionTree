/*!	\file	patient.hpp
	\brief	class defition for any given patient sample.
	\author	Ethan Rivers
	\date	2023-11-22
*/
#pragma once
#include <iostream>
#include <vector>

class Patient {

	using patient_list_type = std::vector<Patient>;

	int codeNumber_;
	int clumpThickness_;
	int uniformityOfCellSize_;
	int uniformityOfCellShape_;
	int marginalAdhesion_;
	int singleEpithelialCellSize_;
	int bareNuclei_;
	int blandChromatin_;
	int normalNucleoli_;
	int mitoses_;
	int severity_; // 2(Benign) or 4(Malignant)

public:

	Patient() : codeNumber_(0), clumpThickness_(0), uniformityOfCellSize_(0),
		uniformityOfCellShape_(0), marginalAdhesion_(0), singleEpithelialCellSize_(0),
		bareNuclei_(0), blandChromatin_(0), normalNucleoli_(0), mitoses_(0), severity_(0) {}

	/* for my debugging purposes */
	Patient(int codeNumber, int clumpThickness, int uniformityOfCellSize,
		int uniformityOfCellShape, int marginalAdhesion, int singleEpithelialCellSize,
		int bareNuclei, int blandChromatin, int normalNucleoli, int mitoses, int severity)
		: codeNumber_(codeNumber), clumpThickness_(clumpThickness), uniformityOfCellSize_(uniformityOfCellSize),
		uniformityOfCellShape_(uniformityOfCellShape), marginalAdhesion_(marginalAdhesion), singleEpithelialCellSize_(singleEpithelialCellSize),
		bareNuclei_(bareNuclei), blandChromatin_(blandChromatin), normalNucleoli_(normalNucleoli), mitoses_(mitoses), severity_(severity) {}


	//accessors
	int codenumber() const { return codeNumber_; }
	int clumpthickness() const { return clumpThickness_; }
	int cellsizeunif() const { return uniformityOfCellSize_; }
	int cellshapeunif() const { return uniformityOfCellShape_; }
	int adhesion() const { return marginalAdhesion_; }
	int epithelialcellsize() const { return singleEpithelialCellSize_; }
	int barenuclei() const { return bareNuclei_; }
	int blandchromatin() const { return blandChromatin_; }
	int normalnucleoli() const { return normalNucleoli_; }
	int mitoses() const { return mitoses_; }
	int severity() const { return severity_; }

	//mutators 
	void setcodenumber(int value) { codeNumber_ = value; }
	void setclumpthickness(int value) { clumpThickness_ = value; }
	void setcellsizeunif(int value) { uniformityOfCellSize_ = value; }
	void setcellshapeunif(int value) { uniformityOfCellShape_ = value; }
	void setadhesion(int value) { marginalAdhesion_ = value; }
	void setepithelialcellsize(int value) { singleEpithelialCellSize_ = value; }
	void setbarenuclei(int value) { bareNuclei_ = value; }
	void setblandchromatin(int value) { blandChromatin_ = value; }
	void setnormalnucleoli(int value) { normalNucleoli_ = value; }
	void setmitoses(int value) { mitoses_ = value; }
	void setseverity(int value) { severity_ = value; } //  2(Benign) or 4(Malignant)

	/* will be used to store all the patients from file */
	using PatientList = patient_list_type;

};

/* strem insertion operator that will put back the ? into the file based on my default value of -1 */
std::ostream& operator<<(std::ostream& os, const Patient& p) {
	os << p.codenumber() << ",";
	p.clumpthickness() == -1 ? os << "?," : os << p.clumpthickness() << ",";
	p.cellsizeunif() == -1 ? os << "?," : os << p.cellsizeunif() << ",";
	p.cellshapeunif() == -1 ? os << "?," : os << p.cellshapeunif() << ",";
	p.adhesion() == -1 ? os << "?," : os << p.adhesion() << ",";
	p.epithelialcellsize() == -1 ? os << "?," : os << p.epithelialcellsize() << ",";
	p.barenuclei() == -1 ? os << "?," : os << p.barenuclei() << ",";
	p.blandchromatin() == -1 ? os << "?," : os << p.blandchromatin() << ",";
	p.normalnucleoli() == -1 ? os << "?," : os << p.normalnucleoli() << ",";
	p.mitoses() == -1 ? os << "?," : os << p.mitoses() << ",";
	os << p.severity() << "\n";
	return os;
}

