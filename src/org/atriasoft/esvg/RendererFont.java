package org.atriasoft.esvg;

import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.ArraysTools;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
public class RendererFont {
	protected float[][] buffer; // for debug
	protected EsvgFont document; // for debug
	
	protected int interpolationRecurtionMax = 10;
	
	protected float interpolationThreshold = 0.25f;
	protected int nbSubScanLine = 8;
	protected Vector2i size;
	
	public RendererFont(final Vector2i size, final EsvgFont document) {
		this(size, document, false);
	}
	
	public RendererFont(final Vector2i size, final EsvgFont document, final boolean visualDebug) {
		this.size = size;
		this.document = document;
		setSize(size);
	}
	
	float[][] getData() {
		return this.buffer;
	}
	
	int getInterpolationRecurtionMax() {
		return this.interpolationRecurtionMax;
	}
	
	float getInterpolationThreshold() {
		return this.interpolationThreshold;
	}
	
	int getNumberSubScanLine() {
		return this.nbSubScanLine;
	}
	
	Vector2i getSize() {
		return this.size;
	}
	
	protected float mergeColor(final float base, final float integration) {
		return FMath.avg(0.0f, integration + base, 1.0f);
	}
	
	public void print(final Weight weightFill, final Weight weightStroke, final float opacity) {
		// all together
		for (int yyy = 0; yyy < this.size.y(); ++yyy) {
			for (int xxx = 0; xxx < this.size.x(); ++xxx) {
				
				Vector2i pos = new Vector2i(xxx, yyy);
				float valueFill = weightFill.get(pos);
				float valueStroke = weightStroke.get(pos);
				// calculate merge of stroke and fill value:
				Color intermediateColorFill = Color.NONE;
				/*
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
				this.buffer[yyy][xxx] = mergeColor(this.buffer[yyy][xxx], intermediateColor);*/
			}
		}
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
		this.buffer = new float[this.size.y()][this.size.x()];
		ArraysTools.fill2(this.buffer, 0.0f);
	}
	
}
