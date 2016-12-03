#include "cfield.h"
using namespace Field;

CField::CField(size_t vsize, size_t hsize) {
	m_logic = NULL;
	m_field.resize(hsize);
	for(size_t i = 0; i < hsize; ++i) {
		m_field[i].resize(vsize);
		for(size_t j = 0; j < vsize; ++j) m_field[i][j] = NULL; 
	}
	//m_next_element = m_elements.begin();
}

CField::~CField() {
	if(m_logic) delete m_logic;
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
	Logic::ILogicObject* obj;
	if(representation->type() == Unit::EUnitClass::NO_UNIT) obj = dynamic_cast<Logic::CBullet*>(obj);
	else obj = dynamic_cast<Logic::CUnit*>(obj);
	//TODO: build obj
	m_field[x][y] = obj;
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
	m_logic->update();
}

bool CField::element_exists(int x, int y) const {
	return (m_field[x / Representation::CELL_SIZE][y / Representation::CELL_SIZE] != NULL);
}

void CField::activate_logic() {
	m_logic = new Logic::CGeneralLogic(&m_field);
	for(size_t i = 0; i < m_elements.size(); ++i)
		m_logic->add_unit(dynamic_cast<Representation::CUnitRepresentation*>(m_elements[i]));
}
