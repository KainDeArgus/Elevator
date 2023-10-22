#include "Passenger.h"
Passenger::Passenger(Base_class* p_head_object, string s_object_name)
	: Base_class(p_head_object, s_object_name) {}
void Passenger::Signal_condition(string& message) {
	message = "\nPassenger condition: " + get_object_name();
	string floor = get_p_head_object()->get_object_name();
	if (floor == "object_elevator")
		message += " in the elevator";
	else {
		message += " on the floor " + floor;
	}
}
int Passenger::get_des_floor() {
	return destination_floor;
}
void Passenger::Handler_control_panel(string& s) {
	emit_signal(SIGNAL_D(Passenger::Signal_control_panel), s);
}void Passenger::Handler_coming_to_the_floor(string& s) {
	emit_signal(SIGNAL_D(Passenger::Signal_coming_to_the_floor), s);
}
void Passenger::Handler_condition(string& s) {
	emit_signal(SIGNAL_D(Passenger::Signal_condition), s);
}
void Passenger::Signal_coming_to_the_floor(string& s_command) {
	string str_number_floor = "";
	while (s_command[0] != ' ') {
		str_number_floor += s_command[0];
		s_command.erase(s_command.begin());
	}
	s_command.erase(s_command.begin());
	destination_floor = stoi(s_command);
	int number_floor = stoi(str_number_floor);
	if (destination_floor > number_floor)
		s_command = "u" + get_object_name();
	else
		s_command = "d" + get_object_name();
}
void Passenger::Signal_control_panel(string& destination_floor) {
	destination_floor = to_string(this->destination_floor);
}