namespace Unit {
	enum EUnitClass {
		ARCHER,
		WARRIOR,
		WIZARD
	};
	
	class CBaseUnit {
		private:
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
	};

	class CCreator {
		public:
			static CBaseUnit* create(EUnitClass unit_class) {
				CBaseUnit* unit = NULL;
				if(unit_class == EUnitClass::ARCHER)
					unit = new CBaseUnit(100, 50, 25);
				else if(unit_class == EUnitClass::WARRIOR)
					unit = new CBaseUnit(100, 100, 15);
				else if(unit_class == EUnitClass::WIZARD):
					unit = new CBaseUnit(100, 0, 50);
				return unit;
			}
	};
}
