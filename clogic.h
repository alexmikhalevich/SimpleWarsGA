#ifndef CLOGIC_H
#define CLOGIC_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "unit.hpp"
#include "representation.hpp"

#define EPS 0.0001

namespace Logic {
	const unsigned int AGRO_RANGE = 3;
	enum EDirection {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	class ILogicObject {
		public:
			virtual void set_representation(Representation::IRepresentation* repr) = 0;
	};
	
	class CBullet : public ILogicObject {
		public:
			CBullet();
			SDL_Rect* rect();
			void set_representation(Representation::IRepresentation* repr) { /*TODO*/ }
	};

	class CUnit : public ILogicObject {
		private:
			Unit::CBaseUnit* m_unit;
			Representation::CUnitRepresentation* m_representation;
			CUnit* m_target;
		public:
			CUnit(Unit::CBaseUnit* unit, Representation::CUnitRepresentation* representation);
			CUnit* get_target();
			void set_target(CUnit* unit);
			Representation::s_point get_position() const;
			void set_position(int x, int y);
			Representation::CUnitRepresentation* representation();
			Unit::EUnitClass type() const;
			void take_damage(CUnit* enemy);
			void set_representation(Representation::IRepresentation* repr) { /*TODO*/ } 
	};

	class IUnitLogic {
		public:
			virtual CUnit* get_enemy(CUnit* cur_unit, std::vector<CUnit*>& enemy_team) = 0;
			virtual void process_enemy(CUnit* cur_unit, CUnit* enemy, std::vector<std::vector<CUnit*>>* field) = 0;
	};

	class CWarriorLogic : public IUnitLogic {
		public:
			CUnit* get_enemy(CUnit* cur_unit, std::vector<std::vector<CUnit*>>& enemy_team);
			void process_enemy(CUnit* cur_unit, CUnit* enemy, std::vector<std::vector<CUnit*>>* field);
	};

	class CGeneralLogic {
		private:
			std::vector<std::vector<CUnit*>> m_ateam;	//side = false
			std::vector<std::vector<CUnit*>> m_bteam;	//side = true
			std::vector<CBullet*> m_bullets;
			std::vector<std::vector<ILogicObject*>>* m_field;
			void _update_units(std::vector<CUnit*>& allies, std::vector<CUnit*>& enemies, Unit::EUnitClass type, 
			 	     IUnitLogic* ulogic);
		public:
			CGeneralLogic(std::vector<std::vector<ILogicObject*>>* field);
			void add_unit(Representation::CUnitRepresentation* repr);
			void update();
			static CUnit* enemy_in_range(CUnit* cur_unit, std::vector<std::vector<CUnit*>>& enemy_team, unsigned int range);
			static CUnit* nearest_enemy(CUnit* cur_unit, std::vector<std::vector<CUnit*>>& enemy_team, Unit::EUnitClass type);
			static Representation::s_point distance(Representation::s_point first, Representation::s_point second);
	};
};

#endif //CLOGIC_H
