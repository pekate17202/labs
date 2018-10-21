#pragma once

enum Nucleotide
{
	A, C, G, T
};

//namespace my_biology_lib;

class RNA
{
private:
	class reference
	{
		size_t position;
		size_t * rna_nucl_array;
	public:
		reference() { position = 0; rna_nucl_array = nullptr; };
		reference(size_t, size_t*);
		reference (const reference&);
		reference & operator=(const reference&);
		reference & operator=(Nucleotide);
		explicit operator Nucleotide () const;
	};
	size_t * nucl_array = nullptr;
	size_t length;
	size_t nucl_number;
	reference  ref;
public:
	RNA(Nucleotide, size_t);
	RNA();
	~RNA();
	RNA(const RNA & rna);
	RNA& operator=(const RNA & rna);
	size_t capacity();
	reference& operator[](size_t pos);
	size_t cardinality(Nucleotide);
	void trim(size_t last_index);
	size_t last_nucl_index();
	RNA operator+ (const RNA & r1, const RNA & r2);
};