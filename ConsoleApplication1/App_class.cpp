#include "App_class.h"
#include "Input_class.h"
#include "Output_class.h"
#include "Passenger.h"
#include "Control_panel.h"
App_class::App_class(Base_class* p_head_object) :Base_class(p_head_object){}
void App_class::Signal_on_input(string& s_command) {}
void App_class::Signal_for_condition_elevator(string& s_command) {}
void App_class::Signal_for_condition_floor(string& s_command) {}
void App_class::Signal_for_condition_passenger(string& s_command) {}
void App_class::Signal_elevator_enter(string& s_command) {}
void App_class::Signal_elevator_exit(string& s_command) {}
void App_class::Signal_elevator_move(string& s_command) {}
void App_class::Signal_passenger_coming(string& s_command) {}
void App_class::Signal_to_control_panel(string& s_command) {}
void App_class::Handler_from_elevator(string& s) {
	emit_signal(SIGNAL_D(App_class::Signal_from_floors), s);
}
void App_class::bild_tree_objects() {
	//построение исходного дерева иерархии объектов
	rename_object("object_system");
	Control_panel* control_panel = new Control_panel(this,
		"object_remote_control"); Input_class* input = new Input_class(this, "object_read_command");
	input->set_connect(SIGNAL_D(Input_class::Signal_input), this,
		HANDLER_D(App_class::Handler_construct_sistem));
	set_connect(SIGNAL_D(App_class::Signal_on_input), input,
		HANDLER_D(Input_class::Handler_input));
	Output_class* output = new Output_class(this, "object_display_screen");
	this->set_connect(SIGNAL_D(App_class::Signal_sistem), output,
		HANDLER_D(Output_class::Handler_output));
	Elevator* elevator = new Elevator(control_panel, "object_elevator");
	set_default_ready_state();
	string s_command;
	do
	{
		emit_signal(SIGNAL_D(App_class::Signal_on_input), s_command);
	} while (s_command != "Ready to work");
	input->delete_connect(SIGNAL_D(Input_class::Signal_input), this,
		HANDLER_D(App_class::Handler_construct_sistem));
	//установка связей
	elevator->set_connect(SIGNAL_D(Elevator::Signal_condition), output,
		HANDLER_D(Output_class::Handler_output));
	elevator->set_connect(SIGNAL_D(Elevator::Signal_to_system), this,
		HANDLER_D(App_class::Handler_from_elevator));
	this->set_connect(SIGNAL_D(App_class::Signal_elevator_enter), elevator,
		HANDLER_D(Elevator::enter_passenger));
	this->set_connect(SIGNAL_D(App_class::Signal_elevator_exit), elevator,
		HANDLER_D(Elevator::exit_passenger));
	this->set_connect(SIGNAL_D(App_class::Signal_elevator_move), elevator,
		HANDLER_D(Elevator::move));
	this->set_connect(SIGNAL_D(App_class::Signal_condition), output,
		HANDLER_D(Output_class::Handler_output));
	this->set_connect(SIGNAL_D(App_class::Signal_not_found_passenger), output,
		HANDLER_D(Output_class::Handler_output));
	this->set_connect(SIGNAL_D(App_class::Signal_from_floors), elevator,
		HANDLER_D(Elevator::Handler_passengers));
	this->set_connect(SIGNAL_D(App_class::Signal_for_condition_elevator),
		elevator,
		HANDLER_D(Elevator::Handler_condition));
	this->set_connect(SIGNAL_D(App_class::Signal_to_control_panel),
		control_panel,
		HANDLER_D(Control_panel::Handler_from_system));
	input->set_connect(SIGNAL_D(Input_class::Signal_input), this,
		HANDLER_D(App_class::Handler_exec_sistem));
	control_panel->set_connect(SIGNAL_D(Control_panel::Signal_elevator),
		elevator,
		HANDLER_D(Elevator::Handler_from_control_panel));
	for (int i = 1; find_s_object(to_string(i)) != nullptr; i++) {
		Base_class* floor = find_s_object(to_string(i)); floor->set_connect(SIGNAL_D(Floor::Signal_enter_passenger),
			elevator, HANDLER_D(Elevator::Handler_enter_passenger));
		floor->set_connect(SIGNAL_D(Floor::Signal_condition), output,
			HANDLER_D(Output_class::Handler_output));
		this->set_connect(SIGNAL_D(App_class::Signal_for_condition_floor),
			floor,

			HANDLER_D(Floor::Handler_condition));
	}
}
int App_class::exec_app() {
	string s_command;
	do
	{
		emit_signal(SIGNAL_D(App_class::Signal_on_input), s_command);
	} while (s_command != "\nTurn off the system");
	return 0;
}
void App_class::Handler_construct_sistem(string& s_command) {
	//разбиваем строку на два числа
	string number = "";
	if (s_command == "End of settings") {
		emit_signal(SIGNAL_D(App_class::Signal_sistem), s_command); //команда конца настроек системы
			return;
	}
	while (s_command[0] != ' ') {
		number += s_command[0];
		s_command.erase(s_command.begin());
	}
	s_command.erase(s_command.begin());
	//создаём n объектов этажей, включаем их и добавляем в хранилище этажей системы
		floors = stoi(number);
	for (int i = 0; i < floors; i++) {
		Floor* floor = new Floor(this, to_string(i + 1));
		floor->set_ready_state(1);
	}
	//устанавливаем вместимость лифта
	((Elevator*
		)(get_pointer_object("/object_remote_control/object_elevator"))) -> set_capacity(stoi(s_command));
}
void App_class::change_name_objects() {//меняем имена и объектов этажей и пассажирах на этих этажах
	for (int i = 1; i <= floors; i++)
		find_s_object(to_string(i))->
		rename_object("object_floor_" + find_s_object(to_string(i)) -> get_object_name());
}
void App_class::Handler_exec_sistem(string& s_command) {
	Elevator* elevator =
		(Elevator*)get_pointer_object("/object_remote_control/object_elevator");
	string message = "";//строка для передачи в сигналы
	time++;
	if (s_command != "") {
		if (s_command == "SHOWTREE") {//команда показа дерева и окончания работы системы
				change_name_objects();//смена имён
			//вывод дерева с метками готовности
			cout << endl;
			show_tree_objects_ready_state();
		}
		message = s_command[0];
		if (message == "T" || s_command == "SHOWTREE") {//команда окончания работы системы
				emit_signal(SIGNAL_D(App_class::Signal_sistem), s_command);
			return;
		}
		if (message == "S")//команда показа состояния системы
			emit_signal(SIGNAL_D(App_class::Signal_condition), message);
		if (message == "E")
			emit_signal(SIGNAL_D(App_class::Signal_for_condition_elevator),

				message);
		if (message == "C") {
			s_command.erase(s_command.begin(), s_command.begin() + 23);
			emit_signal(SIGNAL_D(App_class::Signal_for_condition_floor),
				s_command);
		}
		if (message == "P") {//команда пассажира
			s_command.erase(s_command.begin(), s_command.begin() + 10);
			if (s_command[0] == 'c') {//команда показа состояния пассажира
				s_command.erase(s_command.begin(), s_command.begin() + 10);
				Base_class* passenger = find_object_by_name(s_command);//поиск пассажира в системе

					if (passenger == nullptr)//если пассажир не найден, система об этом говорит, ...

						emit_signal(SIGNAL_D(App_class::Signal_not_found_passenger), s_command);

					else {//... иначе вызывается сигнал показа состояния пассажира
						set_connect(SIGNAL_D(App_class::Signal_for_condition_passenger),
							passenger,

							HANDLER_D(Passenger::Handler_condition));

						emit_signal(SIGNAL_D(App_class::Signal_for_condition_passenger),
							s_command);
						delete_connect(SIGNAL_D(App_class::Signal_for_condition_passenger),
							passenger,

							HANDLER_D(Passenger::Handler_condition));
					}
			}
			else {//команда прихода пассажира на этаж
				//выделение номера конкретного этажа, куда подошёл пассажир
				string str_number_floor = "";//в этой строке получим два числа разделённых пробелом :

				// этаж прихода и этаж назначения
				while (s_command[0] != ' ') {
					str_number_floor += s_command[0];
					s_command.erase(s_command.begin());
				}
				Base_class* floor = find_s_object(str_number_floor);
				do {
					str_number_floor += s_command[0];
					s_command.erase(s_command.begin());
				} while (s_command[0] != ' ');
				s_command.erase(s_command.begin());
				//в командной строке остаётся только ФИО пассажира
				//создание объекта пассажира, его включение, установка связей
				Passenger* passenger = new Passenger(floor, s_command);
				passenger->set_ready_state(1);
				passenger->set_connect(SIGNAL_D(Passenger::Signal_condition),

					find_s_object("object_display_screen"),

					HANDLER_D(Output_class::Handler_output));
				passenger -> set_connect(SIGNAL_D(Passenger::Signal_coming_to_the_floor), floor,
HANDLER_D(Floor::Handler_passengers));
				passenger->set_connect(SIGNAL_D(Passenger::Signal_control_panel),

					find_s_object("object_remote_control"),

					HANDLER_D(Control_panel::Handler_from_passenger));
				//возбуждение сигнала подхода пассажира к этажу
				set_connect(SIGNAL_D(App_class::Signal_passenger_coming),

					passenger,

					HANDLER_D(Passenger::Handler_coming_to_the_floor));
				emit_signal(SIGNAL_D(App_class::Signal_passenger_coming),

					str_number_floor);

				delete_connect(SIGNAL_D(App_class::Signal_passenger_coming), passenger,

					HANDLER_D(Passenger::Handler_coming_to_the_floor));
			}
		}
	}
	//обработка такта
	{
		emit_signal(SIGNAL_D(App_class::Signal_elevator_exit),
			message);//старые пассажиры выходят
		emit_signal(SIGNAL_D(App_class::Signal_elevator_enter),
			message);//новые пассажиры заходят
		emit_signal(SIGNAL_D(App_class::Signal_to_control_panel),
			message);//лифту подаётся новый пункт назначения
		emit_signal(SIGNAL_D(App_class::Signal_from_floors), message);//этажи подают данные о нажатых кнопках
			emit_signal(SIGNAL_D(App_class::Signal_elevator_move), message);//в соответствии с данными системы лифт движется
	}
}
void App_class::Signal_sistem(string& s_command) {//сигнал окончания
	//команды об окончании работы системы
	if (s_command == "Turn off the system" || s_command == "SHOWTREE")
		s_command = "\nTurn off the system";
	//команды об окончании построения системы
	else s_command = "Ready to work";
}
void App_class::Signal_not_found_passenger(string& message) {
	message = "\nPassenger " + message + " not found";//сигнал о ненайденном пассажире
}
void App_class::Signal_condition(string& message) {//сигнал состояния системы
		message = "\n" + to_string(time) + ": Elevator: "
		+ to_string(((Elevator*)(get_pointer_object("/object_remote_control/object_elevator")))->get_level()) + " " +to_string(((Elevator*)(get_pointer_object("/object_remote_control/object_elevator")))->get_people()) + " Floors:";

	for (int i = 1; find_s_object(to_string(i)) != nullptr; i++) {
		Floor* floor = (Floor*)(find_s_object(to_string(i)));
		int count_up_people = floor->get_count_up_people();
		int count_down_people = floor->get_count_down_people();
		if (count_up_people + count_down_people != 0)
			message += " (" + floor->get_object_name() + ": " +
			to_string(count_up_people) + "-"
			+ to_string(count_down_people) + ")";
	}
}
void App_class::Signal_from_floors(string& s_command) {//сигнал от этажей скнопками
		Elevator* elevator =
		(Elevator*)get_pointer_object("/object_remote_control/object_elevator");
	int now_level = elevator->get_level();//нынешний этаж лифта
	/*
	Если лифт движется вверх, то сначала проверяются все этажи выше
	текущего. Если находится этаж с включённой
	кнопкой "ВВЕРХ", то лифт передаётся новый пункт назначения. Если такого
	этажа не находится, то проверяются
	этажи выше текущего на наличие кнопки "ВНИЗ". Если такого этажа не
	находится, то проверяются этажи ниже
	текущего на наличие кнопки "ВНИЗ".
	Если лифт движется вниз, то сначала проверяются все этажи нижа
	текущего. Если находится этаж с включённой
	кнопкой "ВНИЗ", то лифт передаётся новый пункт назначения. Если такого
	этажа не находится, то проверяются
	этажи ниже текущего на наличие кнопки "ВВЕРХ". Если такого этажа не
	находится, то проверяются этажи ниже
	текущего на наличие кнопки "ВВЕРХ".
	Если лифт стоит, то проверяются все этажи на наличие любых сигналов.
	Ситуация, когда лифт едет сначала вниз, а потом вверх или наоборот,
	называется change_direction и обозначается
	символом [c].
	Ситуация, когда лифт едет вверх, доставляет пассажиров, а затем
	продолжает ехать вверх, чтобы забрать и
	доставить пассажира вниз или наоборот, называется reverse_direction и
	обозначается символом [r]. Так же сюда
	подходят ситуации, когда лифт из положения стоп едет выше своего
	нынешнего этажа, чтобы забрать и
	доставить пассажира вниз или наоборот.
	Ситуация, когда лифт стоит и получает сигнал, называется stop_direction
	и обозначается символом [s].
	Остальные ситуации, когда лифт "подхватывает" по пути пассажиров
	называются usual_direction и обозначаются
	символом [u].
	Ситуация, когда сигналов от этажей нет, называется NON_direction и
	обозначается символом [N].
	*/
	if (elevator->get_direction() == Elevator::up) {
		for (int i = floors; i >= now_level; i--) {
			Floor* floor = (Floor*)get_pointer_object("/" + to_string(i));
			if (floor->get_up_button()) {
				s_command = "u" + floor->get_object_name();
				return;
			}
		}
		if (elevator->get_people() == 0) {
			for (int i = floors; i > now_level; i--) {
				Floor* floor = (Floor*)get_pointer_object("/" + to_string(i));
				if (floor->get_down_button()) {
					s_command = "r" + floor->get_object_name();
					return;
				}
			}
			for (int i = now_level; i >= 1; i--) {
				Floor* floor = (Floor*)get_pointer_object("/" + to_string(i));
				if (floor->get_down_button()) {
					s_command = "c" + floor->get_object_name();
					return;
				}
			}
		}
	}
	if (elevator->get_direction() == Elevator::down) {
		for (int i = 1; i <= now_level; i++) {
			Floor* floor = (Floor*)get_pointer_object("/" + to_string(i));
			if (floor->get_down_button()) {
				s_command = "u" + floor->get_object_name();
				return;
			}
		}
		if (elevator->get_people() == 0) {
			for (int i = 1; i < now_level; i++) {
				Floor* floor = (Floor*)get_pointer_object("/" + to_string(i));
				if (floor->get_up_button()) {
					s_command = "r" + floor->get_object_name();
					return;
				}
			}
			for (int i = now_level; i <= floors; i++) {
				Floor* floor = (Floor*)get_pointer_object("/" + to_string(i));
				if (floor->get_up_button()) {
					s_command = "c" + floor->get_object_name();
					return;
				}
			}
		}
	}
	if (elevator->get_direction() == Elevator::stop) {
		for (int i = 1; i <= floors; i++) {
			Floor* floor = (Floor*)get_pointer_object("/" + to_string(i));
			if (floor->get_up_button() || floor->get_down_button()) {
				s_command = "s";
				if ((floor->get_up_button() && now_level > i)
					|| (floor->get_down_button() && now_level < i))
					s_command = "r";
				s_command += floor->get_object_name();
				return;
			}
		}
	}
	s_command = "N";
}