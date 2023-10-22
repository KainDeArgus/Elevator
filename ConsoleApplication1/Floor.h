#ifndef __FLOOR__H
#define __FLOOR__H
#include "Base_class.h"
class Floor : public Base_class {
private:
	vector <string> up_queue;//ФИО людей, стоящих в очереди "ВВЕРХ"
	vector <string> down_queue;//ФИО людей, стоящих в очереди "ВНИЗ"
	bool up_button = false;
	bool down_button = false;
public:
	Floor(Base_class* p_head_object, string s_object_name);//конструктор
	void Signal_condition(string& message);//сигнал показа состояния
	void Signal_enter_passenger(string& direction_elevator);//сигнал входа пассажира
	void Handler_passengers(string& dir);//обработчик подойдённых и нажавших кнопки пассажиров
	void Handler_enter_passenger(string& s);
	void Handler_condition(string& s_command); int get_count_up_people();//метод, который возвращает количество людей на этаже с направлением "ВВЕРХ"
	int get_count_down_people();//метод, который возвращает количество людей на этаже с направлением "ВНИЗ"
	bool get_up_button();
	bool get_down_button();
};
#endif