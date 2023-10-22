#ifndef APP_CLASS_H
#define APP_CLASS_H

#include "App_class.h"
#include "Elevator.h"
#include "Floor.h"

class App_class : public Base_class {
private:
	int floors;//���������� ������
	int time = 0;//���� �������

public:
	App_class(Base_class* p_head_object);//�����������

	void bild_tree_objects();//����� ���������� ������
	int exec_app();//����� ������� �������

	void Handler_construct_sistem(string& s_command);//���������� ��� ���������� ������ ��������

	void Handler_exec_sistem(string& s_command);//���������� ������� �������, ������������ �������

	void Signal_sistem(string& s_command);//������ ��� ��������� ���������� ��� ������ �������

	void Signal_condition(string& message);//������ ������ ���������

	void Signal_not_found_passenger(string& message);//������ ������������ ���������, ���������� ���� �������� � ������� �� ��� ������

	void Signal_from_floors(string& s_command);//������ �������� ������ �� ���������� ������ "�����" ��� "����"

	void Signal_on_input(string& s_command);//������ ������� ������ �� ����

	void Signal_for_condition_elevator(string& s_command);//������ ����� � ������ ���������

	void Signal_for_condition_floor(string& s_command);//������ ������ � ������ ���������

	void Signal_for_condition_passenger(string& s_command);//������ ���������� � ������ ���������

	void change_name_objects();//����� ��������� ��� �������� ����� ������� ������

	void Signal_elevator_exit(string& s);
	void Signal_elevator_enter(string& s);
	void Signal_elevator_move(string& s);

	void Signal_passenger_coming(string& s);

	void Signal_to_control_panel(string& s);

	void Handler_from_elevator(string& s);
};

#endif