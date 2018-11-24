#include<gtest/gtest.h>
#include "rna.h"
TEST(test_rna, capacity){
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

TEST(test_rna, trim) {
	RNA rna(A, 100);
	rna.trim(88);
	ASSERT_EQ(rna.last_nucl_index(), 88) << "invalid last nucleotide";
}

TEST(test_rna, operator_plus) {
	RNA rna1(A, 100);
	RNA rna2(G, 80);
	RNA rna = rna1 + rna2;
	ASSERT_EQ(rna[3], A) << "invalid first rna";
	ASSERT_EQ(rna[105], G) << "invalid second rna";
	ASSERT_EQ(rna.last_nucl_index(), 180) << "invalid nucl_number";
}

TEST(test_rna, operator_is_equal) {
	RNA rna1(A, 100);
	RNA rna2(A, 100);
	RNA rna3(A, 101);
	RNA rna4 = rna1;
	rna4.push_back(C);
	ASSERT_EQ(rna1 == rna2, true) << "invalid comparing";
	ASSERT_EQ(rna1 == rna3, false) << "unexpected equal";
	ASSERT_EQ(rna4 == rna3, false) << "unexpected equal last nucleotides";
}

TEST(test_rna, operator_is_not_equal) {
	RNA rna1(A, 100);
	RNA rna2(A, 101);
	RNA rna3 = rna1;
	rna3.push_back(C);
	ASSERT_EQ(rna1 != rna2, true) << "invalid comparing";
	ASSERT_EQ(rna2 != rna3, true) << "invalid comparing";
	ASSERT_EQ(rna2 != rna2, false) << "unexpected not equal";
}

TEST(test_rna, push_back) {
	RNA rna(A, 100);
	rna.push_back(G);
	rna[101];
	ASSERT_EQ(rna[101], G) << "invalid last nucleotide";
}

TEST(test_rna, operator_is_complimentary) {
	RNA rna1(A, 100);
	RNA rna2(T, 100);
	RNA rna3(A, 99);
	RNA rna4 = rna3;
	rna4.push_back(C);
	ASSERT_EQ(rna1.is_ñomplementary(rna2), true) << "unexpected uncomplimentary";
	ASSERT_EQ(rna2.is_ñomplementary(rna3), false) << "unexpected complimentary RNAs with differen lengths";
	ASSERT_EQ(rna2.is_ñomplementary(rna3), false) << "unexpected complimentary";
}

TEST(test_rna, operator_split) {
	two_rna t;
	RNA rna1(A, 100);
	rna1[43] = C;
	t = rna1.split(43);
	ASSERT_EQ(t.rna1->last_nucl_index(), 43) << "invalid number of nucleotides in rna1";
	ASSERT_EQ(t.rna2->last_nucl_index(), 57) << "invalid number of nucleotides in rna2";
	ASSERT_EQ((*t.rna1)[0], rna1[0]) << "invalid nucleotide in rna1";
	ASSERT_EQ((*t.rna2)[0], rna1[43]) << "invalid nucleotide in rna2";
	delete t.rna1;
	delete t.rna2;
}
