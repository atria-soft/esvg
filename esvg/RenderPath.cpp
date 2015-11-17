/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#include <esvg/debug.h>
#include <esvg/RenderPath.h>

void esvg::RenderPath::clear() {
	m_points.clear();
}

void esvg::RenderPath::stop() {
	SVG_TODO("Must be implemented");
}

void esvg::RenderPath::addPoint(const vec2& _pos) {
	m_points.push_back(_pos);
}

void esvg::RenderPath::moveTo(bool _relative, vec2 _pos) {
	if(_relative == true) {
		_pos = relativeToAbsolute(_pos);
	}
	if (m_points.size() > 0) {
		m_points.back() = _pos;
	} else {
		addPoint(_pos);
	}
}

vec2 esvg::RenderPath::relativeToAbsolute(const vec2& _value) {
	vec2 out(_value);
	if (m_points.size() > 0) {
		out += m_points.back();
	}
	return out;
}

void esvg::RenderPath::lineTo(bool _relative, vec2 _pos) {
	if(_relative == true) {
		_pos = relativeToAbsolute(_pos);
	}
	vec2 pos;
	vec2 delta;
	if (m_points.size() > 0) {
		vec2 oldPos = m_points.back();
		vec2 delta = _pos - oldPos;
		// create a basic bezier curve ...
		addPoint(oldPos + delta*0.3333f);
		addPoint(oldPos - delta*0.3333f);
		addPoint(_pos);
	} else {
		SVG_ERROR("try to lineTo whith no previous point ...");
	}
}

void esvg::RenderPath::curve3SmoothTo(bool _relative, vec2 _pos) {
	if(_relative == true) {
		_pos = relativeToAbsolute(_pos);
	}
	SVG_TODO("later ...");
}

void esvg::RenderPath::curve3To(bool _relative, vec2 _pos1, vec2 _pos) {
	if(_relative == true) {
		_pos1 = relativeToAbsolute(_pos1);
		_pos = relativeToAbsolute(_pos);
	}
	SVG_TODO("later ...");
}

void esvg::RenderPath::curve4SmoothTo(bool _relative, vec2 _pos2, vec2 _pos) {
	if(_relative == true) {
		_pos2 = relativeToAbsolute(_pos2);
		_pos = relativeToAbsolute(_pos);
	}
	SVG_TODO("later ...");
}

void esvg::RenderPath::curve4To(bool _relative, vec2 _pos1, vec2 _pos2, vec2 _pos) {
	if(_relative == true) {
		_pos1 = relativeToAbsolute(_pos1);
		_pos2 = relativeToAbsolute(_pos2);
		_pos = relativeToAbsolute(_pos);
	}
	addPoint(_pos1);
	addPoint(_pos2);
	addPoint(_pos);
}

void esvg::RenderPath::display() {
	SVG_VERBOSE("PATH : ");
	for (uint32_t iii=0; iii<m_points.size()-1; iii+=3) {
		SVG_VERBOSE("    point: " << m_points[iii]);
		SVG_VERBOSE("        v: " << m_points[iii+1]);
		SVG_VERBOSE("        v: " << m_points[iii+2]);
	}
	SVG_VERBOSE("    point: " << m_points.back());
}

