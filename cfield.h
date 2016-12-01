#include <vector>
#include "unit.hpp"

class CField {
	private:
		std::vector<std::vector<Unit::EUnitClass>> m_field;
	public:
		CField(size_t vsize, size_t hsize);
		void set_cell(size_t x, size_t y, Unit::EUnitClass value);
		Unit::EUnitClass get_type(size_t x, size_t y) const;
};
