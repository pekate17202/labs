#include "exceptions.h"

const char * command_format_exception::what() const throw()
{
	return "Invalid command format";
}

const char * command_exec_exception::what() const throw()
{
	return "Command execute error";
}

const char * command_unknown_exception::what() const throw()
{
	return "Unknown command";
}

const char * context_variables_exception::what() const throw()
{
	return "Unknown variable";
}

const char * context_stack_exception::what() const throw()
{
	return "Invalid stack";
}

