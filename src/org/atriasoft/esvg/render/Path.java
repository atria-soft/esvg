package org.atriasoft.esvg.render;

import java.util.List;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

class Path {
	public List<Element> listElement;
	
	SegmentList debugInformation;
	
	public Path() {
		
	}
	
	void clear();
	
	void stop();
	
	void close(final boolean _relative=false);
	
	void moveTo(final boolean _relative, const Vector2f& _pos);
	
	void lineTo(final boolean _relative, const Vector2f& _pos);
	
	void lineToH(boolean _relative, float _posX);
	
	void lineToV(boolean _relative, float _posY);
	
	void curveTo(final boolean _relative, const Vector2f& _pos1, const Vector2f& _pos2, const Vector2f& _pos);
	
	void smoothCurveTo(final boolean _relative, const Vector2f& _pos2, const Vector2f& _pos);
	
	void bezierCurveTo(final boolean _relative, const Vector2f& _pos1, const Vector2f& _pos);
	
	void bezierSmoothCurveTo(final boolean _relative, const Vector2f& _pos);
	
	void ellipticTo(final boolean _relative,
				                const Vector2f& _radius,
				                float _angle,
				                boolean _largeArcFlag,
				                boolean _sweepFlag,
				                const Vector2f& _pos);
	
	void display(int _spacing);esvg::render::PointList generateListPoints(final int _level, final int _recurtionMax = 10, float _threshold = 0.25f);
		};
}}
