/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/render/PointList.hpp>

esvg::render::PointList::PointList() {
	// nothing to do ...
}

void esvg::render::PointList::addList(etk::Vector<esvg::render::Point>& _list) {
	m_data.pushBack(_list);
	// TODO : Add a checker of correct list ...
}

void esvg::render::PointList::applyMatrix(const mat2x3& _transformationMatrix) {
	for (auto &it : m_data) {
		for (auto &val : it) {
			val.m_pos = _transformationMatrix * val.m_pos;
		}
	}
}

etk::Pair<vec2, vec2> esvg::render::PointList::getViewPort() {
	etk::Pair<vec2, vec2> out(vec2(9999999999.0,9999999999.0),vec2(-9999999999.0,-9999999999.0));
	for (auto &it : m_data) {
		for (auto &it2 : it) {
			out.first.setMin(it2.m_pos);
			out.second.setMax(it2.m_pos);
		}
	}
	return out;
}

void esvg::render::PointList::display() {
	Log.verbose(" Display list of points : size=" << m_data.size());
	for (auto &it : m_data) {
		Log.verbose("    Find List " << it.size() << " members");
		for (size_t iii=0;
		     iii < it.size();
		     ++iii) {
			switch (it[iii].m_type) {
				case esvg::render::Point::type::single:
					Log.verbose("        [" << iii << "] Find Single " << it[iii].m_pos);
					break;
				case esvg::render::Point::type::start:
					Log.verbose("        [" << iii << "] Find Start " << it[iii].m_pos);
					break;
				case esvg::render::Point::type::stop:
					Log.verbose("        [" << iii << "] Find Stop " << it[iii].m_pos);
					break;
				case esvg::render::Point::type::interpolation:
					Log.verbose("        [" << iii << "] Find interpolation " << it[iii].m_pos);
					break;
				case esvg::render::Point::type::join:
					Log.verbose("        [" << iii << "] Find Join " << it[iii].m_pos);
					break;
			}
		}
	}
}
