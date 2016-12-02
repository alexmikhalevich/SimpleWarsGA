#ifndef CFIELD_H
#define CFIELD_H
#include <vector>
#include "unit.hpp"

namespace Representation {
	class IRepresentation {
		public:
			virtual int x() const = 0;
			virtual int y() const = 0;
			virtual Unit::EUnitClass type() const = 0;
	};

	class CUnitRepresentation : public IRepresentation {
		private:
			int m_x;
			int m_y;
			Unit::EUnitClass m_type;
		public:
			CUnitRepresentation(int x, int y, Unit::EUnitClass type) : m_x(x), m_y(y), m_type(type) {}
			int x() const;
			int y() const;
			Unit::EUnitClass type() const;
	};

	class CShotRepresentation : public IRepresentation {
		private:
			int m_x;
			int m_y;
		public:
			CShotRepresentation(int x, int y) : m_x(x), m_y(y) {}
			int x() const;
			int y() const;
			Unit::EUnitClass type() const;
	};

	class CField {
		private:
			std::vector<std::vector<Unit::EUnitClass>> m_field;
			std::vector<IRepresentation*> m_elements;
		public:
			CField(size_t vsize, size_t hsize);
			void set_cell(size_t x, size_t y, Unit::EUnitClass value);
			Unit::EUnitClass get_type(size_t x, size_t y) const;
	};
}
#endif //CFIELD_H
