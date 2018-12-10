#include"calc.h"
#include"exceptions.h"

double calculator::get_var(const string& name) {
	if (variables.count(name) == 0) throw context_variables_exception();
	return variables[name];
	
}
void calculator::set_var(const string& name, double value) {
	variables[name] = value;
}
double calculator::pop() {
	if (stack.empty()) throw context_stack_exception();
	double val = stack.top();
	stack.pop();
	return val;
}
void calculator::push(double val) {
	stack.push(val);
}
double calculator::top() {
	if (stack.empty()) throw context_stack_exception();
	return stack.top();
}
void calculator::reset() {
	while (!stack.empty()) stack.pop();
	variables.clear();
}