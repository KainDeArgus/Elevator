#ifndef __ELEVATOR__H
#define __ELEVATOR__H

#include "Floor.h"

class Elevator : public Base_class {
private:
	int level_now = 1;//уровень(этаж), на котором находится лифт
	int level_max = 1;//уровень(этаж) - назначения лифта
	int capacity;//вместимость лифта
	int people;//количество людей в лифте в данный момент
	int direction = stop;//направление движения лифта
	bool reverse_direction = false;//особая ситуация движения лифта, когда лифт отвёз всех пассажиров вверх и движется до 
	//самого верхнего сигнала вниз и наоборот
	bool stop_for_passenger = false;//лифт высаживает или засаживает пассажиров
public:

	Elevator(Base_class* p_head_object, string s_object_name);//конструктор

	enum directions {//перечисление возможных направлений движения лифта
		stop = 0, up = 1, down = -1
	};

	void Signal_condition(string& message);//сигнал показа состояния

	void Handler_from_control_panel(string destination_floor);//обработчик сигналов с панели управления

	void Handler_passengers(string& destination_floor);//обработчик сигналов с кнопок "ВВЕРХ"-"ВНИЗ" на этажах

	void Handler_enter_passenger(string fio);//обработчик входа пассажиров

	void Handler_condition(string s_command);

	int get_level();//геттер уровня

	void set_capacity(int capacity);//сеттер вместимости

	int get_people();//геттер количества людей в лифте

	int get_direction();//геттер направления

	void exit_passenger(string& s);//метод выхода пассажиров

	void enter_passenger(string& s);//метод входа пассажиров

	void move(string& s);

	void Signal_to_passenger_about_control_panel(string& s);

	void Signal_to_floor(string& s);

	void Signal_to_system(string& s);
};

#endif
