#ifndef __ELEVATOR__H
#define __ELEVATOR__H

#include "Floor.h"

class Elevator : public Base_class {
private:
	int level_now = 1;//�������(����), �� ������� ��������� ����
	int level_max = 1;//�������(����) - ���������� �����
	int capacity;//����������� �����
	int people;//���������� ����� � ����� � ������ ������
	int direction = stop;//����������� �������� �����
	bool reverse_direction = false;//������ �������� �������� �����, ����� ���� ���� ���� ���������� ����� � �������� �� 
	//������ �������� ������� ���� � ��������
	bool stop_for_passenger = false;//���� ���������� ��� ���������� ����������
public:

	Elevator(Base_class* p_head_object, string s_object_name);//�����������

	enum directions {//������������ ��������� ����������� �������� �����
		stop = 0, up = 1, down = -1
	};

	void Signal_condition(string& message);//������ ������ ���������

	void Handler_from_control_panel(string destination_floor);//���������� �������� � ������ ����������

	void Handler_passengers(string& destination_floor);//���������� �������� � ������ "�����"-"����" �� ������

	void Handler_enter_passenger(string fio);//���������� ����� ����������

	void Handler_condition(string s_command);

	int get_level();//������ ������

	void set_capacity(int capacity);//������ �����������

	int get_people();//������ ���������� ����� � �����

	int get_direction();//������ �����������

	void exit_passenger(string& s);//����� ������ ����������

	void enter_passenger(string& s);//����� ����� ����������

	void move(string& s);

	void Signal_to_passenger_about_control_panel(string& s);

	void Signal_to_floor(string& s);

	void Signal_to_system(string& s);
};

#endif
