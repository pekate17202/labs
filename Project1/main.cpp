#include "memleaks.h"
#include "rna.h"
#include "dna.h"
#include <iostream>
#include<gtest/gtest.h>
//using namespace std;
int main(int argc, char **argv) {
	MEMLEAKS_leaks = 0;
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	cout << "memory leaks: " << MEMLEAKS_leaks<<"\n";
	char k;
	cin >> k;
	return 0;
}
/*int main() {

	RNA rna(Nucleotide::G, 100);
	cout << rna.capacity() << " " << rna[3] << "\n";
	rna[50] = C;
	rna[100] = A;
	cout << rna[50] << " " << rna[rna.last_nucl_index()] << "\n";
	rna[1] = rna[5] = rna[10] = T;
	cout << rna[1] << " " << rna[5] << " " << rna[10] << "\n";
	rna.trim(3);
	cout << rna[0] << " " << rna[1] << " " << rna[2] << " " << rna.capacity() << "\n";
	char k;
	cin >> k;
}*/