/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/render/Element.hpp>
#include <esvg/debug.hpp>

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


etk::String esvg::render::ElementElliptic::display() const {
	return etk::String("pos=") + etk::toString(m_pos)
	       + " radius=" + etk::toString(m_pos1)
	       + " angle=" + etk::toString(m_angle)
	       + " largeArcFlag=" + etk::toString(m_largeArcFlag)
	       + " sweepFlag=" + etk::toString(m_sweepFlag);
}