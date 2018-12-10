#pragma once
#include<exception>
using namespace std;
class command_exception : public exception
{
	virtual const char* what() const throw() = 0;
};

class context_exception : public exception
{
	virtual const char* what() const throw() = 0;
};

class command_format_exception : public command_exception
{
	virtual const char* what() const throw();
};

class command_exec_exception : public command_exception
{
	virtual const char* what() const throw();
};

class command_unknown_exception : public command_exception
{
	virtual const char* what() const throw();
};

class context_stack_exception : public context_exception
{
	virtual const char* what() const throw();
};

class context_variables_exception : public context_exception
{
	virtual const char* what() const throw();
};
