/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <esvg/render/Element.h>
#include <esvg/debug.h>

esvg::render::ElementElliptic::ElementElliptic(bool _relative,
                                               const vec2& _radius, // in m_vec1
                                               float _angle,
                                               bool _largeArcFlag,
                                               bool _sweepFlag,
                                               const vec2& _pos):
  Element(esvg::render::path_elliptic, _relative) {
	m_pos1 = _radius;
	m_pos = _pos;
	m_angle = _angle;
	m_largeArcFlag = _largeArcFlag;
	m_sweepFlag = _sweepFlag;
}


std::string esvg::render::ElementElliptic::display() const {
	return std::string("pos=") + etk::to_string(m_pos)
	       + " radius=" + etk::to_string(m_pos1)
	       + " angle=" + etk::to_string(m_angle)
	       + " largeArcFlag=" + etk::to_string(m_largeArcFlag)
	       + " sweepFlag=" + etk::to_string(m_sweepFlag);
}