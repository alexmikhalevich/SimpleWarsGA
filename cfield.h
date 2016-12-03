#ifndef CFIELD_H
#define CFIELD_H
#include <vector>
#include <iterator>
#include <SDL2/SDL_rect.h>
#include "clogic.h"
#include "unit.hpp"
#include "representation.hpp"

namespace Field {
	constexpr int CELL_SIZE = 10;
	class CField {
		private:
			std::vector<std::vector<Representation::IRepresentation*>> m_field; //TODO: store here Unit::BaseUnit
			std::vector<Representation::IRepresentation*> m_elements;
			element m_next_element;
			CLogic* m_logic;
		public:
			CField(size_t vsize, size_t hsize);
			bool get_next(element* next);
			void renew();
			void add_element(Representation::IRepresentation* representation);
			void pop_element();
			void renew_positions();
			bool element_exists(int x, int y) const;
	};
}
#endif //CFIELD_H
