#ifndef CVIEW_CPP
#define CVIEW_CPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "exception.hpp"

class CView {
	private:
		SDL_DisplayMode* m_display_mode;
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
	public:
		CView() {}
		void init();
		~CView();
};

#endif //CVIEW_CPP
