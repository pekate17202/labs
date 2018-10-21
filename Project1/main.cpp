#include "rna.h"
#include <iostream>
using namespace std;
int main() {
	RNA rna(Nucleotide::G, 100);
	cout << rna.capacity() << " " << Nucleotide(rna[3]) << "\n";
	rna[50] = C;
	rna[100] = A;
	cout << Nucleotide(rna[50])<<" "<<Nucleotide(rna[rna.last_nucl_index()]);
	char k;
	cin >> k;
}