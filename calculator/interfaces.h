#pragma once
#include<string>
#include<map>
#include<vector>
using namespace std;
class context {
public:
	virtual double get_var(const string& name)=0;
	virtual void set_var(const string& name, double value)=0;
	virtual double pop()=0;
	virtual void push(double)=0;
	virtual double top()=0;
	virtual void reset()=0;
};

class command {
public:
	virtual void exec(context*)=0;
};

class command_creator{
	static map<string, command_creator*> command_creators;
public:
	static void registrer_creator(command_creator* new_creator);
	static command* create_command(string command_str);
	virtual command* create(vector<string> cmd_parts) = 0;
	virtual const string name() = 0;
};