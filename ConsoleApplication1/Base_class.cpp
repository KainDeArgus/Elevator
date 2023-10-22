#include <iostream>
#include <vector>
#include "Base_class.h"
using namespace std;
Base_class::~Base_class() {
	for (int i = 0; i < subordinate_objects.size(); i++) delete
		subordinate_objects[i];
	for (int i = 0; i < connects.size(); i++) delete connects[i];
}
Base_class::Base_class(Base_class* p_head_object, string s_object_name) {
	this->p_head_object = p_head_object;
	this->s_object_name = s_object_name;
	if (p_head_object != nullptr)
		p_head_object->subordinate_objects.push_back(this);
}
bool Base_class::rename_object(string new_object_name) {
	if (p_head_object != nullptr) {
		if (p_head_object->find_s_object(new_object_name) != nullptr) return
			false;
	}
	s_object_name = new_object_name;
	return true;
}
string Base_class::get_object_name() {
	return s_object_name;
}
Base_class* Base_class::get_p_head_object() {
	return p_head_object;
}
Base_class* Base_class::find_s_object(string s_object_name) {
	for (int i = 0; i < subordinate_objects.size(); i++)
		if (subordinate_objects[i]->s_object_name == s_object_name)
			return subordinate_objects[i];
	return nullptr;
}
Base_class* Base_class::find_object_by_name(string object_name) {
	if (s_object_name == object_name) return this;
	if (subordinate_objects.size() != 0) {
		for (int i = 0; i < subordinate_objects.size(); i++) {
			Base_class* result = subordinate_objects[i] -> find_object_by_name(object_name);
			if (result != nullptr)
				return result;
		}
	}
	return nullptr;
}
Base_class* Base_class::find_object_tree(string object_name) {
	if (p_head_object != nullptr)
		return p_head_object->find_object_tree(object_name);
	else
		return find_object_by_name(object_name);
}
void Base_class::set_ready_state(int state) {
	if (state == 0) {
		ready_state = 0;
		for (int i = 0; i < subordinate_objects.size(); i++) {
			if (subordinate_objects[i]->ready_state != 0)
				subordinate_objects[i]->set_ready_state();
		}
	}
	else {
		if (p_head_object != nullptr) {
			if (p_head_object->ready_state != 0)
				ready_state = state;
		}
		else ready_state = state;
	}
}
void Base_class::show_tree_objects_ready_state(int level) {
	cout << s_object_name;
	if (ready_state != 0)
		cout << " is ready";
	else
		cout << " is not ready";
	string spaces = "";
	for (int i = 0; i < 4 * level; i++)
		spaces += " ";
	for (int j = 0; j < subordinate_objects.size(); j++) {
		cout << endl << spaces;
		subordinate_objects[j]->show_tree_objects_ready_state(level + 1);
	}
}
void Base_class::show_tree_objects(int level) {
	cout << s_object_name;
	string spaces = "";
	for (int i = 0; i < 4 * level; i++)
		spaces += " ";
	for (int j = 0; j < subordinate_objects.size(); j++) {
		cout << endl << spaces;
		subordinate_objects[j]->show_tree_objects(level + 1);
	}
}
bool Base_class::change_head_object(Base_class* new_head_object) {
	if (p_head_object == nullptr ||
		find_object_by_name(new_head_object->s_object_name) != nullptr ||
		new_head_object->find_s_object(s_object_name) != nullptr)
		return false;
	else {
		for (int i = 0; i < p_head_object->subordinate_objects.size(); i++) {
			if (p_head_object->subordinate_objects[i]->s_object_name ==
				s_object_name) {

				p_head_object->subordinate_objects.erase(p_head_object -> subordinate_objects.begin() + i);

				break;
			}
		}
		p_head_object = new_head_object;
		new_head_object->subordinate_objects.push_back(this);
		return true;
	}
}
void Base_class::erase_s_object(string s_object_name) {
	for (int i = 0; i < subordinate_objects.size(); i++) {
		if (subordinate_objects[i]->s_object_name == s_object_name) {
			vector<Base_class*> tree_objects = { get_pointer_object("/") };
			for (int j = 0; j < tree_objects.size(); j++) {
				for (int k = 0; k < tree_objects[j]->connects.size(); k++) {
					if (tree_objects[j]->connects[k]->p_cl_base ==

						subordinate_objects[i]) {

						delete tree_objects[j]->connects[k];
						tree_objects[j]->connects.erase(tree_objects[j] ->connects.begin() + k);
					}
				}
				for (int k = 0; k < tree_objects[j]->subordinate_objects.size(); k ++)
					tree_objects.push_back(tree_objects[j] -> subordinate_objects[k]);

			}
			delete subordinate_objects[i];
			subordinate_objects.erase(subordinate_objects.begin() + i);
			break;
		}
	}
}
Base_class* Base_class::get_s_object(int i) {
	return subordinate_objects[i];
}
Base_class* Base_class::get_pointer_object(string coordinates) {
	string object_name = "";
	Base_class* next_object = nullptr;
	if (coordinates == "")
		return nullptr;
	if (coordinates[0] == '/') {
		if (coordinates == "/") {
			if (p_head_object != nullptr)
				return p_head_object->get_pointer_object("/");
			else
				return this;
		}
		if (coordinates[1] == '/') {
			coordinates.erase(coordinates.begin(), coordinates.begin() + 2);
			return find_object_tree(coordinates);
		}
		if (p_head_object != nullptr)
			return p_head_object->get_pointer_object(coordinates);
		else {
			coordinates.erase(coordinates.begin());
			return get_pointer_object(coordinates);
		}
	}
	if (coordinates[0] == '.') {
		if (coordinates == ".")
			return this;
		else {
			coordinates.erase(coordinates.begin());
			return find_object_by_name(coordinates);
		}
	}
	for (int i = 0; i < coordinates.size(); i++) {
		if (coordinates[i] == '/') {
			coordinates.erase(coordinates.begin(), coordinates.begin() + i + 1);
			break;
		}
		object_name += coordinates[i];
	}
	next_object = find_s_object(object_name);
	if (next_object == nullptr)
		return nullptr;
	if (object_name == coordinates)
		return next_object;
	else
		return next_object->get_pointer_object(coordinates);
}
void Base_class::set_connect(TYPE_SIGNAL p_signal, Base_class* p_object,

	TYPE_HANDLER p_ob_handler) {

	o_sh* p_value;
	for (int i = 0; i < connects.size(); i++) {
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_cl_base == p_object &&
			connects[i]->p_handler == p_ob_handler)
			return;
	}
	p_value = new o_sh();
	p_value->p_signal = p_signal;
	p_value->p_cl_base = p_object;
	p_value->p_handler = p_ob_handler;
	connects.push_back(p_value);
}
void Base_class::delete_connect(TYPE_SIGNAL p_signal, Base_class*
	p_object,

	TYPE_HANDLER p_ob_handler) {

	for (int i = 0; i < connects.size(); i++) {
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_cl_base == p_object &&
			connects[i]->p_handler == p_ob_handler) {
			delete connects[i];
			connects.erase(connects.begin() + i);
			break;
		}
	}
}void Base_class::emit_signal(TYPE_SIGNAL p_signal, string& s_command) {
	TYPE_HANDLER p_handler;
	Base_class* p_object;
	if (ready_state == 0) return;
	(this->*p_signal)(s_command);
	for (int i = 0; i < connects.size(); i++) {
		if (connects[i]->p_signal == p_signal) {
			p_handler = connects[i]->p_handler;
			p_object = connects[i]->p_cl_base;
			if (p_object->ready_state == 0) continue;
			(p_object->*p_handler)(s_command);
		}
	}
}
string Base_class::get_coordinates(string coordinates) {
	if (p_head_object != nullptr) {
		coordinates = "/" + s_object_name + coordinates;
		return p_head_object->get_coordinates(coordinates);
	}
	else {
		if (coordinates == "") return "/";
		else return coordinates;
	}
}
void Base_class::set_default_ready_state() {
	if ((p_head_object == nullptr) || (p_head_object != nullptr && p_head_object -> ready_state != 0)) {
		ready_state = 1;
		for (int i = 0; i < subordinate_objects.size(); i++)
			subordinate_objects[i]->set_default_ready_state();
	}
}
void Base_class::set_class_id(int class_id) {
	this->class_id = class_id;
}
int Base_class::get_class_id() {
	return class_id;
}