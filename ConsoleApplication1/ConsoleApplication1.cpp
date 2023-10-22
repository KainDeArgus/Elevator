#include <stdlib.h>
#include <stdio.h>
#include "App_class.h"
int main()
{
	App_class ob_app_class = App_class(nullptr);
	ob_app_class.bild_tree_objects();
	return ob_app_class.exec_app();
}