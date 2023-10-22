#ifndef APP_CLASS_H
#define APP_CLASS_H

#include "App_class.h"
#include "Elevator.h"
#include "Floor.h"

class App_class : public Base_class {
private:
	int floors;//количество этажей
	int time = 0;//такт системы

public:
	App_class(Base_class* p_head_object);//конструктор

	void bild_tree_objects();//метод построения дерева
	int exec_app();//метод запуска системы

	void Handler_construct_sistem(string& s_command);//обработчик для построения дерева объектов

	void Handler_exec_sistem(string& s_command);//обработчик запуска системы, обрабатывает команды

	void Signal_sistem(string& s_command);//сигнал для окончания построения или работы системы

	void Signal_condition(string& message);//сигнал показа состояния

	void Signal_not_found_passenger(string& message);//сигнал ненайденного пассажира, вызывается если пассажир в команде не был найден

	void Signal_from_floors(string& s_command);//сигнал проверки этажей на включённые кнопки "ВВЕРХ" или "ВНИЗ"

	void Signal_on_input(string& s_command);//сигнал объекту чтения на ввод

	void Signal_for_condition_elevator(string& s_command);//сигнал лифту о показе состояние

	void Signal_for_condition_floor(string& s_command);//сигнал этажам о показе состояния

	void Signal_for_condition_passenger(string& s_command);//сигнал пассажирам о показе состояния

	void change_name_objects();//метод изменения имён объектов перед выводом дерева

	void Signal_elevator_exit(string& s);
	void Signal_elevator_enter(string& s);
	void Signal_elevator_move(string& s);

	void Signal_passenger_coming(string& s);

	void Signal_to_control_panel(string& s);

	void Handler_from_elevator(string& s);
};

#endif