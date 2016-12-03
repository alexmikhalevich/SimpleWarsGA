#include "cfield.h"
using namespace Field;

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

void CField::add_element(Representation::IRepresentation* representation) {
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
	for(size_t i = 0; i < m_elements.size(); ++i) {
		m_elements[i]->move(m_logic->direction());
	}
}

bool CField::element_exists(int x, int y) const {
	return (m_field[x / CELL_SIZE][y / CELL_SIZE] != NULL);
}
