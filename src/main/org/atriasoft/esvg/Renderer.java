package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.egami.ImageFloatRGBA;
import org.atriasoft.esvg.render.DynamicColor;
import org.atriasoft.esvg.render.DynamicColorSpecial;
import org.atriasoft.esvg.render.Point;
import org.atriasoft.esvg.render.Segment;
import org.atriasoft.esvg.render.SegmentList;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
public class Renderer {
	private static final Logger LOGGER = LoggerFactory.getLogger(Renderer.class);
	private static final boolean DEBUG_MODE = false;
	protected ImageFloatRGBA buffer; // for debug
	protected EsvgDocument document; // for debug

	private int factor = 1;

	protected int interpolationRecurtionMax = 10;

	protected float interpolationThreshold = 0.25f;
	protected int nbSubScanLine = 8;
	protected Vector2i size;
	private final boolean visualDebug = false;

	public Renderer(final Vector2i size, final EsvgDocument document) {
		this(size, document, false);
	}

	public Renderer(final Vector2i size, final EsvgDocument document, final boolean visualDebug) {
		this.size = size;
		this.document = document;
		if (Renderer.DEBUG_MODE) {
			if (this.visualDebug) {
				this.factor = 20;
			}
		}
		setSize(size);
	}

	void addDebugSegment(final SegmentList listSegment) {
		if (!this.visualDebug) {
			return;
		}
		final Vector2i dynamicSize = this.size.multiply(this.factor);
		// for each lines:
		for (int yyy = 0; yyy < dynamicSize.y(); ++yyy) {
			// Reduce the number of lines in the subsampling parsing:
			final List<Segment> availlableSegmentPixel = new ArrayList<>();
			for (final Segment it : listSegment.data) {
				if (it.p0.y() * this.factor <= yyy + 1 && it.p1.y() * this.factor >= (yyy)) {
					availlableSegmentPixel.add(it);
				}
			}
			//find all the segment that cross the middle of the line of the center of the pixel line:
			final float subSamplingCenterPos = yyy + 0.5f;
			final List<Segment> availlableSegment = new ArrayList<>();
			// find in the subList ...
			for (final Segment it : availlableSegmentPixel) {
				if (it.p0.y() * this.factor <= subSamplingCenterPos
						&& it.p1.y() * this.factor >= subSamplingCenterPos) {
					availlableSegment.add(it);
				}
			}
			// x position, angle
			for (final Segment it : availlableSegment) {
				final Vector2f delta = it.p0.multiply(this.factor).less(it.p1.multiply(this.factor));
				// x = coefficent*y+bbb;
				final float coefficient = delta.x() / delta.y();
				final float bbb = it.p0.x() * this.factor - coefficient * it.p0.y() * this.factor;
				final float xpos = coefficient * subSamplingCenterPos + bbb;
				if (xpos >= 0 && xpos < dynamicSize.x() && yyy >= 0 && yyy < dynamicSize.y()) {
					if (it.direction == 1.0f) {
						this.buffer.setColor((int) xpos, yyy, Color.BLUE);
					} else {
						this.buffer.setColor((int) xpos, yyy, Color.DARK_RED);
					}
				}
			}
		}
		// for each colomn:
		for (int xxx = 0; xxx < dynamicSize.x(); ++xxx) {
			// Reduce the number of lines in the subsampling parsing:
			final List<Segment> availlableSegmentPixel = new ArrayList<>();
			for (final Segment it : listSegment.data) {
				if ((it.p0.x() * this.factor <= xxx + 1 && it.p1.x() * this.factor >= (xxx))
						|| (it.p0.x() * this.factor >= xxx + 1 && it.p1.x() * this.factor <= (xxx))) {
					availlableSegmentPixel.add(it);
				}
			}
			//find all the segment that cross the middle of the line of the center of the pixel line:
			final float subSamplingCenterPos = xxx + 0.5f;
			final List<Segment> availlableSegment = new ArrayList<>();
			// find in the subList ...
			for (final Segment it : availlableSegmentPixel) {
				if ((it.p0.x() * this.factor <= subSamplingCenterPos && it.p1.x() * this.factor >= subSamplingCenterPos)
						|| (it.p0.x() * this.factor >= subSamplingCenterPos
								&& it.p1.x() * this.factor <= subSamplingCenterPos)) {
					availlableSegment.add(it);
				}
			}
			// x position, angle
			for (final Segment it : availlableSegment) {
				final Vector2f delta = it.p0.multiply(this.factor).less(it.p1.multiply(this.factor));
				// x = coefficent*y+bbb;
				if (delta.x() == 0) {
					continue;
				}
				final float coefficient = delta.y() / delta.x();
				final float bbb = it.p0.y() * this.factor - coefficient * it.p0.x() * this.factor;
				final float ypos = coefficient * subSamplingCenterPos + bbb;
				if (ypos >= 0 && ypos < dynamicSize.y() && xxx >= 0 && xxx < dynamicSize.y()) {
					if (it.direction == 1.0f) {
						this.buffer.setColor(xxx, (int) ypos, Color.BLUE);
					} else {
						this.buffer.setColor(xxx, (int) ypos, Color.DARK_RED);
					}
				}
			}
		}
	}

	ImageFloatRGBA getData() {
		return this.buffer;
	}

	int getInterpolationRecurtionMax() {
		return this.interpolationRecurtionMax;
	}

	float getInterpolationThreshold() {
		return this.interpolationThreshold;
	}

	public EsvgDocument getMainDocument() {
		return this.document;
	}

	int getNumberSubScanLine() {
		return this.nbSubScanLine;
	}

	Vector2i getSize() {
		return this.size;
	}

	protected Color mergeColor(final Color base, final Color integration) {
		/*
		if (integration.a() < base.a()) {
			result = integration;
			integration = base;
			base = result;
		}
		*/
		/*
		float r = (integration.a() * integration.r() + base.a() * (1.0f - integration.a()) * base.r());
		float g = (integration.a() * integration.g() + base.a() * (1.0f - integration.a()) * base.g());
		float b = (integration.a() * integration.b() + base.a() * (1.0f - integration.a()) * base.b());
		float a = (integration.a() + base.a() * (1.0f - integration.a()));
		if (a != 0.0f) {
			float reverse = 1.0f / a;
			r *= reverse;
			g *= reverse;
			b *= reverse;
		}
		return new Color(r, g, b, a);
		*/
		final float a1 = integration.a(); // alpha over
		final float a0 = base.a(); // alpha under

		final float a = a1 + a0 * (1 - a1);
		final float aCalc = a != 0 ? 1 / a : 1;
		
		final float r = (integration.r() * a1 + base.r() * a0 * (1 - a1)) * aCalc;
		final float g = (integration.g() * a1 + base.g() * a0 * (1 - a1)) * aCalc;
		final float b = (integration.b() * a1 + base.b() * a0 * (1 - a1)) * aCalc;
		
		return new Color(r, g, b, a);
	}

	public void print(
			final Weight weightFill,
			final DynamicColor colorFill,
			final Weight weightStroke,
			final DynamicColor colorStroke,
			final float opacity) {
		final long startTime = System.currentTimeMillis();
		if (colorFill != null) {
			//colorFill.setViewPort(Pair<Vector2f, Vector2f>(new Vector2f(0,0), Vector2f(sizeX, sizeY)));
			colorFill.generate(this.document);
		}
		if (colorStroke != null) {
			//colorStroke.setViewPort(Pair<Vector2f, Vector2f>(new Vector2f(0,0), Vector2f(sizeX, sizeY)));
			colorStroke.generate(this.document);
		}
		// all together
		for (int yyy = 0; yyy < this.size.y(); ++yyy) {
			final long stopTime2 = System.currentTimeMillis();
			LOGGER.trace("take time to gnerate: " + (stopTime2 - startTime) + " for " + yyy + "/" + this.size.y());
			for (int xxx = 0; xxx < this.size.x(); ++xxx) {

				final Vector2i pos = new Vector2i(xxx, yyy);
				final float valueFill = weightFill.get(pos);
				final float valueStroke = weightStroke.get(pos);
				// calculate merge of stroke and fill value:
				Color intermediateColorFill = Color.NONE;

				Color intermediateColorStroke = Color.NONE;
				if (colorFill != null && valueFill != 0.0f) {
					intermediateColorFill = colorFill.getColor(pos);
					intermediateColorFill = intermediateColorFill.withA(intermediateColorFill.a() * valueFill);
				}
				if (colorStroke != null && valueStroke != 0.0f) {
					intermediateColorStroke = colorStroke.getColor(pos);
					intermediateColorStroke = intermediateColorStroke.withA(intermediateColorStroke.a() * valueStroke);
				}
				Color intermediateColor = mergeColor(intermediateColorFill, intermediateColorStroke);
				intermediateColor = intermediateColor.withA(intermediateColor.a() * opacity);
				if (Renderer.DEBUG_MODE) {
					for (int deltaY = 0; deltaY < this.factor; deltaY++) {
						for (int deltaX = 0; deltaX < this.factor; deltaX++) {
							final int idx = xxx * this.factor + deltaX;
							final int idy = yyy * this.factor + deltaY;
							this.buffer.mergeColor(idx, idy, intermediateColor);
						}
					}
				} else {
					this.buffer.mergeColor(xxx, yyy, intermediateColor);
				}
			}
		}

		if (Renderer.DEBUG_MODE) {

			// display the gradient position:
			if (colorFill instanceof final DynamicColorSpecial tmpColor) {
				final SegmentList listSegment = new SegmentList();
				// Display bounding box
				listSegment.addSegment(new Point(tmpColor.viewPort.first),
						new Point(new Vector2f(tmpColor.viewPort.first.x(), tmpColor.viewPort.second.y())), false);
				listSegment.addSegment(
						new Point(new Vector2f(tmpColor.viewPort.first.x(), tmpColor.viewPort.second.y())),
						new Point(tmpColor.viewPort.second), false);
				listSegment.addSegment(new Point(tmpColor.viewPort.second),
						new Point(new Vector2f(tmpColor.viewPort.second.x(), tmpColor.viewPort.first.y())), false);
				listSegment.addSegment(
						new Point(new Vector2f(tmpColor.viewPort.second.x(), tmpColor.viewPort.first.y())),
						new Point(tmpColor.viewPort.first), false);
				listSegment.applyMatrix(tmpColor.matrix);
				// display the gradient axis
				listSegment.addSegment(new Point(tmpColor.pos1), new Point(tmpColor.pos2), false);
				/*
					Matrix2x3f this.matrix;
					Pair<Vector2f, Vector2f> this.viewPort;
					Vector2f this.pos1;
					Vector2f this.pos2;
				*/
				addDebugSegment(listSegment);
			}
		}
		final long stopTime = System.currentTimeMillis();
		LOGGER.trace("take time to generate: " + (stopTime - startTime));
	}

	public void setInterpolationRecurtionMax(final int value) {
		this.interpolationRecurtionMax = FMath.avg(1, value, 200);
	}

	void setInterpolationThreshold(final float value) {
		this.interpolationThreshold = FMath.avg(0.0f, value, 20000.0f);
	}

	void setNumberSubScanLine(final int value) {
		this.nbSubScanLine = FMath.avg(1, value, 200);
	}

	public void setSize(final Vector2i size) {
		this.size = size;
		if (Renderer.DEBUG_MODE) {
			this.buffer = new ImageFloatRGBA(this.size);
		} else {
			this.buffer = new ImageFloatRGBA(this.size.multiply(this.factor));
		}
	}

}
