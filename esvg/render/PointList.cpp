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


void esvg::render::PointList::display() {
	SVG_VERBOSE(" Display list of points : size=" << m_data.size());
	for (auto &it : m_data) {
		SVG_VERBOSE("    Find List " << it.size() << " members");
		for (int32_t iii=0;
		     iii < it.size();
		     ++iii) {
			switch (it[iii].m_type) {
				case esvg::render::Point::type_single:
					SVG_VERBOSE("        [" << iii << "] Find Single " << it[iii].m_pos);
					break;
				case esvg::render::Point::type_start:
					SVG_VERBOSE("        [" << iii << "] Find Start " << it[iii].m_pos);
					break;
				case esvg::render::Point::type_stop:
					SVG_VERBOSE("        [" << iii << "] Find Stop " << it[iii].m_pos);
					break;
				case esvg::render::Point::type_interpolation:
					SVG_VERBOSE("        [" << iii << "] Find interpolation " << it[iii].m_pos);
					break;
				case esvg::render::Point::type_join:
					SVG_VERBOSE("        [" << iii << "] Find Join " << it[iii].m_pos);
					break;
			}
		}
	}
}
