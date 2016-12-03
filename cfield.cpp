#include "cfield.h"
using namespace Representation;

CShotRepresentation::CShotRepresentation(int x, int y, bool side) {
	m_x = x / CELL_SIZE;
	m_y = y / CELL_SIZE;
	m_rect.x = (x / CELL_SIZE) * CELL_SIZE;
	m_rect.y = (y / CELL_SIZE) * CELL_SIZE;
	m_rect.w = CELL_SIZE;
	m_rect.h = CELL_SIZE;
	m_side = side;
}

SDL_Rect* CShotRepresentation::rect() {
	return &m_rect;
}

Unit::EUnitClass CShotRepresentation::type() const {
	return Unit::EUnitClass::NO_UNIT;
}

bool CShotRepresentation::side() const {
	return m_side;
}

int CShotRepresentation::x() const {
	return m_x;
}

int CShotRepresentation::y() const {
	return m_y;
}

CUnitRepresentation::CUnitRepresentation(int x, int y, Unit::EUnitClass type, bool side) {
	m_x = x / CELL_SIZE;
	m_y = y / CELL_SIZE;
	m_rect.x = (x / CELL_SIZE) * CELL_SIZE; 
	m_rect.y = (y / CELL_SIZE) * CELL_SIZE;
	m_rect.w = CELL_SIZE;
	m_rect.h = CELL_SIZE;
	m_type = type;
	m_side = side;
}

SDL_Rect* CUnitRepresentation::rect() {
	return &m_rect;
}

Unit::EUnitClass CUnitRepresentation::type() const {
	return m_type;
}

bool CUnitRepresentation::side() const {
	return m_side;
}

int CUnitRepresentation::x() const {
	return m_x;
}

int CUnitRepresentation::y() const {
	return m_y;
}

CField::CField(size_t vsize, size_t hsize) {
	m_field.resize(hsize);
	for(size_t i = 0; i < hsize; ++i) {
		m_field[i].resize(vsize);
		for(size_t j = 0; j < vsize; ++j) m_field[i][j] = NULL; 
	}
	//m_next_element = m_elements.begin();
}

bool CField::get_next(element* next) {
	if(m_elements.empty()) return false;
	else if(m_next_element != m_elements.end()) {
		*next = m_next_element++;
		return true;
	}
	else return false;
}

void CField::renew() {
	if(!m_elements.empty()) m_next_element = m_elements.begin();
}

void CField::add_element(IRepresentation* representation) {
	int x = representation->x();
	int y = representation->y();
	m_field[x][y] = representation;
	m_elements.push_back(representation);
}

void CField::pop_element() {
	if(m_elements.empty()) return;
	int x = (*(m_elements.end() - 1))->x();
	int y = (*(m_elements.end() - 1))->y();
	//delete m_field[x][y];
	m_field[x][y] = NULL;
	m_elements.pop_back();
}

void CField::renew_positions() {
}

bool CField::element_exists(int x, int y) const {
	return (m_field[x / CELL_SIZE][y / CELL_SIZE] != NULL);
}
