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
	struct o_sh //структура задания одной связи
	{
		TYPE_SIGNAL p_signal;//указатель на метод сигнала
		Base_class* p_cl_base;//указатель на целевой объект
		TYPE_HANDLER p_handler;//указатель на метод обработчика
	};
	vector < o_sh* > connects;//хранилище связей сигнал-обработчик
	Base_class* p_head_object;//указатель на головной объект
	string s_object_name;//имя объекта
	vector < Base_class* > subordinate_objects;//подчинённые объекта
	int ready_state = 0;//метка готовности объекта
	int class_id; //классовый идентификатор класса
public:
	~Base_class();//деструктор
	Base_class(Base_class* p_head_object, string s_object_name =
		"Default_name");//конструктор
	bool rename_object(string new_object_name);//переименование объекта
	string get_object_name();//геттер имени объекта
	Base_class* get_p_head_object();//геттер указателя на головной объект
	Base_class* find_s_object(string s_object_name);//поиск объекта по имени среди подчинённых
	Base_class* find_object_by_name(string object_name);//поиск объекта по имени на данной ветке дерева
	Base_class* find_object_tree(string object_name);//поиск оъекта по имени всистеме
	void set_ready_state(int state = 0);//сеттер метки готовности объекта
	void show_tree_objects_ready_state(int level = 1);//вывод системы с метками готовности
	void show_tree_objects(int level = 1);//вывод системы
	bool change_head_object(Base_class* new_head_object);//переопределение головного объекта
	void erase_s_object(string s_object_name);//удаление подчинённого объекта по имени
	Base_class* get_pointer_object(string coordinates);//получение указателя на объект по его координате
	void set_connect(TYPE_SIGNAL p_signal, Base_class* p_object,
			TYPE_HANDLER p_ob_hendler);//установка связи сигнал-обработчик
	void delete_connect(TYPE_SIGNAL p_signal, Base_class* p_object,
		TYPE_HANDLER p_ob_hendler);//удаление связи сигнал-обработчик
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command);//генерация сигнала и выполнение отработчиков
	string get_coordinates(string coordinates = "");//получение координаты объекта
	void set_default_ready_state();//включение всех объектов на ветке дерева
	//или всего дерева если текущий объект корневой
	void set_class_id(int class_id);//сеттер классового идентификатора
	int get_class_id();//геттер классового идентификатора
	Base_class* get_s_object(int i);//геттер i-того подчинённого объекта
};
#endif