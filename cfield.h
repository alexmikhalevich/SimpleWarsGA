#ifndef CFIELD_H
#define CFIELD_H
#include <vector>
#include <iterator>
#include <SDL2/SDL_rect.h>
#include "clogic.h"
#include "unit.hpp"
#include "representation.hpp"

namespace Field {
	typedef std::vector<Representation::IRepresentation*>::iterator element;
	class CField {
		private:
			std::vector<std::vector<Logic::ILogicObject*>> m_field;
			std::vector<Representation::IRepresentation*> m_elements;
			element m_next_element;
			Logic::CGeneralLogic* m_logic;
		public:
			CField(size_t vsize, size_t hsize);
			~CField();
			bool get_next(element* next);
			void renew();
			void add_element(Representation::IRepresentation* representation);
			void pop_element();
			void renew_positions();
			bool element_exists(int x, int y) const;
			void activate_logic();
	};
}
#endif //CFIELD_H
