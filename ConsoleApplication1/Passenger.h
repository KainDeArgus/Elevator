#ifndef __PASSENGER__H
#define __PASSENGER__H
#include "Base_class.h"
class Passenger : public Base_class {
private:
	int destination_floor;//этаж назначения
public:
	Passenger(Base_class* p_head_object, string s_object_name);//конструктор
	void Signal_condition(string& message);//сигнал показа состояния
	void Signal_coming_to_the_floor(string& inform);//сигнал прихода пассажира на этаж
	void Signal_control_panel(string& destination_floor);//сигнал на панель управления с нужным пассажиру этажом
	void Handler_coming_to_the_floor(string& message);
	void Handler_condition(string& s);
	void Handler_control_panel(string& s);
	int get_des_floor();
};
#endif