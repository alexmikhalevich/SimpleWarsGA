#ifndef REPRESENTATION_HPP
#define REPRESENTATION_HPP

namespace Representation {
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
			CUnitRepresentation(int x, int y, Unit::EUnitClass type, bool side) {
				m_x = x / CELL_SIZE;
				m_y = y / CELL_SIZE;
				m_rect.x = (x / CELL_SIZE) * CELL_SIZE; 
				m_rect.y = (y / CELL_SIZE) * CELL_SIZE;
				m_rect.w = CELL_SIZE;
				m_rect.h = CELL_SIZE;
				m_type = type;
				m_side = side;
			}
			SDL_Rect* rect() { return &m_rect; }
			Unit::EUnitClass type() const { return m_type; }
			bool side() const { return m_side; }
			int x() const { return m_x; }
			int y() const { return m_y; }
	};
	class CShotRepresentation : public IRepresentation {
		private:
			SDL_Rect m_rect;
			bool m_side;
			int m_x;
			int m_y;
			//TODO: shot type?
		public:
			CShotRepresentation(int x, int y, bool side) {
				m_x = x / CELL_SIZE;
				m_y = y / CELL_SIZE;
				m_rect.x = (x / CELL_SIZE) * CELL_SIZE;
				m_rect.y = (y / CELL_SIZE) * CELL_SIZE;
				m_rect.w = CELL_SIZE;
				m_rect.h = CELL_SIZE;
				m_side = side;
			}
			SDL_Rect* rect() { return &m_rect; }
			Unit::EUnitClass type() const { return Unit::EUnitClass::NO_UNIT; }
			bool side() const { return m_side; }
			int x() const { return m_x; }
			int y() const {return m_y; }
	};
};
#endif //REPRESENTATION_HPP
