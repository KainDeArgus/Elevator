#ifndef __CONTROL_PANEL__H
#define __CONTROL_PANEL__H

#include "Base_class.h"

class Control_panel : public Base_class {
private:
	vector <string> queue_requests;//очередь запросов людей, находящихся в лифте
public:
	Control_panel(Base_class* p_head_object, string s_object_name);//конструктор

	void Handler_from_passenger(string destination_floor);//сигнал от пассажира до его пункта назначения
														//вызывается при входе пассажира в лифт

	void Signal_elevator(string& destination_floor);//сигнал лифту об изменении его пункта назначения

	void Handler_from_system(string& s);
};

#endif
