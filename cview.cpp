#include "cview.h"
#include <iostream>

void CView::init() {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) throw new ExInitFailed(std::string(SDL_GetError()));
	int request = SDL_GetDesktopDisplayMode(0, &m_display_mode);
	m_window = SDL_CreateWindow("SimpleGame", 0, 0, 500, 500, SDL_WINDOW_SHOWN); //TODO
	if(m_window == NULL) throw new ExWindowCreationFailed(std::string(SDL_GetError())); 
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_field = new Field::CField(500 / Representation::CELL_SIZE, 500 / Representation::CELL_SIZE); //TODO 
	m_active_type = Unit::EUnitClass::ARCHER;
	m_active_type_rect.x = 0;
	m_active_type_rect.y = 0;
	m_active_type_rect.h = Representation::CELL_SIZE;
	m_active_type_rect.w = Representation::CELL_SIZE;
	m_active_side = false;

	_process_events();
}

void CView::_set_represent_rect(Unit::EUnitClass type, SDL_Rect* rect, bool side) const {
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
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 0);
			break;
	}
	if(side) SDL_RenderFillRect(m_renderer, rect); 
	SDL_RenderDrawRect(m_renderer, rect); 
}

void CView::_redraw() {
	m_field->renew();
	SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 0);
	SDL_RenderClear(m_renderer);
	while(m_field->get_next(&m_next_iter)) 
		_set_represent_rect((*m_next_iter)->type(), (*m_next_iter)->rect(), (*m_next_iter)->side());
	_set_represent_rect(m_active_type, &m_active_type_rect, m_active_side);
	SDL_RenderPresent(m_renderer);
}

void CView::_process_events() {
	SDL_Event event;
	bool quit = false;
	while(!quit) {
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT) quit = true;
		else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if(!m_field->element_exists(event.button.x, event.button.y))
				m_field->add_element(new Representation::CUnitRepresentation(event.button.x, event.button.y, m_active_type,
										     	     m_active_side));
		}
		else if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_SPACE) {
				m_active_side = m_active_side ? 0 : 1;
			}
			else if(event.key.keysym.sym == SDLK_a) {
				m_active_type = Unit::EUnitClass::ARCHER;
			}
			else if(event.key.keysym.sym == SDLK_w) {
				m_active_type = Unit::EUnitClass::WARRIOR;
			}
			else if(event.key.keysym.sym == SDLK_z) {
				m_active_type = Unit::EUnitClass::WIZARD;
			}
			else if(event.key.keysym.sym == SDLK_u) {
				m_field->pop_element();
			}
			else if(event.key.keysym.sym == SDLK_RETURN) {
				quit = true;
				m_field->activate_logic();
				_renew_cycle();
			}
		}
		_redraw();
	}
}

void CView::_renew_cycle() {
	bool quit = false;
	while(!quit) {
		m_field->renew_positions();
		_redraw();
	}
}

CView::~CView() {
	delete m_field;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
