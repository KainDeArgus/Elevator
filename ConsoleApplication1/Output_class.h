#ifndef __OUTPUT_CLASS__H
#define __OUTPUT_CLASS__H

#include "Base_class.h"

class Output_class : public Base_class {
public:
	Output_class(Base_class* p_head_object, string s_object_name);//конструктор

	void Handler_output(string& message);//обработчик строки на вывод
};

#endif
