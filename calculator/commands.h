#pragma once
#include "interfaces.h"
#include <string>
#include <vector>

using namespace std;

class comment_command : public command {
private:
	string text;
public:
	comment_command();
	virtual void exec(context* ctx);
};

class comment_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};

class define_command : public command {
private:
	string name;
	double value;
public:
	define_command(string name, double value);
	virtual void exec(context* ctx);
};

class define_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};

class push_command : public command{
private:
	string value;
public:
	push_command(string value);
	virtual void exec(context* ctx);
};

class push_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};

class pop_command : public command{
public:
	pop_command() = default;
	virtual void exec(context* ctx);
};

class pop_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};

class print_command : public command {
public:
	print_command() = default;
	virtual void exec(context* ctx);
};

class print_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};

class plus_command : public command {
public:
	plus_command() = default;
	virtual void exec(context* ctx);
};

class plus_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};

class minus_command : public command {
public:
	minus_command() = default;
	virtual void exec(context* ctx);
};

class minus_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};

class mul_command : public command {
public:
	mul_command() = default;
	virtual void exec(context* ctx);
};

class mul_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};

class div_command : public command {
public:
	div_command() = default;
	virtual void exec(context* ctx);
};

class div_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};

class sqrt_command : public command {
public:
	sqrt_command() = default;
	virtual void exec(context* ctx);
};

class sqrt_creator : public command_creator {
public:
	virtual command* create(vector<string> cmd_parts);
	virtual const string name();
};