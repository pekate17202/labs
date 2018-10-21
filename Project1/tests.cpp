#include<gtest/gtest.h>
#include "rna.h"
TEST(test_rna, capacity)
{
	RNA rna(A, 1000);
	// length of internal array
	size_t allocLength = rna.capacity();
	ASSERT_GE(allocLength, 1000 * 2 / 8 / sizeof(size_t)) << allocLength << " < 1000 * 2 / 8 / sizeof(uint)";
	ASSERT_LT(allocLength, 1000 * 2 / 8 / sizeof(size_t) + 2) << allocLength << " > 1000 * 2 / 8 / sizeof(uint) + 2";
	//ASSERT_EQ(1, 1) << "1 is not equal 0";
}

TEST(test_rna, cardinality){
	RNA rna(A, 100);
	rna[1] = rna[3] = rna[8] = T;
	ASSERT_EQ(rna.cardinality(A), 100-3) << "unexpected count of A";
	ASSERT_EQ(rna.cardinality(T), 3) << "unexpected count of T";
}

TEST(test_rna, map_cardinality) {
	RNA rna(A, 100);
	rna[1] = rna[3] = rna[8] = T;
	unordered_map< Nucleotide, int, std::hash<int> > map = rna.cardinality();
	ASSERT_EQ(map[A], 100 - 3) << "unexpected count of A";
	ASSERT_EQ(map[T], 3) << "unexpected count of T";
	ASSERT_EQ(map[G], 0) << "unexpected count of G";
}

TEST(test_rna, operator_plus) {
	RNA rna1(A, 100);
	RNA rna2(G, 80);
	RNA rna = rna1 + rna2;
	ASSERT_EQ(rna[3], A) << "invalid first rna";
	ASSERT_EQ(rna[105], G) << "invalid second rna";
	ASSERT_EQ(rna.last_nucl_index(), 180) << "invalid nucl_number";
}