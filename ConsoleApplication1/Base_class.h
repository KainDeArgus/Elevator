#ifndef BASE_CLASS_H
#define BASE_CLASS_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Base_class {
public:
	typedef void (Base_class ::* TYPE_SIGNAL) (string&);
	typedef void (Base_class ::* TYPE_HANDLER) (string&);
#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HANDLER_D( handler_f ) ( TYPE_HANDLER ) ( & handler_f )
private:
	struct o_sh //��������� ������� ����� �����
	{
		TYPE_SIGNAL p_signal;//��������� �� ����� �������
		Base_class* p_cl_base;//��������� �� ������� ������
		TYPE_HANDLER p_handler;//��������� �� ����� �����������
	};
	vector < o_sh* > connects;//��������� ������ ������-����������
	Base_class* p_head_object;//��������� �� �������� ������
	string s_object_name;//��� �������
	vector < Base_class* > subordinate_objects;//���������� �������
	int ready_state = 0;//����� ���������� �������
	int class_id; //��������� ������������� ������
public:
	~Base_class();//����������
	Base_class(Base_class* p_head_object, string s_object_name =
		"Default_name");//�����������
	bool rename_object(string new_object_name);//�������������� �������
	string get_object_name();//������ ����� �������
	Base_class* get_p_head_object();//������ ��������� �� �������� ������
	Base_class* find_s_object(string s_object_name);//����� ������� �� ����� ����� ����������
	Base_class* find_object_by_name(string object_name);//����� ������� �� ����� �� ������ ����� ������
	Base_class* find_object_tree(string object_name);//����� ������ �� ����� ��������
	void set_ready_state(int state = 0);//������ ����� ���������� �������
	void show_tree_objects_ready_state(int level = 1);//����� ������� � ������� ����������
	void show_tree_objects(int level = 1);//����� �������
	bool change_head_object(Base_class* new_head_object);//��������������� ��������� �������
	void erase_s_object(string s_object_name);//�������� ����������� ������� �� �����
	Base_class* get_pointer_object(string coordinates);//��������� ��������� �� ������ �� ��� ����������
	void set_connect(TYPE_SIGNAL p_signal, Base_class* p_object,
			TYPE_HANDLER p_ob_hendler);//��������� ����� ������-����������
	void delete_connect(TYPE_SIGNAL p_signal, Base_class* p_object,
		TYPE_HANDLER p_ob_hendler);//�������� ����� ������-����������
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command);//��������� ������� � ���������� ������������
	string get_coordinates(string coordinates = "");//��������� ���������� �������
	void set_default_ready_state();//��������� ���� �������� �� ����� ������
	//��� ����� ������ ���� ������� ������ ��������
	void set_class_id(int class_id);//������ ���������� ��������������
	int get_class_id();//������ ���������� ��������������
	Base_class* get_s_object(int i);//������ i-���� ����������� �������
};
#endif