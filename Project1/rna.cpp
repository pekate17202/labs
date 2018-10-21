#include "rna.h"
RNA::RNA() {
	length = 0;
	nucl_number = 0;
	ref = reference(0, nucl_array);
}
RNA::RNA(Nucleotide N, size_t num) {
	length = num * 2 / sizeof(size_t) / 8 + 1;
	nucl_number = num;
	nucl_array = new size_t[length];
	for (int i = 0; i < num; i++) {
		(*this)[i] = N;
	}
	ref = reference(0, nucl_array);
}
RNA::~RNA() {
	delete[] nucl_array;
}
RNA::reference::reference(size_t pos, size_t* arr) {
	position = pos;
	rna_nucl_array = arr;
}
RNA::reference::reference(const reference& ref) {
	position = ref.position;
	rna_nucl_array = ref.rna_nucl_array;
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
	size_t val = (rna_nucl_array[i] & (3 << sh)) >> sh;
	return Nucleotide(val);
	//switch (val) {
	//case 0: return Nucleotide::A;
	//case 1: return Nucleotide::C;
	//case 2: return Nucleotide::G;
	//case 3: return Nucleotide::T;
}
RNA::reference& RNA::reference::operator=(Nucleotide  N) {

	size_t i = position * 2 / sizeof(size_t) / 8;
	size_t sh = (position * 2) % (sizeof(size_t) * 8);
	rna_nucl_array[i] = (rna_nucl_array[i] & (~(3 << sh))) | (N << sh);
	return *this;
}
RNA::reference& RNA::reference::operator=(const RNA::reference& ref) {
	//operator=(Nucleotide(ref));
	position = ref.position;
	rna_nucl_array = ref.rna_nucl_array;
	return *this;
}
RNA::RNA(const RNA & rna) {
	length = rna.length;
	nucl_number = rna.nucl_number;
	for (int i = 0; i < length; ++i) {
		nucl_array[i] = rna.nucl_array[i];
	}
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
RNA::reference& RNA::operator[](size_t pos) {
	ref = reference(pos, nucl_array);
	return ref;
}
size_t RNA::cardinality(Nucleotide N) {
	size_t count = 0;
	for (int i = 0; i < nucl_number; i++) {
		if (Nucleotide((*this)[i]) == N) count++;
	}
	return count;
}
void RNA::trim(size_t last_index) {
	for (int i = last_index; i < nucl_number; i++) {
		//
		//
	}
}
size_t RNA::last_nucl_index() {
	return nucl_number;
}
RNA operator+(RNA & r1, RNA & r2) {

}
