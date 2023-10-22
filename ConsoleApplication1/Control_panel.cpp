#include "Control_panel.h"
#include "Elevator.h"
#include "Floor.h"

Control_panel::Control_panel(Base_class* p_head_object, string s_object_name)
	: Base_class(p_head_object, s_object_name) {}

void Control_panel::Handler_from_passenger(string destination_floor) {
	queue_requests.push_back(destination_floor);
}

void Control_panel::Signal_elevator(string& destination_floor) {
	if (queue_requests.size() != 0) {
		destination_floor = queue_requests[0];
		queue_requests.erase(queue_requests.begin());
	}
	else destination_floor = "N";
}

void Control_panel::Handler_from_system(string& s) {
	emit_signal(SIGNAL_D(Control_panel::Signal_elevator), s);
}