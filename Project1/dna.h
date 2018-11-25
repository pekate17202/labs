#pragma once
#include "rna.h"

class DNA {
private:
	RNA chain1;
	RNA chain2;
public:
	DNA(RNA& rna1, RNA& rna2) {
		chain1 = rna1;
		chain2 = rna2;
	}
	RNA& get_first() {
		return chain1;
	}
	RNA& get_second() {
		return chain2;
	}
};