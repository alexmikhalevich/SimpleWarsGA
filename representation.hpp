#ifndef REPRESENTATION_HPP
#define REPRESENTATION_HPP

#include <SDL2/SDL_rect.h>
#include "unit.hpp"

namespace Representation 
{
	constexpr int CELL_SIZE = 10;
	struct s_point 
	{
		int x;
		int y;
	};
	class IRepresentation 
	{
		public:
			virtual SDL_Rect* rect() = 0;
			virtual Unit::EUnitClass type() const = 0;
			virtual bool side() const = 0;
			virtual int x() const = 0;
			virtual int y() const = 0;
			virtual void add_x(int add) = 0;
			virtual void add_y(int add) = 0;
	};
	class CUnitRepresentation : public IRepresentation 
	{
		private:
			SDL_Rect m_rect;
			Unit::EUnitClass m_type;
			bool m_side;
			s_point m_position;
		public:
			CUnitRepresentation(int x, int y, Unit::EUnitClass type, bool side) 
			{
				m_position.x = x / CELL_SIZE;
				m_position.y = y / CELL_SIZE;
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
			int x() const { return m_position.x; }
			int y() const { return m_position.y; }
			void add_x(int add) { m_position.x += add; }
			void add_y(int add) { m_position.y += add; }

	};
	class CShotRepresentation : public IRepresentation 
	{
		private:
			SDL_Rect m_rect;
			bool m_side;
			s_point m_position;
			//TODO: shot type?
		public:
			CShotRepresentation(int x, int y, bool side) 
			{
				m_position.x = x / CELL_SIZE;
				m_position.y = y / CELL_SIZE;
				m_rect.x = (x / CELL_SIZE) * CELL_SIZE;
				m_rect.y = (y / CELL_SIZE) * CELL_SIZE;
				m_rect.w = CELL_SIZE;
				m_rect.h = CELL_SIZE;
				m_side = side;
			}
			SDL_Rect* rect() { return &m_rect; }
			Unit::EUnitClass type() const { return Unit::EUnitClass::NO_UNIT; }
			bool side() const { return m_side; }
			int x() const { return m_position.x; }
			int y() const {return m_position.y; }
			void add_x(int add) { m_position.x += add; }
			void add_y(int add) { m_position.y += add; }
	};
};
#endif //REPRESENTATION_HPP
