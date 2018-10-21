#include "rna.h"
#include <iostream>
using namespace std;
int main() {
	RNA rna(Nucleotide::G, 100);
	cout << rna.capacity() << " " << Nucleotide(rna[3]) << "\n";
	rna[50] = C;
	cout << Nucleotide(rna[50]);
	char k;
	cin >> k;
}