package org.atriasoft.esvg.render;

import java.awt.Shape;
import java.awt.geom.GeneralPath;

import org.apache.batik.parser.AWTPathProducer;
import org.apache.batik.parser.PathParser;

/**
 * Converts SVG path {@code d} attribute strings to {@link java.awt.Shape}
 * using Apache Batik's path parser.
 */
public final class SvgPathToShape {

	/**
	 * Parse an SVG path data string into a Java2D Shape.
	 * @param d the SVG path data (e.g. "M10 10 L20 20 Z")
	 * @return the parsed Shape, or an empty GeneralPath if d is null/empty
	 */
	public static Shape parsePath(final String d) {
		if (d == null || d.isEmpty()) {
			return new GeneralPath();
		}
		final PathParser parser = new PathParser();
		final AWTPathProducer producer = new AWTPathProducer();
		parser.setPathHandler(producer);
		parser.parse(d);
		return producer.getShape();
	}

	private SvgPathToShape() {}
}
