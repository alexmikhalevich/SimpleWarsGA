#include "cview.h"

void CView::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) throw new ExInitFailed(std::string(SDL_GetError()));
	int request = SDL_GetDesktopDisplayMode(0, &m_display_mode);
	m_window = SDL_CreateWindow("SimpleGame", 0, 0, m_display_mode.w, m_display_mode.h, SDL_WINDOW_SHOWN);
	if(m_window == NULL) throw new ExWindowCreationFailed(std::string(SDL_GetError())); 
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_field = new CField(100, 100); //TODO: replace with real size from argv
}

void CView::redraw() {
	SDL_SetRenderDrawColor(m_renderer, 0, 200, 0, 0);
	SDL_RenderClear(m_renderer);
	element iter;
	while(m_field->get_next(iter)) {
		Unit::EUnitClass type = (*iter)->get_type();
		SDL_Rect* rect = (*iter)->get_rect();
		switch(type) {
			case Unit::EUnitClass::ARCHER:
				SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
				break;
			case Unit::EUnitClass::WARRIOR:
				SDL_SetRenderDrawColor(m_renderer, 230, 255, 0, 0);
				break;
			case Unit::EUnitClass::WIZARD:
				SDL_SetRenderDrawColor(m_renderer, 105, 99, 188, 0);
				break;
			case Unit::EUnitClass::NO_UNIT:
				//SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);	TODO
				break
		}
		SDL_RenderDrawRect(m_renderer, rect); 
	}
	m_field->renew();
}

CView::~CView() {
	delete m_field;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
