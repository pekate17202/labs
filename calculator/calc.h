#pragma once
#include "interfaces.h"
#include<map>
#include<stack>
class calculator:public context {
private:
	map<string, double> variables;
	stack<double> stack;
	map<string, command_creator*> *command_creators;
public:
	calculator(map<string, command_creator*>*);
	virtual double get_var(const string& name);
	virtual void set_var(const string& name, double value);
	virtual void pop();
	virtual void push(double);
	virtual double top();
	virtual void reset();
};