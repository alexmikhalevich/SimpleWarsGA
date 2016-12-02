#include <iostream>
#include "cview.h"

int main(int argc, char** argv) {
	try {
		CView* view = new CView();
		view->init();
	} catch(IException* e) {
		std::cerr << e->what() << std::endl;
	}

	delete view;
	return 0;
}
