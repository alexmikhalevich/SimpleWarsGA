#include "cview.h"

void CView::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) throw new ExInitFailed(std::string(SDL_GetError()));
	int request = SDL_GetDesktopDisplayMode(0, &m_display_mode);
	m_window = SDL_CreateWindow("SimpleGame", 0, 0, m_display_mode.w, m_display_mode.h, SDL_WINDOW_SHOWN);
	if(m_window == NULL) throw new ExWindowCreationFailed(std::string(SDL_GetError())); 
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_field = new Representation::CField(/*100, 100*/); //TODO: replace with real size from argv
	m_active_type = Unit::EUnitClass::ARCHER;
	m_active_type_rect.x = 0;
	m_active_type_rect.y = 0;
	m_active_type_rect.h = Representation::CELL_SIZE;
	m_active_type_rect.w = Representation::CELL_SIZE;
	m_active_side = false;
}

void CView::_set_unit_rect_color(Unit::EUnitClass type, bool side) const {
	switch(type) {
		case Unit::EUnitClass::ARCHER:
			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, (side ? 0 : 100));
			break;
		case Unit::EUnitClass::WARRIOR:
			SDL_SetRenderDrawColor(m_renderer, 230, 255, 0, (side ? 0 : 100));
			break;
		case Unit::EUnitClass::WIZARD:
			SDL_SetRenderDrawColor(m_renderer, 105, 99, 188, (side ? 0 : 100));
			break;
		case Unit::EUnitClass::NO_UNIT:
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, (side ? 0 : 100));
			break;
	}
}

void CView::_redraw() {
	SDL_SetRenderDrawColor(m_renderer, 0, 200, 0, 0);
	SDL_RenderClear(m_renderer);
	Representation::element iter;
	while(m_field->get_next(iter)) {
		_set_unit_rect_color((*iter)->type(), (*iter)->side());
		SDL_RenderDrawRect(m_renderer, (*iter)->get_rect()); 
	}
	_set_unit_rect_color(m_active_type, m_active_side);
	SDL_RenderDrawRect(m_renderer, &m_active_type_rect); 
	SDL_RenderPresent(m_renderer);
	m_field->renew();
}

void CView::_process_events() {
	SDL_Event event;
	const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
	bool quit = false;
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			SDL_PumpEvents();
			if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				m_field->add_element(
						new Representation::CUnitRepresentation(event.button.x - Representation::CELL_SIZE / 2, 
									     		event.button.y - Representation::CELL_SIZE / 2,
									     		m_active_type,
											m_active_side));
				_redraw();
			}
			else if(keyboard_state[SDL_SCANCODE_A]) {
				m_active_type = Unit::EUnitClass::ARCHER;
				_redraw();
			}
			else if(keyboard_state[SDL_SCANCODE_W]) {
				m_active_type = Unit::EUnitClass::WARRIOR;
				_redraw();
			}
			else if(keyboard_state[SDL_SCANCODE_Z]) {
				m_active_type = Unit::EUnitClass::WIZARD;
				_redraw();
			}
			else if(keyboard_state[SDL_SCANCODE_U]) {
				m_field->pop_element();
				_redraw();
			}
			else if(keyboard_state[SDL_SCANCODE_SPACE]) {
				m_active_side = ~m_active_side;
				_redraw();
			}
			else if(keyboard_state[SDL_SCANCODE_RETURN]) {
				quit = true;
				_renew_cycle();
			}
		}
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
