#pragma once
#include "interfaces.h"
#include<map>
#include<stack>
class calculator:public context {
private:
	map<string, double> variables;
	stack<double> stack;
	
public:
	virtual double get_var(const string& name);
	virtual void set_var(const string& name, double value);
	virtual double pop();
	virtual void push(double);
	virtual double top();
	virtual void reset();
};