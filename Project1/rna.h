#pragma once
#include<unordered_map>
using namespace std;
enum Nucleotide
{
	A, C, G, T
};
class RNA;
struct two_rna{
	RNA *rna1 = nullptr;
	RNA *rna2 = nullptr;
	//~two_rna();
};
//namespace my_biology_lib;

class RNA
{
private:
	friend class reference;
	class reference
	{
		size_t position;
		RNA* r_rna;
	public:
		reference(size_t, RNA*);
		reference(const reference&);
		~reference();
		reference & operator=(const reference&);
		reference & operator=(Nucleotide);
		operator Nucleotide () const;
	};
	size_t * nucl_array = nullptr;
	size_t length;
	size_t nucl_number;
public:
	RNA(Nucleotide, size_t);
	RNA();
	~RNA();
	RNA(const RNA & rna);
	RNA& operator=(const RNA & rna);
	size_t capacity();
	reference operator[](size_t pos);
	Nucleotide RNA::operator[](size_t pos) const;
	size_t cardinality(Nucleotide);
	void trim(size_t last_index);
	size_t last_nucl_index();
	unordered_map< Nucleotide, int, std::hash<int> > cardinality();
	friend RNA operator+(RNA & r1, RNA & r2);
	friend bool operator==(const RNA & r1, const RNA & r2);
	friend bool operator!=(const RNA & r1, const RNA & r2);
	void push_back(Nucleotide);
	Nucleotide pop_back();
	bool is_ñomplementary(RNA &);
	two_rna split(size_t index);
	friend two_rna;
	RNA operator!();
	//void resize
	//memory leaks 
};
RNA operator+ (RNA & r1, RNA & r2);
bool operator==(const RNA & r1, const RNA & r2);
bool operator!=(const RNA & r1, const RNA & r2);