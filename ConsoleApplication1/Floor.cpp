#include "Floor.h"
#include "Control_panel.h"

Floor::Floor(Base_class* p_head_object, string s_object_name)
	: Base_class(p_head_object, s_object_name) {}

void Floor::Signal_condition(string& message) {
	message = "\nCondition on the floor " + get_object_name() + " -up-";
	for (int i = 0; i < up_queue.size(); i++)
		message += " " + up_queue[i];

	message += "\nCondition on the floor " + get_object_name() + " -down-";
	for (int i = 0; i < down_queue.size(); i++)
		message += "  " + down_queue[i];
}

void Floor::Handler_condition(string& s_command) {
	if (s_command == get_object_name())
		emit_signal(SIGNAL_D(Floor::Signal_condition), s_command);
}

void Floor::Signal_enter_passenger(string& direction_elevator) {
	string str_people = "";
	while (direction_elevator[0] != ' ') {
		str_people += direction_elevator[0];
		direction_elevator.erase(direction_elevator.begin());
	}
	direction_elevator.erase(direction_elevator.begin());
	int people = stoi(str_people);
	str_people = direction_elevator;
	direction_elevator = "";
	if (str_people == "up") {
		for (; people > 0; people--) {
			if (up_queue.empty())
				break;
			direction_elevator += up_queue[0] + "/";
			up_queue.erase(up_queue.begin());
		}
		if (up_queue.size() == 0) up_button = false;
	}

	if (str_people == "down") {
		for (; people > 0; people--) {
			if (down_queue.empty())
				break;
			direction_elevator += down_queue[0] + "/";
			down_queue.erase(down_queue.begin());
		}
		if (down_queue.size() == 0) down_button = false;
	}

	if (str_people == "stop") {
		if (up_queue.size() != 0) {
			direction_elevator += up_queue[0] + "/";
			up_button = false;
			up_queue.erase(up_queue.begin());
		}
		if (down_queue.size() != 0) {
			direction_elevator += down_queue[0] + "/";
			down_button = false;
			down_queue.erase(down_queue.begin());
		}
	}
}

void Floor::Handler_enter_passenger(string& s) {
	emit_signal(SIGNAL_D(Floor::Signal_enter_passenger), s);
}

void Floor::Handler_passengers(string& dir) {
	char direcrion = dir[0];
	dir.erase(dir.begin());

	if (direcrion == 'u') {
		if (!up_button) {
			up_button = true;
			up_queue.push_back(dir);
		}
		else
			up_queue.push_back(dir);
	}
	else {
		if (!down_button) {
			down_button = true;
			down_queue.push_back(dir);
		}
		else
			down_queue.push_back(dir);
	}
}

int Floor::get_count_up_people() {
	return up_queue.size();
}

int Floor::get_count_down_people() {
	return down_queue.size();
}

bool Floor::get_up_button() {
	return up_button;
}

bool Floor::get_down_button() {
	return down_button;
}