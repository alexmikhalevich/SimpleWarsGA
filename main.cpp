#include <iostream>
#include "cview.h"

int main(int argc, char** argv) {
	try {
		CView* view = new CView();
		view->init();
		delete view;
	} catch(IException* e) {
		std::cerr << e->what() << std::endl;
	}

	return 0;
}
