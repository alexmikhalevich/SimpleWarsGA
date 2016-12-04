#include "clogic.h"

using namespace Logic;

CUnit* CWarriorLogic::get_enemy(CUnit* cur_unit, std::vector<std::vector<CUnit*>>& enemy_team) {
	CUnit* enemy = NULL;
	CUnit* target = cur_unit->get_target();
	if(!target) {
		enemy = CGeneralLogic::enemy_in_range(cur_unit, enemy_team, AGRO_RANGE);
		if(!enemy_team[Unit::EUnitClass::WIZARD].empty()) 
			enemy = CGeneralLogic::nearest_enemy(cur_unit, enemy_team, Unit::EUnitClass::WIZARD);
		else if(!enemy_team[Unit::EUnitClass::ARCHER].empty())
			enemy = CGeneralLogic::nearest_enemy(cur_unit, enemy_team, Unit::EUnitClass::ARCHER);
		else enemy = CGeneralLogic::nearest_enemy(cur_unit, enemy_team, Unit::EUnitClass::WARRIOR);
	}
	return enemy;
}

void CWarriorLogic::process_enemy(CUnit* cur_unit, CUnit* enemy, std::vector<std::vector<ILogicObject*>>* field) {
	cur_unit->set_target(enemy);
	if(!enemy) return;
	Representation::s_point dist = CGeneralLogic::distance(cur_unit->get_position(), enemy->get_position());
	Representation::s_point position = cur_unit->get_position();
	Representation::s_point old_position = cur_unit->get_position();
	if(std::abs(dist.x) > std::abs(dist.y)) position.x += dist.x / std::abs(dist.x);
	else if(std::abs(dist.x) <= std::abs(dist.y)) position.y += dist.y / std::abs(dist.y);
	if(position.x < 0 || position.x >= field->size() || position.y < 0 || position.y >= (*field)[0].size())
		return; //TODO: throw exception?
	if((*field)[position.x][position.y] == NULL) {
		(*field)[position.x][position.y] = (*field)[old_position.x][old_position.y];
		(*field)[old_position.x][old_position.y] = NULL;
		cur_unit->set_position(position.x, position.y);
	}
	else if((*field)[position.x][position.y]->type() != Unit::EUnitClass::NO_UNIT) 
		(*field)[position.x][position.y]->take_damage(cur_unit);	//TODO: process units' deaths
	else {
		//TODO: bullet in the cell
	}
}

CUnit::CUnit(Unit::CBaseUnit* unit, Representation::CUnitRepresentation* representation) {
	m_unit = unit;
	m_representation = representation;
	m_target = NULL;
}

Representation::CUnitRepresentation* CUnit::representation() {
	return m_representation;
}

CUnit* CUnit::get_target() {
	return m_target;
}

void CUnit::set_target(CUnit* unit) {
	m_target = unit;
}

Representation::s_point CUnit::get_position() const {
	Representation::s_point res;
	res.x = m_representation->x();
	res.y = m_representation->y();
	return res; 
}

void CUnit::set_position(int x, int y) {
	m_representation->add_x(x);
	m_representation->add_y(y);
}

Unit::EUnitClass CUnit::type() const {
	return m_unit->get_class();
}

bool CUnit::side() const {
	return m_representation->side();
}

void CUnit::take_damage(CUnit* enemy) {
	m_unit->take_damage(enemy->m_unit->get_base_damage(), enemy->m_unit->damage_type());
}

CGeneralLogic::CGeneralLogic(std::vector<std::vector<ILogicObject*>>* field) {
	m_field = field;
	m_ateam.reserve(3);
	m_bteam.reserve(3);
	std::srand(time(NULL));
}

void CGeneralLogic::add_unit(Representation::CUnitRepresentation* repr) {
	if(repr->type() > 3) throw new ExInvalidUnit("unit class is greater than 3");
	CUnit* unit = new CUnit(Unit::CCreator::create_unit(repr->type()), repr);
	if(!unit->side()) m_ateam[repr->type()].push_back(unit);
	else m_bteam[repr->type()].push_back(unit);
}

void CGeneralLogic::update() {
	CWarriorLogic* logic = new CWarriorLogic;
	_update_units(m_ateam, m_bteam, Unit::EUnitClass::WARRIOR, logic);
	_update_units(m_bteam, m_ateam, Unit::EUnitClass::WARRIOR, logic); 
	delete logic;
	//TODO: update all units
}

void CGeneralLogic::_update_units(std::vector<std::vector<CUnit*>>& allies, std::vector<std::vector<CUnit*>>& enemies,
				  Unit::EUnitClass type, IUnitLogic* ulogic) {
	for(size_t i = 0; i < allies[type].size(); ++i) {
		CUnit* cur_unit = allies[type][i];
		CUnit* enemy = ulogic->get_enemy(cur_unit, enemies);
		ulogic->process_enemy(cur_unit, enemy, m_field);
	}
}

CUnit* CGeneralLogic::enemy_in_range(CUnit* cur_unit, std::vector<std::vector<CUnit*>>& enemy_team, unsigned int range) {
	Representation::s_point cur_unit_pos = cur_unit->get_position();
	for(size_t i = 0; i < 3; ++i) {
		for(size_t j = 0; j < enemy_team[i].size(); ++j) {
			CUnit* enemy_unit = enemy_team[i][j];
			Representation::s_point dist_point = CGeneralLogic::distance(cur_unit_pos, enemy_unit->get_position());
			unsigned int dist = (unsigned int)std::sqrt(dist_point.x * dist_point.x + dist_point.y * dist_point.y);
			if(dist <= range) return enemy_team[i][j];
		}
	}
}

CUnit* CGeneralLogic::nearest_enemy(CUnit* cur_unit, std::vector<std::vector<CUnit*>>& enemy_team, Unit::EUnitClass type) {
	Representation::s_point cur_unit_pos = cur_unit->get_position();
	CUnit* best_unit = NULL;
	double min_dist = 10000000.0;
	for(size_t i = 0; i < enemy_team[type].size(); ++i) {
		CUnit* enemy_unit = enemy_team[type][i];
		Representation::s_point dist_point = CGeneralLogic::distance(cur_unit_pos, enemy_unit->get_position());
		double dist = std::sqrt(dist_point.x * dist_point.x + dist_point.y * dist_point.y);
		if(min_dist > dist) {
			min_dist = dist;
			best_unit = enemy_unit;
		}
	}
	return best_unit;
}

Representation::s_point CGeneralLogic::distance(Representation::s_point first, Representation::s_point second) {
	Representation::s_point res;
	res.x = second.x - first.x;
	res.y = second.y - first.y;
	return res;
}
