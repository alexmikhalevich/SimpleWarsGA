#ifndef CFIELD_H
#define CFIELD_H
#include <vector>
#include <iterator>
#include <SDL2/SDL_rect.h>
#include "unit.hpp"

namespace Representation {
	constexpr int CELL_SIZE = 20;
	class IRepresentation {
		public:
			virtual SDL_Rect* rect() = 0;
			virtual Unit::EUnitClass type() const = 0;
			virtual bool side() const = 0;
	};
	typedef std::vector<IRepresentation*>::iterator element;
	class CUnitRepresentation : public IRepresentation {
		private:
			SDL_Rect m_rect;
			Unit::EUnitClass m_type;
			bool m_side;
		public:
			CUnitRepresentation(int xupperleft, int yupperleft, Unit::EUnitClass type, bool side);
			SDL_Rect* rect();
			Unit::EUnitClass type() const;
			bool side() const;
	};

	class CShotRepresentation : public IRepresentation {
		private:
			SDL_Rect m_rect;
			bool m_side;
			//TODO: shot type?
		public:
			CShotRepresentation(int xupperleft, int yupperleft, bool side);
			SDL_Rect* rect();
			Unit::EUnitClass type() const;
			bool side() const;
	};

	class CField {
		private:
			//std::vector<std::vector<Unit::EUnitClass>> m_field;
			std::vector<IRepresentation*> m_elements;
			element m_next_element;
		public:
			CField(/*size_t vsize, size_t hsize*/);
			bool get_next(element* next);
			void renew();
			void add_element(IRepresentation* representation);
			void pop_element();
			void renew_positions();
	};
}
#endif //CFIELD_H
