#include "interfaces.h"
#include "exceptions.h"
#include <iostream>
#include <sstream>

map<string, command_creator*> command_creator::command_creators = map<string, command_creator*>();

void command_creator::registrer_creator(command_creator * new_creator)
{
	command_creator::command_creators[new_creator->name()] = new_creator;
}

command * command_creator::create_command(string command_str)
{
	istringstream istr(command_str);
	string cmd_part;
	vector<string> cmd_parts;
	while (getline(istr, cmd_part, ' ')) {
		cmd_parts.push_back(cmd_part);
	}
	if (command_creators.count(cmd_parts[0]) > 0) {
		return command_creators[cmd_parts[0]]->create(cmd_parts);
	}
	else {
		throw command_unknown_exception();
	}
}
