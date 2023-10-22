#ifndef __CONTROL_PANEL__H
#define __CONTROL_PANEL__H

#include "Base_class.h"

class Control_panel : public Base_class {
private:
	vector <string> queue_requests;//������� �������� �����, ����������� � �����
public:
	Control_panel(Base_class* p_head_object, string s_object_name);//�����������

	void Handler_from_passenger(string destination_floor);//������ �� ��������� �� ��� ������ ����������
														//���������� ��� ����� ��������� � ����

	void Signal_elevator(string& destination_floor);//������ ����� �� ��������� ��� ������ ����������

	void Handler_from_system(string& s);
};

#endif
