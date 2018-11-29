#include"calc.h"
calculator::calculator(map<string, command_creator*>* com_cr){
	command_creators = com_cr;
}
double calculator::get_var(const string& name) {
	return variables[name];
	
}

void calculator::set_var(const string& name, double value) {
	variables[name] = value;
}
void calculator::pop() {
	stack.pop();
}
void calculator::push(double val) {
	stack.push(val);
}
double calculator::top() {
	return stack.top();
}
void calculator::reset() {
	//stack.clear();
	variables.clear();
}