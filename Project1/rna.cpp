#include <iostream>
#include "rna.h"
using namespace std;
RNA::RNA() {
	length = 0;
	nucl_number = 0;
	cout << "RNA()\n";
}
RNA::RNA(Nucleotide N, size_t num) {
	length = num * 2 / sizeof(size_t) / 8 + 1;
	nucl_number = num;
	nucl_array = new size_t[length];
	for (int i = 0; i < num; i++) {
		(*this)[i] = N;
	}
	cout << "RNA(Nucleotide, size_t)\n";
}
RNA::~RNA() {
	delete[] nucl_array;
	cout << "~RNA\n";
}
RNA::reference::reference(size_t pos, RNA* rna) {
	position = pos;
	r_rna = rna;
	cout << "reference(size_t, RNA*)\n";
}
RNA::reference::reference(const reference& ref) {
	position = ref.position;
	r_rna = ref.r_rna;
	cout << "reference(const reference&)\n";
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
	cout << "reference[" << position << "]=" << N<< "\n"; 
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
	cout << "~reference()\n";
}
RNA::RNA(const RNA & rna) {
	length = rna.length;
	nucl_number = rna.nucl_number;
	for (int i = 0; i < length; ++i) {
		nucl_array[i] = rna.nucl_array[i];
	}
	cout << "RNA(const RNA&)\n";
}
RNA& RNA::operator=(const RNA & rna) {
	delete[] nucl_array;
	length = rna.length;
	nucl_number = rna.nucl_number;
	for (int i = 0; i < length; ++i) {
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
size_t RNA::cardinality(Nucleotide N) {
	size_t count = 0;
	for (int i = 0; i < nucl_number; i++) {
		if ((*this)[i] == N) count++;
	}
	return count;
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
//RNA operator+(RNA & r1, RNA & r2)
