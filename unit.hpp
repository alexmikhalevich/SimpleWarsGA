#ifndef UNIT_HPP
#define UNIT_HPP
#include <vector>

namespace Unit {
	enum EUnitClass {
		ARCHER,
		WARRIOR,
		WIZARD,
		NO_UNIT
	};

	enum EDamageType {
		PHYSICAL, 
		MAGICAL
	};
	
	class CBaseUnit {
		protected:
			unsigned int m_hp;
			unsigned int m_armor;
			unsigned int m_base_damage;
			EUnitClass m_class;
		public:
			CBaseUnit() = delete;
			CBaseUnit(unsigned int hp, unsigned int armor, unsigned int base_damage, EUnitClass unit_class) : 
				m_hp(hp), m_armor(armor), m_base_damage(base_damage), m_class(unit_class) {}
			CBaseUnit(const CBaseUnit& unit) {
				m_hp = unit.m_hp;
				m_armor = unit.m_armor;
				m_base_damage = unit.m_base_damage;
				m_class = unit.m_class;
			}
			void set_hp(unsigned int hp) { m_hp = hp; }
			void set_base_damage(unsigned int damage) { m_base_damage = damage; }
			void set_armor(unsigned int armor) { m_armor = armor; }
			unsigned int get_hp() const { return m_hp; }
			unsigned int get_base_damage() const { return m_base_damage; }
			unsigned int get_armor() const { return m_armor; }
			EUnitClass get_class() const { return m_class; }
			void take_damage(unsigned int damage, EDamageType type) {
				if(type == EDamageType::PHYSICAL) {
					if(m_armor >= damage) m_armor -= damage;
					else {
						damage -= m_armor;
						m_armor = 0;
						m_hp = std::max((unsigned int)0, m_hp - damage);
					}
				}
				else if(type == EDamageType::MAGICAL) m_hp = std::max((unsigned int)0, m_hp - damage);
			}
	};

	class CArmy : public CBaseUnit {
		protected:
			size_t m_size;
			unsigned int m_base_hp;
			unsigned int m_base_armor;
			unsigned int m_base_damage;
		public:
			CArmy() = delete;
			CArmy(unsigned int hp, unsigned int armor, unsigned int base_damage, size_t army_size, EUnitClass unit_class) 
				: CBaseUnit(hp * army_size, armor * army_size, base_damage * army_size, unit_class), m_size(army_size),
				  m_base_hp(hp), m_base_armor(armor), m_base_damage(base_damage) {}
			std::vector<CBaseUnit*> disband() const {
				std::vector<CBaseUnit*> units(m_size);
				unsigned int unit_hp = m_hp / m_size;
				unsigned int unit_armor = m_armor / m_size;
				for(size_t i = 0; i < m_size - 1; ++i) 
					units.push_back(new CBaseUnit(unit_hp, unit_armor, m_base_damage, m_class));
				unit_hp += m_hp - unit_hp * m_size;
				unit_armor += m_armor - unit_armor * m_size;
				units.push_back(new CBaseUnit(unit_hp, unit_armor, m_base_damage, m_class));
				return units;
			}
	};

	class CCreator {
		public:
			static CBaseUnit* create_unit(EUnitClass unit_class) {
				CBaseUnit* unit = NULL;
				if(unit_class == EUnitClass::ARCHER)
					unit = new CBaseUnit(100, 50, 25, EUnitClass::ARCHER);
				else if(unit_class == EUnitClass::WARRIOR)
					unit = new CBaseUnit(100, 100, 15, EUnitClass::WARRIOR);
				else if(unit_class == EUnitClass::WIZARD)
					unit = new CBaseUnit(100, 0, 50, EUnitClass::WIZARD);
				return unit;
			}
			static CArmy* create_army(EUnitClass unit_class, size_t army_size) {
				CArmy* army = NULL;
				if(unit_class == EUnitClass::ARCHER)
					army = new CArmy(100, 50, 25, army_size, EUnitClass::ARCHER);
				else if(unit_class == EUnitClass::WARRIOR)
					army = new CArmy(100, 100, 15, army_size, EUnitClass::WARRIOR);
				else if(unit_class == EUnitClass::WIZARD)
					army = new CArmy(100, 0, 50, army_size, EUnitClass::WIZARD);
				return army;
			}
	};
};
#endif //UNIT_HPP
