#include "cview.h"

void CView::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) throw new ExInitFailed;
	int request = SDL_GetDesktopDisplayMode(0, m_display_mode);
	m_window = SDL_CreateWindow("SimpleGame", 0, 0, m_display_mode->w, m_display_mode->h, SDL_WINDOW_SHOWN);
	if(m_window == NULL) throw new ExWindowCreationFailed; 
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

CView::~CView() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
