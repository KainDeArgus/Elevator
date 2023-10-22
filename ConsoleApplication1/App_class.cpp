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
	//���������� ��������� ������ �������� ��������
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
	//��������� ������
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
	//��������� ������ �� ��� �����
	string number = "";
	if (s_command == "End of settings") {
		emit_signal(SIGNAL_D(App_class::Signal_sistem), s_command); //������� ����� �������� �������
			return;
	}
	while (s_command[0] != ' ') {
		number += s_command[0];
		s_command.erase(s_command.begin());
	}
	s_command.erase(s_command.begin());
	//������ n �������� ������, �������� �� � ��������� � ��������� ������ �������
		floors = stoi(number);
	for (int i = 0; i < floors; i++) {
		Floor* floor = new Floor(this, to_string(i + 1));
		floor->set_ready_state(1);
	}
	//������������� ����������� �����
	((Elevator*
		)(get_pointer_object("/object_remote_control/object_elevator"))) -> set_capacity(stoi(s_command));
}
void App_class::change_name_objects() {//������ ����� � �������� ������ � ���������� �� ���� ������
	for (int i = 1; i <= floors; i++)
		find_s_object(to_string(i))->
		rename_object("object_floor_" + find_s_object(to_string(i)) -> get_object_name());
}
void App_class::Handler_exec_sistem(string& s_command) {
	Elevator* elevator =
		(Elevator*)get_pointer_object("/object_remote_control/object_elevator");
	string message = "";//������ ��� �������� � �������
	time++;
	if (s_command != "") {
		if (s_command == "SHOWTREE") {//������� ������ ������ � ��������� ������ �������
				change_name_objects();//����� ���
			//����� ������ � ������� ����������
			cout << endl;
			show_tree_objects_ready_state();
		}
		message = s_command[0];
		if (message == "T" || s_command == "SHOWTREE") {//������� ��������� ������ �������
				emit_signal(SIGNAL_D(App_class::Signal_sistem), s_command);
			return;
		}
		if (message == "S")//������� ������ ��������� �������
			emit_signal(SIGNAL_D(App_class::Signal_condition), message);
		if (message == "E")
			emit_signal(SIGNAL_D(App_class::Signal_for_condition_elevator),

				message);
		if (message == "C") {
			s_command.erase(s_command.begin(), s_command.begin() + 23);
			emit_signal(SIGNAL_D(App_class::Signal_for_condition_floor),
				s_command);
		}
		if (message == "P") {//������� ���������
			s_command.erase(s_command.begin(), s_command.begin() + 10);
			if (s_command[0] == 'c') {//������� ������ ��������� ���������
				s_command.erase(s_command.begin(), s_command.begin() + 10);
				Base_class* passenger = find_object_by_name(s_command);//����� ��������� � �������

					if (passenger == nullptr)//���� �������� �� ������, ������� �� ���� �������, ...

						emit_signal(SIGNAL_D(App_class::Signal_not_found_passenger), s_command);

					else {//... ����� ���������� ������ ������ ��������� ���������
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
			else {//������� ������� ��������� �� ����
				//��������� ������ ����������� �����, ���� ������� ��������
				string str_number_floor = "";//� ���� ������ ������� ��� ����� ���������� �������� :

				// ���� ������� � ���� ����������
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
				//� ��������� ������ ������� ������ ��� ���������
				//�������� ������� ���������, ��� ���������, ��������� ������
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
				//����������� ������� ������� ��������� � �����
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
	//��������� �����
	{
		emit_signal(SIGNAL_D(App_class::Signal_elevator_exit),
			message);//������ ��������� �������
		emit_signal(SIGNAL_D(App_class::Signal_elevator_enter),
			message);//����� ��������� �������
		emit_signal(SIGNAL_D(App_class::Signal_to_control_panel),
			message);//����� ������� ����� ����� ����������
		emit_signal(SIGNAL_D(App_class::Signal_from_floors), message);//����� ������ ������ � ������� �������
			emit_signal(SIGNAL_D(App_class::Signal_elevator_move), message);//� ������������ � ������� ������� ���� ��������
	}
}
void App_class::Signal_sistem(string& s_command) {//������ ���������
	//������� �� ��������� ������ �������
	if (s_command == "Turn off the system" || s_command == "SHOWTREE")
		s_command = "\nTurn off the system";
	//������� �� ��������� ���������� �������
	else s_command = "Ready to work";
}
void App_class::Signal_not_found_passenger(string& message) {
	message = "\nPassenger " + message + " not found";//������ � ����������� ���������
}
void App_class::Signal_condition(string& message) {//������ ��������� �������
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
void App_class::Signal_from_floors(string& s_command) {//������ �� ������ ���������
		Elevator* elevator =
		(Elevator*)get_pointer_object("/object_remote_control/object_elevator");
	int now_level = elevator->get_level();//�������� ���� �����
	/*
	���� ���� �������� �����, �� ������� ����������� ��� ����� ����
	��������. ���� ��������� ���� � ����������
	������� "�����", �� ���� ��������� ����� ����� ����������. ���� ������
	����� �� ���������, �� �����������
	����� ���� �������� �� ������� ������ "����". ���� ������ ����� ��
	���������, �� ����������� ����� ����
	�������� �� ������� ������ "����".
	���� ���� �������� ����, �� ������� ����������� ��� ����� ����
	��������. ���� ��������� ���� � ����������
	������� "����", �� ���� ��������� ����� ����� ����������. ���� ������
	����� �� ���������, �� �����������
	����� ���� �������� �� ������� ������ "�����". ���� ������ ����� ��
	���������, �� ����������� ����� ����
	�������� �� ������� ������ "�����".
	���� ���� �����, �� ����������� ��� ����� �� ������� ����� ��������.
	��������, ����� ���� ���� ������� ����, � ����� ����� ��� ��������,
	���������� change_direction � ������������
	�������� [c].
	��������, ����� ���� ���� �����, ���������� ����������, � �����
	���������� ����� �����, ����� ������� �
	��������� ��������� ���� ��� ��������, ���������� reverse_direction �
	������������ �������� [r]. ��� �� ����
	�������� ��������, ����� ���� �� ��������� ���� ���� ���� ������
	��������� �����, ����� ������� �
	��������� ��������� ���� ��� ��������.
	��������, ����� ���� ����� � �������� ������, ���������� stop_direction
	� ������������ �������� [s].
	��������� ��������, ����� ���� "������������" �� ���� ����������
	���������� usual_direction � ������������
	�������� [u].
	��������, ����� �������� �� ������ ���, ���������� NON_direction �
	������������ �������� [N].
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