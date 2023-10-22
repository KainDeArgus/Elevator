#ifndef __FLOOR__H
#define __FLOOR__H
#include "Base_class.h"
class Floor : public Base_class {
private:
	vector <string> up_queue;//��� �����, ������� � ������� "�����"
	vector <string> down_queue;//��� �����, ������� � ������� "����"
	bool up_button = false;
	bool down_button = false;
public:
	Floor(Base_class* p_head_object, string s_object_name);//�����������
	void Signal_condition(string& message);//������ ������ ���������
	void Signal_enter_passenger(string& direction_elevator);//������ ����� ���������
	void Handler_passengers(string& dir);//���������� ���������� � �������� ������ ����������
	void Handler_enter_passenger(string& s);
	void Handler_condition(string& s_command); int get_count_up_people();//�����, ������� ���������� ���������� ����� �� ����� � ������������ "�����"
	int get_count_down_people();//�����, ������� ���������� ���������� ����� �� ����� � ������������ "����"
	bool get_up_button();
	bool get_down_button();
};
#endif