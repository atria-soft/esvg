/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Point.h>
#include <esvg/debug.h>

void esvg::render::Point::setEndPath() {
	if (m_type == esvg::render::Point::type::interpolation) {
		ESVG_WARNING("Request stop path of an interpolate Point");
		m_type = esvg::render::Point::type::stop;
		return;
	}
	if (m_type == esvg::render::Point::type::stop) {
		ESVG_WARNING("Request stop path of an STOP Point");
		return;
	}
	if (m_type == esvg::render::Point::type::start) {
		m_type = esvg::render::Point::type::single;
		return;
	}
	m_type = esvg::render::Point::type::stop;
}

void esvg::render::Point::normalize(const vec2& _nextPoint) {
	m_delta = _nextPoint - m_pos;
	m_len = m_delta.length();
}

