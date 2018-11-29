#pragma once
#include<string>
using namespace std;
class context {
public:
	virtual double get_var(const string& name)=0;
	virtual void set_var(const string& name, double value)=0;
	virtual void pop()=0;
	virtual void push(double)=0;
	virtual double top()=0;
	virtual void reset()=0;
};

class command {
public:
	virtual void exec(context*)=0;
};

class command_creator{
public:
	virtual command* create(string name)=0;
};