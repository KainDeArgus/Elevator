#ifndef __INPUT_CLASS__H
#define __INPUT_CLASS__H
#include "Base_class.h"
class Input_class : public Base_class {
public:
	Input_class(Base_class* p_head_object, string s_object_name);//�����������
	void Signal_input(string& s_command);//���������� ������ �� ����
	void Handler_input(string& s_command);//����� ������� ������� ������
};
#endif