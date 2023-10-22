#ifndef __PASSENGER__H
#define __PASSENGER__H
#include "Base_class.h"
class Passenger : public Base_class {
private:
	int destination_floor;//���� ����������
public:
	Passenger(Base_class* p_head_object, string s_object_name);//�����������
	void Signal_condition(string& message);//������ ������ ���������
	void Signal_coming_to_the_floor(string& inform);//������ ������� ��������� �� ����
	void Signal_control_panel(string& destination_floor);//������ �� ������ ���������� � ������ ��������� ������
	void Handler_coming_to_the_floor(string& message);
	void Handler_condition(string& s);
	void Handler_control_panel(string& s);
	int get_des_floor();
};
#endif