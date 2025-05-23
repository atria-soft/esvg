package org.atriasoft.esvg.render;

import org.atriasoft.etk.math.Vector2f;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class Point {
	static final Logger LOGGER = LoggerFactory.getLogger(Point.class);
	public Vector2f delta = Vector2f.ZERO;
	public float len = 0;
	public Vector2f miterAxe = Vector2f.ZERO;
	public Vector2f orthoAxeNext = Vector2f.ZERO;
	public Vector2f orthoAxePrevious = Vector2f.ZERO;
	// TODO : Clean all element here ...
	public Vector2f pos; //!< position of the point
	public Vector2f posNext = Vector2f.ZERO;
	public Vector2f posPrevious = Vector2f.ZERO;
	public PointType type;

	public Point() {
		this.pos = Vector2f.ZERO;
		this.type = PointType.join;
	}

	public Point(final Vector2f pos) {
		this.pos = pos;
		this.type = PointType.join;
	}

	public Point(final Vector2f pos, final PointType type) {
		this.pos = pos;
		this.type = type;
	}

	void normalize(final Vector2f nextPoint) {
		this.delta = nextPoint.less(this.pos);
		this.len = this.delta.length();
	}

	void setEndPath() {
		if (this.type == PointType.interpolation) {
			LOGGER.warn("Request stop path of an interpolate Point");
			this.type = PointType.stop;
			return;
		}
		if (this.type == PointType.stop) {
			LOGGER.warn("Request stop path of an STOP Point");
			return;
		}
		if (this.type == PointType.start) {
			this.type = PointType.single;
			return;
		}
		this.type = PointType.stop;
	}
}
