#pragma once
#include<stdlib.h>
#include<iostream>
using namespace std;
//struct MEMLEAKS {
//	static int leaks;
//};

int MEMLEAKS_leaks = 0;

void* operator new(size_t size) {
	MEMLEAKS_leaks += 1;
	void* p = malloc(size);
	cout << "new " << size << " " << hex << p<<"\n";
	return p;
}

//void* operator new[](size_t size) {
//	MEMLEAKS::leaks += 1;
//	return malloc(size);
//}

void operator delete(void* p) {
	MEMLEAKS_leaks -= 1;
	cout << "delete " << " " << hex << p <<" "<< MEMLEAKS_leaks <<"\n";
	free(p);
}
