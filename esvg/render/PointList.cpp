/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.h>
#include <esvg/render/PointList.h>

esvg::render::PointList::PointList() {
	// nothing to do ...
}

void esvg::render::PointList::addList(std::vector<esvg::render::Point>& _list) {
	m_data.push_back(_list);
	// TODO : Add a checker of correct list ...
}

void esvg::render::PointList::applyMatrix(const mat2& _transformationMatrix) {
	for (auto &it : m_data) {
		for (auto &val : it) {
			val.m_pos = _transformationMatrix * val.m_pos;
		}
	}
}


void esvg::render::PointList::display() {
	ESVG_VERBOSE(" Display list of points : size=" << m_data.size());
	for (auto &it : m_data) {
		ESVG_VERBOSE("    Find List " << it.size() << " members");
		for (int32_t iii=0;
		     iii < it.size();
		     ++iii) {
			switch (it[iii].m_type) {
				case esvg::render::Point::type_single:
					ESVG_VERBOSE("        [" << iii << "] Find Single " << it[iii].m_pos);
					break;
				case esvg::render::Point::type_start:
					ESVG_VERBOSE("        [" << iii << "] Find Start " << it[iii].m_pos);
					break;
				case esvg::render::Point::type_stop:
					ESVG_VERBOSE("        [" << iii << "] Find Stop " << it[iii].m_pos);
					break;
				case esvg::render::Point::type_interpolation:
					ESVG_VERBOSE("        [" << iii << "] Find interpolation " << it[iii].m_pos);
					break;
				case esvg::render::Point::type_join:
					ESVG_VERBOSE("        [" << iii << "] Find Join " << it[iii].m_pos);
					break;
			}
		}
	}
}
