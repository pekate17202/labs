#include "calc.h"
#include "gtest/gtest.h"
#include "commands.h"
#include <iostream>
#include <sstream>

//#include<gtest/gtest.h>
//using namespace std;
int main(int argc, char **argv) {
	if (argc > 1 && strcmp(argv[1],"T") == 0)
	{
		::testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();
	}
	else {
		calculator calc;
		command_creator::registrer_creator(new comment_creator());
		command_creator::registrer_creator(new define_creator());
		command_creator::registrer_creator(new push_creator());
		command_creator::registrer_creator(new pop_creator());
		command_creator::registrer_creator(new print_creator());
		command_creator::registrer_creator(new plus_creator());
		command_creator::registrer_creator(new minus_creator());
		command_creator::registrer_creator(new mul_creator());
		command_creator::registrer_creator(new div_creator());
		command_creator::registrer_creator(new sqrt_creator());
		string cmd_str;
		while (getline(cin, cmd_str) && cmd_str.compare("QUIT") != 0) {
			try {
				command* cmd = command_creator::create_command(cmd_str);
				if (cmd != nullptr) {
					cmd->exec(&calc);
					delete cmd;
				}
			}
			catch (exception& ex) {
				cout << ex.what() << endl;
			}
		}
		/*MEMLEAKS_leaks = 0;
		
		cout << "memory leaks: " << MEMLEAKS_leaks << "\n";*/
		return 0;
	}
	
}