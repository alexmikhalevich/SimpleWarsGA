#include "cfield.h"

CField::CField(size_t vsize, size_t hsize) {
	m_field.resize(hsize);
	for(size_t i = 0; i < hsize; ++i) {
		m_field.resize(vsize);
		for(size_t j = 0; j < vsize; ++j) 
			m_field[i][j] = Unit::EUnitClass::NO_UNIT;
	}
}

void CField:set_cell(size_t x, size_t y, Unit::EUnitClass value) {
	m_field[x][y] = value;
}

Unit::EUnitClass CField::get_type(size_t x, size_t y) const {
	 return m_field[x][y];
}
