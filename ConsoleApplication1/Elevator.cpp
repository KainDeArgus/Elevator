#include "Elevator.h"
#include "App_class.h"
#include "Passenger.h"
Elevator::Elevator(Base_class* p_head_object, string s_object_name)
	: Base_class(p_head_object, s_object_name) {}
int Elevator::get_level() {
	return level_now;
}
void Elevator::set_capacity(int capacity) {
	this->capacity = capacity;
}
int Elevator::get_people() {
	return people;
}
int Elevator::get_direction() {
	return direction;
}
void Elevator::Handler_condition(string& s_command) {
	emit_signal(SIGNAL_D(Elevator::Signal_condition), s_command);
}
void Elevator::Signal_condition(string& message) {
	message = "\nElevator condition: " + to_string(level_now) + " " +
		to_string(people) + " ";
	if (stop_for_passenger) {
		message += "stop";
		return;
	}
	switch (direction) {
	case stop:
		message += "stop";
		break;
	case up:
		message += "direction up";
		break;
	case down:
		message += "direction down";
		break;
	}
}
void Elevator::Handler_passengers(string& s_command) {
	string destination_floor = s_command;
	if (destination_floor == "N") {
		if (level_max == level_now) direction = Elevator::stop;
		return;
	}
	char switcher = destination_floor[0];
	destination_floor.erase(destination_floor.begin());
	int number_floor = stoi(destination_floor);
	if (switcher == 'u' && (direction == Elevator::up && level_max <
		number_floor) ||
		(direction == Elevator::down && level_max > number_floor))
		level_max = number_floor;
	if (switcher == 'r')
		reverse_direction = true;
	if (switcher == 'c') {
		direction *= -1;
		level_max = number_floor;
	}
	if (switcher == 's' || switcher == 'r') {
		level_max = number_floor;
		if (level_max > level_now)
			direction = Elevator::up;
		if (level_max < level_now)
			direction = Elevator::down;
		if (level_max == level_now) direction = Elevator::stop;
	}
}
void Elevator::move(string& s) {
	if (stop_for_passenger) return;
	if (direction == Elevator::down)
		level_now--;
	if (direction == Elevator::up)
		level_now++;
}
void Elevator::exit_passenger(string& s) {
	string command = "";
	int ppl = people;
	if (stop_for_passenger) stop_for_passenger = false;
	for (int i = 0; i < people;) {
		Passenger* person = (Passenger*)get_s_object(i);
		if (person->get_des_floor() == level_now) {
			stop_for_passenger = true;
			erase_s_object(person->get_object_name());
			people--;
		}
		else i++;
	}
	if ((people == 0 && ppl != people) || (reverse_direction && level_now ==
		level_max)) {
		reverse_direction = false;
		emit_signal(SIGNAL_D(Elevator::Signal_to_system), command);
	}
}
void Elevator::Signal_to_system(string& s) {}void Elevator::Signal_to_passenger_about_control_panel(string& s) {}
void Elevator::Handler_enter_passenger(string& fio) {
	Base_class* floor = get_pointer_object("/" + to_string(level_now));
	Base_class* passenger;
	string fio_passenger = "";
	while (fio != "") {
		if (fio[0] != '/')
			fio_passenger += fio[0];
		else {
			stop_for_passenger = true;
			passenger = floor->find_s_object(fio_passenger);
			passenger->change_head_object(this);
			set_connect(SIGNAL_D(Elevator::Signal_to_passenger_about_control_panel),
				passenger,

				HANDLER_D(Passenger::Handler_control_panel));

			emit_signal(SIGNAL_D(Elevator::Signal_to_passenger_about_control_panel),
				fio_passenger);
			delete_connect(SIGNAL_D(Elevator::Signal_to_passenger_about_control_panel),
				passenger,

				HANDLER_D(Passenger::Handler_control_panel));
			people++;
			fio_passenger = "";
		}
		fio.erase(fio.begin());
	}
}
void Elevator::Signal_to_floor(string& s) {}
void Elevator::enter_passenger(string& s) {
	string command = to_string(capacity - people);
	if (direction == Elevator::up) command += " up";
	if (direction == Elevator::down) command += " down";
	if (direction == Elevator::stop) command += " stop";
	set_connect(SIGNAL_D(Elevator::Signal_to_floor), get_pointer_object("/" +
		to_string(level_now)),
		HANDLER_D(Floor::Handler_enter_passenger));
	emit_signal(SIGNAL_D(Elevator::Signal_to_floor), command);
	delete_connect(SIGNAL_D(Elevator::Signal_to_floor), get_pointer_object("/"
		+ to_string(level_now)),
		HANDLER_D(Floor::Handler_enter_passenger));
}
void Elevator::Handler_from_control_panel(string& destination_floor) {
	if (destination_floor == "N") return;
	int d_f = stoi(destination_floor);
	if ((direction == Elevator::up && d_f > level_max)
		|| (direction == Elevator::down && d_f < level_max) || direction ==
		Elevator::stop)level_max = d_f;
	if (direction == Elevator::stop && level_max > level_now)
		direction = Elevator::up;
	if (direction == Elevator::stop && level_max < level_now)
		direction = Elevator::down;
}