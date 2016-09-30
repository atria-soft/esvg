/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/render/PointList.hpp>

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

std::pair<vec2, vec2> esvg::render::PointList::getViewPort() {
	std::pair<vec2, vec2> out(vec2(9999999999.0,9999999999.0),vec2(-9999999999.0,-9999999999.0));
	for (auto &it : m_data) {
		for (auto &it2 : it) {
			out.first.setMin(it2.m_pos);
			out.second.setMax(it2.m_pos);
		}
	}
	return out;
}

void esvg::render::PointList::display() {
	ESVG_VERBOSE(" Display list of points : size=" << m_data.size());
	for (auto &it : m_data) {
		ESVG_VERBOSE("    Find List " << it.size() << " members");
		for (int32_t iii=0;
		     iii < it.size();
		     ++iii) {
			switch (it[iii].m_type) {
				case esvg::render::Point::type::single:
					ESVG_VERBOSE("        [" << iii << "] Find Single " << it[iii].m_pos);
					break;
				case esvg::render::Point::type::start:
					ESVG_VERBOSE("        [" << iii << "] Find Start " << it[iii].m_pos);
					break;
				case esvg::render::Point::type::stop:
					ESVG_VERBOSE("        [" << iii << "] Find Stop " << it[iii].m_pos);
					break;
				case esvg::render::Point::type::interpolation:
					ESVG_VERBOSE("        [" << iii << "] Find interpolation " << it[iii].m_pos);
					break;
				case esvg::render::Point::type::join:
					ESVG_VERBOSE("        [" << iii << "] Find Join " << it[iii].m_pos);
					break;
			}
		}
	}
}
