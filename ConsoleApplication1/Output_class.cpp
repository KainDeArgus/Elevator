#include "Output_class.h"
#include <iostream>
using namespace std;
Output_class::Output_class(Base_class* p_head_object, string s_object_name)
	: Base_class(p_head_object, s_object_name) {}
void Output_class::Handler_output(string& message) {
	cout << message;
}