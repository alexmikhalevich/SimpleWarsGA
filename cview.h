#ifndef CVIEW_CPP
#define CVIEW_CPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "cfield.h"
#include "exception.hpp"

class CView {
	private:
		SDL_DisplayMode m_display_mode;
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		Representation::CField* m_field;
		Unit::EUnitClass m_active_type;
		Representation::element m_next_iter;
		bool m_active_side;
		SDL_Rect m_active_type_rect;
		void _set_unit_rect_color(Unit::EUnitClass type, bool side) const;
		void _renew_cycle();
		void _redraw();
		void _process_events();
	public:
		CView() {} 
		void init();
		~CView();
};

#endif //CVIEW_CPP
