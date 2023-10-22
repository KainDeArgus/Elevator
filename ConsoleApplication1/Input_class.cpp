#include "Input_class.h"
#include <iostream>

using namespace std;


Input_class::Input_class(Base_class* p_head_object, string s_object_name)
	: Base_class(p_head_object, s_object_name) {}

void Input_class::Signal_input(string& s_command) {
}

void Input_class::Handler_input(string& s_command) {
	getline(cin, s_command);
	emit_signal(SIGNAL_D(Input_class::Signal_input), s_command);
}