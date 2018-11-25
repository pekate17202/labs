#include <iostream>
#include "rna.h"
//int MEMLEAKS(0);
using namespace std;
//two_rna::~two_rna() {
//	if (rna1 != nullptr)
//		delete rna1;
//	if (rna2 != nullptr)
//		delete rna2;
//}
RNA::RNA() {
	length = 0;
	nucl_number = 0;
	//cout << "RNA()\n";
}
RNA::RNA(Nucleotide N, size_t num) {
	length = num * 2 / sizeof(size_t) / 8 + 1;
	nucl_number = num;
	nucl_array = new size_t[length];
	for (size_t i = 0; i < num; i++) {
		(*this)[i] = N;
	}
	//cout << "RNA(Nucleotide, size_t)\n";
}
RNA::~RNA() {
	if (nucl_array != nullptr) delete[] nucl_array;
	//cout << "~RNA\n";
}
RNA::reference::reference(size_t pos, RNA* rna) {
	position = pos;
	r_rna = rna;
	//cout << "reference(size_t, RNA*)\n";
}
RNA::reference::reference(const reference& ref) {
	position = ref.position;
	r_rna = ref.r_rna;
	//cout << "reference(const reference&)\n";
}
/*Nucleotide RNA::reference::value() {
	size_t i = position * 2 / sizeof(size_t) / 8;
	size_t sh = (position * 2) % (sizeof(size_t) * 8);
	size_t val = (rna_nucl_array[i] & (3 >> sh)) << sh;
	switch (val) {
	case 0: return Nucleotide::A;
	case 1: return Nucleotide::C;
	case 2: return Nucleotide::G;
	case 3: return Nucleotide::T;
	}
}*/
RNA::reference::operator Nucleotide () const {
	size_t i = position * 2 / sizeof(size_t) / 8;
	size_t sh = (position * 2) % (sizeof(size_t) * 8);
	size_t val = (r_rna->nucl_array[i] & (3 << sh)) >> sh;
	return Nucleotide(val);
	//switch (val) {
	//case 0: return Nucleotide::A;
	//case 1: return Nucleotide::C;
	//case 2: return Nucleotide::G;
	//case 3: return Nucleotide::T;
}
RNA::reference& RNA::reference::operator=(Nucleotide  N) {
	//cout << "reference[" << position << "]=" << N<< "\n"; 
	size_t i = position * 2 / sizeof(size_t) / 8;
	size_t sh = (position * 2) % (sizeof(size_t) * 8);
	r_rna->nucl_array[i] = (r_rna->nucl_array[i] & (~(3 << sh))) | (N << sh);
	return *this;
}
RNA::reference& RNA::reference::operator=(const RNA::reference& ref) {
	operator=(Nucleotide(ref));
	return *this;
}
RNA::reference::~reference() {
	//cout << "~reference()\n";
}
RNA::RNA(const RNA & rna) {
	length = rna.length;
	nucl_array = new size_t[length];
	nucl_number = rna.nucl_number;
	for (size_t i = 0; i < length; ++i) {
		nucl_array[i] = rna.nucl_array[i];
	}
	//cout << "RNA(const RNA&)\n";
}
RNA& RNA::operator=(const RNA & rna) {
	if (nucl_array != nullptr) delete[] nucl_array;
	length = rna.length;
	nucl_number = rna.nucl_number;
	nucl_array = new size_t[length];
	for (size_t i = 0; i < length; ++i) {
		nucl_array[i] = rna.nucl_array[i];
	}
	return *this;
}
size_t RNA::capacity() {
	return length;
}
RNA::reference RNA::operator[](size_t pos) {
	return reference(pos, this);
}
Nucleotide RNA::operator[](size_t pos) const{
	size_t i = pos * 2 / sizeof(size_t) / 8;
	size_t sh = (pos * 2) % (sizeof(size_t) * 8);
	size_t val = (this->nucl_array[i] & (3 << sh)) >> sh;
	return Nucleotide(val);
}
size_t RNA::cardinality(Nucleotide N) {
	size_t count = 0;
	for (size_t i = 0; i < nucl_number; i++) {
		if ((*this)[i] == N) count++;
	}
	return count;
}
unordered_map< Nucleotide, int, std::hash<int> > RNA::cardinality() {
	unordered_map< Nucleotide, int, std::hash<int> > map;
	for (size_t i = 0; i < nucl_number; i++) {
		Nucleotide N = (*this)[i];
		map[N]++;
	}
	return map;
}
void RNA::trim(size_t last_index) {
	length = last_index * 2 / sizeof(size_t) / 8 + 1;
	nucl_number = last_index;
	size_t * rna_copy = nucl_array;
	nucl_array = new size_t[length];
	memcpy(nucl_array, rna_copy, length * sizeof(size_t));
	delete[] rna_copy;
}
size_t RNA::last_nucl_index() {
	return nucl_number;
}
RNA operator+(RNA & r1, RNA & r2) {
	RNA rna;
	rna.nucl_number = r1.nucl_number + r2.nucl_number;
	rna.length = rna.nucl_number * 2 / sizeof(size_t) / 8 + 1;
	rna.nucl_array = new size_t[rna.length];
	memcpy(rna.nucl_array, r1.nucl_array, r1.length * sizeof(size_t));
	for (size_t i = r1.nucl_number; i < rna.nucl_number; i++) {
		RNA::reference r(i, &r2);
		rna[i] = r2[i- r1.nucl_number];
	}
	return rna;
}
bool operator==(const RNA & r1, const RNA & r2) {
	if (r1.nucl_number != r2.nucl_number)
		return false;
	for (size_t i = 0; i < r1.length; i++) {
		if (r1.nucl_array[i] != r2.nucl_array[i])
			return false;
	}
	int shift = sizeof(size_t)*r1.length - r1.nucl_number * 2;
	if ((r1.nucl_array[r1.length] >> shift) != (r2.nucl_array[r2.length] >> shift))
		return false;
	return true;
}
bool operator!=(const RNA & r1, const RNA & r2) {
	return !(r1 == r2);
}
bool RNA::is_ñomplementary(RNA &r1) {
	if (r1.nucl_number != nucl_number)
		return false;
	for (size_t i = 0; i < r1.length - 1; i++) {
		if (r1.nucl_array[i] != ~nucl_array[i])
			return false;
	}
	int shift = sizeof(size_t)*r1.length - r1.nucl_number * 2;
	if (r1.nucl_array[r1.length] >> shift != nucl_array[r1.length] >> shift)
		return false;
	return true;
}
void RNA::push_back(Nucleotide N) {
	nucl_number += 1;
	length = nucl_number * 2 / sizeof(size_t) / 8 + 1;
	size_t* rna_copy = nucl_array;
	nucl_array = new size_t[length];
	memcpy(nucl_array, rna_copy, length * sizeof(size_t));
	(*this)[nucl_number] = N;
	delete[] rna_copy;
}
Nucleotide RNA::pop_back() {
	Nucleotide N = (*this)[nucl_number];
	nucl_number -= 1;
	length = nucl_number * 2 / sizeof(size_t) / 8 + 1;
	size_t* rna_copy = nucl_array;
	nucl_array = new size_t[length];
	memcpy(nucl_array, rna_copy, length * sizeof(size_t));
	delete[] rna_copy;
	return N;
}
two_rna RNA::split(size_t index) {
	two_rna t;
	t.rna1 = new RNA;
	t.rna2 = new RNA;
	t.rna1->nucl_number = index;
	t.rna2->nucl_number = this->nucl_number - index;
	t.rna1->length = t.rna1->nucl_number * 2 / sizeof(size_t) / 8 + 1;
	t.rna2->length = t.rna2->nucl_number * 2 / sizeof(size_t) / 8 + 1;
	t.rna1->nucl_array = new size_t[t.rna1->length];
	t.rna2->nucl_array = new size_t[t.rna2->length];
	memcpy(t.rna1->nucl_array, this->nucl_array, t.rna1->length * sizeof(size_t));
	for (size_t i = index; i < this->nucl_number; i++) {
		(*t.rna2)[i-index] = (*this)[i];
	}
	return t;
}

RNA RNA::operator!() {
	RNA rna;
	rna.nucl_number = this->nucl_number;
	rna.length = this->length;
	rna.nucl_array = new size_t[rna.length];
	for (size_t i = 0; i < rna.length; i++){
		rna.nucl_array[i] = ~(this->nucl_array[i]);
	}
	return rna;
}

void RNA::resize() {
	size_t length_old = length;
	length = nucl_number * 4 / sizeof(size_t) / 8 + 1;
	size_t* rnacpy = nucl_array;
	nucl_array = new size_t[length];
	memcpy(nucl_array, rnacpy, length_old * sizeof(size_t));
}


