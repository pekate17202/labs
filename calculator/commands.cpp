#include "commands.h"
#include "exceptions.h"
#include <iostream>
#include <sstream>

comment_command::comment_command() {
	//text = cmd;
}
void comment_command::exec(context * ctx)
{
	//cout << text << endl;
}

command * comment_creator::create(vector<string> cmd_parts)
{
	return new comment_command();
}

const string comment_creator::name()
{
	return "#";
}

define_command::define_command(string name, double value)
{
	this->name = name;
	this->value = value;
}

void define_command::exec(context * ctx)
{
	ctx->set_var(name, value);
}

command * define_creator::create(vector<string> cmd_parts)
{
	if (cmd_parts.size() != 3) throw command_format_exception();
	string name = cmd_parts[1];
	double value;
	try {
		value = stod(cmd_parts[2]);
	}
	catch (exception& ex) {
		throw command_format_exception();
	}
	return new define_command(name, value);
}

const string define_creator::name()
{
	return "DEFINE";
}

push_command::push_command(string value)
{
	this->value = value;
}

void push_command::exec(context * ctx)
{
	double val;
	try {
		val = ctx->get_var(value);
	}
	catch (exception& ex) {
		try {
			val = stod(value);
		}
		catch (exception& ex) {
			throw context_variables_exception();
		}
	}
	ctx->push(val);
}

command * push_creator::create(vector<string> cmd_parts)
{
	if (cmd_parts.size() != 2) throw command_format_exception();
	return new push_command(cmd_parts[1]);
}

const string push_creator::name()
{
	return "PUSH";
}

command * pop_creator::create(vector<string> cmd_parts)
{
	if (cmd_parts.size() != 1) throw command_format_exception();
	return new pop_command();
}

const string pop_creator::name()
{
	return "POP";
}

void pop_command::exec(context * ctx)
{
	ctx->pop();
}

void print_command::exec(context * ctx)
{
	cout << ctx->top() << endl;
}

command * print_creator::create(vector<string> cmd_parts)
{
	if (cmd_parts.size() != 1) throw command_format_exception();
	return new print_command();
}

const string print_creator::name()
{
	return "PRINT";
}

void plus_command::exec(context * ctx)
{
	double val1 = ctx->pop();
	double val2 = ctx->pop();
	ctx->push(val1 + val2);
}

command * plus_creator::create(vector<string> cmd_parts)
{
	if (cmd_parts.size() != 1) throw command_format_exception();
	return new plus_command();
}

const string plus_creator::name()
{
	return "+";
}

void minus_command::exec(context * ctx)
{
	double val1 = ctx->pop();
	double val2 = ctx->pop();
	ctx->push(val2 - val1);
}

command * minus_creator::create(vector<string> cmd_parts)
{
	if (cmd_parts.size() != 1) throw command_format_exception();
	return new minus_command();
}

const string minus_creator::name()
{
	return "-";
}

void mul_command::exec(context * ctx)
{
	double val1 = ctx->pop();
	double val2 = ctx->pop();
	ctx->push(val1*val2);
}

command * mul_creator::create(vector<string> cmd_parts)
{
	if (cmd_parts.size() != 1) throw command_format_exception();
	return new mul_command();
}

const string mul_creator::name()
{
	return "*";
}

void div_command::exec(context * ctx)
{
	double val1 = ctx->top();
	if (val1 == 0) {
		throw command_exec_exception();
	}
	ctx->pop();
	double val2 = ctx->pop();
	ctx->push(val2/val1);
}

command * div_creator::create(vector<string> cmd_parts)
{
	if (cmd_parts.size() != 1) throw command_format_exception();
	return new div_command();
}

const string div_creator::name()
{
	return "/";
}

void sqrt_command::exec(context * ctx)
{
	double val = ctx->pop();
	ctx->push(sqrt(val));
}

command * sqrt_creator::create(vector<string> cmd_parts)
{
	if (cmd_parts.size() != 1) throw command_format_exception();
	return new sqrt_command();
}

const string sqrt_creator::name()
{
	return "SQRT";
}
