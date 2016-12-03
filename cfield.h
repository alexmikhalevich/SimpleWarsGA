#ifndef CFIELD_H
#define CFIELD_H
#include <vector>
#include <iterator>
#include <SDL2/SDL_rect.h>
#include "unit.hpp"

namespace Representation {
	constexpr int CELL_SIZE = 10;
	class IRepresentation {
		public:
			virtual SDL_Rect* rect() = 0;
			virtual Unit::EUnitClass type() const = 0;
			virtual bool side() const = 0;
			virtual int x() const = 0;
			virtual int y() const = 0;
	};
	typedef std::vector<IRepresentation*>::iterator element;
	class CUnitRepresentation : public IRepresentation {
		private:
			SDL_Rect m_rect;
			Unit::EUnitClass m_type;
			bool m_side;
			int m_x;
			int m_y;
		public:
			CUnitRepresentation(int x, int y, Unit::EUnitClass type, bool side);
			SDL_Rect* rect();
			Unit::EUnitClass type() const;
			bool side() const;
			int x() const;
			int y() const;
	};

	class CShotRepresentation : public IRepresentation {
		private:
			SDL_Rect m_rect;
			bool m_side;
			int m_x;
			int m_y;
			//TODO: shot type?
		public:
			CShotRepresentation(int x, int y, bool side);
			SDL_Rect* rect();
			Unit::EUnitClass type() const;
			bool side() const;
			int x() const;
			int y() const;
	};

	class CField {
		private:
			std::vector<std::vector<IRepresentation*>> m_field;
			std::vector<IRepresentation*> m_elements;
			element m_next_element;
		public:
			CField(size_t vsize, size_t hsize);
			bool get_next(element* next);
			void renew();
			void add_element(IRepresentation* representation);
			void pop_element();
			void renew_positions();
			bool element_exists(int x, int y) const;
	};
}
#endif //CFIELD_H
