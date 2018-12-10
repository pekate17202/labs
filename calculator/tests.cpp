#include<gtest/gtest.h>
#include "calc.h"
#include "commands.h"
#include"exceptions.h"
struct test_calc : public testing::Test {
	calculator calc;
	test_calc() {
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
	}
	~test_calc() {}
};
TEST_F(test_calc, PUSH) {
	command* cmd = command_creator::create_command("PUSH 15");
	if (cmd != nullptr) cmd->exec(&calc);
	ASSERT_EQ(15, calc.top()) << calc.top() << " != 15";
}
TEST_F(test_calc, POP) {
	vector<string> cmds = { "PUSH 11", "PUSH 43", "POP" };
	for (int i = 0; i < cmds.size(); i++) {
		command* cmd = command_creator::create_command(cmds[i]);
		cmd->exec(&calc);
		delete cmd;
	}
	ASSERT_EQ(11, calc.top()) << calc.top() << " != 11";
}
TEST_F(test_calc, DEFINE) {
	vector<string> cmds = { "DEFINE a 77", "PUSH a"};
	for (int i = 0; i < cmds.size(); i++) {
		command* cmd = command_creator::create_command(cmds[i]);
		cmd->exec(&calc);
		delete cmd;
	}
	ASSERT_EQ(77, calc.top()) << calc.top() << " != 77";
}
TEST_F(test_calc, PLUS) {
	vector<string> cmds = { "PUSH 77", "PUSH 2", "+" };
	for (int i = 0; i < cmds.size(); i++) {
		command* cmd = command_creator::create_command(cmds[i]);
		cmd->exec(&calc);
		delete cmd;
	}
	ASSERT_EQ(79, calc.top()) << calc.top() << " != 79";
}
TEST_F(test_calc, MINUS) {
	vector<string> cmds = { "PUSH 77", "PUSH 2", "-" };
	for (int i = 0; i < cmds.size(); i++) {
		command* cmd = command_creator::create_command(cmds[i]);
		cmd->exec(&calc);
		delete cmd;
	}
	ASSERT_EQ(75, calc.top()) << calc.top() << " != 75";
}
TEST_F(test_calc, COMMENT) {
	vector<string> cmds = { "PUSH 345", "# PUSH 43",};
	for (int i = 0; i < cmds.size(); i++) {
		command* cmd = command_creator::create_command(cmds[i]);
		cmd->exec(&calc);
		delete cmd;
	}
	ASSERT_EQ(345, calc.top()) << calc.top() << " != 345";
}
TEST_F(test_calc, POPEX) {
	vector<string> cmds = { "POP" };
	try {
		for (int i = 0; i < cmds.size(); i++) {
			command* cmd = command_creator::create_command(cmds[i]);
			cmd->exec(&calc);
			delete cmd;
		}
		FAIL() << "Expected context_stack_exception";
	}
	catch (context_stack_exception const & err) {}
	catch (...) {
		FAIL() << "Expected context_stack_exception";
	}
}