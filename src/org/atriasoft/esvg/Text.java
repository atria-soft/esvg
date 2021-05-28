package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.font.Glyph;
import org.atriasoft.esvg.internal.Log;
import org.atriasoft.esvg.render.DynamicColor;
import org.atriasoft.esvg.render.PathModel;
import org.atriasoft.esvg.render.PointList;
import org.atriasoft.esvg.render.SegmentList;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.exml.model.XmlElement;
import org.atriasoft.exml.model.XmlNode;
import org.atriasoft.exml.model.XmlText;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
public class Text extends Base {
	private float fontSize = 42;
	private Vector2f position = Vector2f.ZERO;
	private final List<TextSpan> texts = new ArrayList<>();
	
	public Text(final PaintState parentPaintState) {
		super(parentPaintState);
	}

	public Text(final Vector2f position, final float fontSize, final String decoratedText, final PaintState parentPaintState) {
		super(parentPaintState);
		this.position = position;
		this.fontSize = fontSize;
		this.texts.add(new TextSpan(position, decoratedText, FontProperty.DEFAULT_FONT.withSize(fontSize), parentPaintState.clone()));
	}
	public Text(final Vector2f position, final String fontName,final float fontSize, final String decoratedText, final PaintState parentPaintState) {
		super(parentPaintState);
		this.position = position;
		this.fontSize = fontSize;
		this.texts.add(new TextSpan(position, decoratedText, FontProperty.DEFAULT_FONT.withSize(fontSize).withFontName(fontName), parentPaintState.clone()));
	}
	
	@Override
	public void display(final int spacing) {
		Log.verbose(spacingDist(spacing) + "Text : ");
		for (TextSpan elem : this.texts) {
			Log.debug(spacingDist(spacing + 1) + elem.toString());
		}
	}
	
	@Override
	public void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW esvg::Text                   ==> position = " + this.position);
		if (this.texts.size() == 0) {
			Log.verbose(spacingDist(level + 1) + "No text ...");
			return;
		}
		boolean withKerning = true;
		
		for (TextSpan elem : this.texts) {
			// get the font or a generic font of the program.
			EsvgFont font = FontCache.getFont(elem.fontState().fontName(), elem.fontState().bold(), elem.fontState().italic());
			if (font == null) {
				Log.error("Can not get the font :" + elem.fontState());
				return;
			}
			
			int realSize = font.calculateFontRealHeight((int) elem.fontState().fontSize());
			float scale = realSize / font.getUnitsPerEm();
			//Log.warning("elem.fontState() =" + elem.fontState());
			//Log.warning("scale =" + scale + " font size = " + elem.fontState().fontSize() + "  realSize=" + realSize);
			
			float offsetWriting = 0;
			int lastValue = 0;
			for (char uVal : elem.text().toCharArray()) {
				Log.verbose(spacingDist(level) + "                                 elem.position = " + elem.position());
				Glyph glyph = font.getGlyph(uVal);
				if (glyph == null) {
					//lastValue = uVal;
					continue;
				}
				if (withKerning) {
					offsetWriting -= glyph.getKerning(lastValue) * scale;
					Log.verbose("    ==> kerning offset = " + (glyph.getKerning(lastValue) * scale));
					lastValue = uVal;
				}
				
				float advenceXLocal = glyph.getHorizAdvX() * scale;
				
				//Matrix2x3f mtx = this.transformMatrix;
				Vector2f tranlate = new Vector2f(elem.position().x() + offsetWriting, elem.position().y() - font.getDescent() * scale);
				Log.verbose("translate : " + tranlate);
				Matrix2x3f translateGlyph = Matrix2x3f.createTranslate(tranlate);
				Matrix2x3f scaleGlyph = Matrix2x3f.createScale(new Vector2f(scale, -scale));
				
				//Matrix2x3f translateGlyph = Matrix2x3f.createTranslate(tranlate).multiply(Matrix2x3f.createScale(scale));
				//mtx = translateGlyph.multiply(this.transformMatrix);
				//mtx = mtx.multiply(translateGlyph);
				//mtx = mtx.multiply(basicTrans);
				
				//Matrix2x3f mtx = this.transformMatrix;
				//mtx = mtx.multiply(basicTrans);
				
				Matrix2x3f mtx = scaleGlyph;
				mtx = mtx.multiply(translateGlyph);
				mtx = mtx.multiply(this.transformMatrix);
				mtx = mtx.multiply(basicTrans);
				//Matrix2x3f mtx = this.transformMatrix;
				//mtx = mtx.multiply(basicTrans);
				
				PathModel listElement = glyph.getModel();
				if (listElement != null) {
					//--------------------------------------------------
					// -- Generate Fill weight
					//--------------------------------------------------
					PointList listPoints = listElement.generateListPoints(level, myRenderer.getInterpolationRecurtionMax(), myRenderer.getInterpolationThreshold());
					DynamicColor colorFill = DynamicColor.createColor(this.paint.fill, mtx);
					Weight tmpFill = new Weight();
					// Check if we need to display background
					if (colorFill != null) {
						SegmentList listSegmentFill = new SegmentList();
						listSegmentFill.createSegmentList(listPoints);
						colorFill.setViewPort(listSegmentFill.getViewPort());
						listSegmentFill.applyMatrix(mtx);
						// TODO but need check ... listSegmentFill.clearHorizontals();
						// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
						tmpFill.generate(myRenderer.getSize(), myRenderer.getNumberSubScanLine(), listSegmentFill);
					}
					
					//--------------------------------------------------
					// -- Generate Stroke weight
					//--------------------------------------------------
					
					Weight tmpStroke = new Weight();
					DynamicColor colorStroke = null;
					if (this.paint.strokeWidth > 0.0f) {
						colorStroke = DynamicColor.createColor(this.paint.stroke, mtx);
						if (colorStroke == null) {
							Log.verbose("Color stroke is null: ...");
						} else {
							// check if we need to display stroke:
							SegmentList listSegmentStroke = new SegmentList();
							listSegmentStroke.createSegmentListStroke(listPoints, this.paint.strokeWidth, this.paint.lineCap, this.paint.lineJoin, this.paint.miterLimit);
							colorStroke.setViewPort(listSegmentStroke.getViewPort());
							listSegmentStroke.applyMatrix(mtx);
							// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
							tmpStroke.generate(myRenderer.getSize(), myRenderer.getNumberSubScanLine(), listSegmentStroke);
						}
					}
					// add on images:
					myRenderer.print(tmpFill, colorFill, tmpStroke, colorStroke, this.paint.opacity);
				}
				offsetWriting += advenceXLocal;
				//Log.warning("offset X =" + offsetWriting + " + " + advenceXLocal + "    " + uVal);
			}
		}
	}
	
	@Override
	public boolean parseXML(final XmlElement element, final Matrix2x3f parentTrans, final Dynamic<Vector2f> sizeMax) {
		// line must have a minimum size...
		this.paint.strokeWidth = 0;
		if (element == null) {
			return false;
		}
		parseTransform(element);
		parsePaintAttr(element);
		
		// add the property of the parrent modifications ...
		this.transformMatrix = this.transformMatrix.multiply(parentTrans);
		
		boolean italic = false;
		String fontStyle = element.getAttribute("font-style", "normal");
		if ("italic".equals(fontStyle)) {
			italic = true;
		} else if ("normal".equals(fontStyle)) {
			italic = false;
		} else {
			Log.error("can not parse font-style='" + fontStyle + "' support ['normal', 'italic']");
		}
		boolean bold = false;
		String fontWeight = element.getAttribute("font-weight", "normal");
		if ("bold".equals(fontWeight)) {
			bold = true;
		} else if ("normal".equals(fontWeight)) {
			bold = false;
		} else {
			Log.error("can not parse font-weight='" + fontWeight + "' support ['normal', 'bold']");
		}
		String fontFamily = element.getAttribute("font-family", "FreeSans");
		if (fontStyle.contains(";")) {
			fontFamily = fontFamily.split(";")[0];
		}
		Log.info("Get font family: '" + fontFamily + "'");
		
		float fontSize = parseLength(element.getAttribute("font-size", "50"));
		this.position = Vector2f.ZERO;
		
		String content = element.getAttribute("x", "");
		if (content.length() != 0) {
			this.position = this.position.withX(parseLength(content));
		}
		content = element.getAttribute("y", "");
		if (content.length() != 0) {
			this.position = this.position.withY(parseLength(content));
		}
		
		// parse all subElement in the Text <TSPAN/>
		for (XmlNode elem : element.getNodes()) {
			if (elem instanceof XmlElement elementSpan && "tspan".equals(elementSpan.getValue())) {
				
			} else if (elem instanceof XmlText elementText) {
				this.texts.add(new TextSpan(this.position, elementText.getValue(), new FontProperty(fontFamily, fontSize, bold, italic), this.paint.clone()));
			} else {
				Log.warning("not managed element : " + elem);
			}
		}
		
		//sizeMax.value = Vector2f.max(this.startPos, this.stopPos);
		return true;
		
	}
	/*
	public Weight render(final String data, final int fontSize, final boolean withKerning) {
		int widthOut = calculateWidth(data, fontSize, withKerning);
		
		int realSize = calculateFontRealHeight(fontSize);
		float scale = realSize / (float) this.unitsPerEm;
		
		Weight weight = new Weight(new Vector2i(widthOut, realSize));
		
		int offsetWriting = 0;
		int lastValue = 0;
		for (char uVal : data.toCharArray()) {
			Glyph glyph = getGlyph(uVal);
			if (glyph == null) {
				lastValue = uVal;
				continue;
			}
			if (withKerning) {
				offsetWriting -= glyph.getKerning(lastValue) * scale;
				Log.info("    ==> kerning offset = " + (glyph.getKerning(lastValue) * scale));
				lastValue = uVal;
			}
			
			float advenceXLocal = glyph.getHorizAdvX() * scale;
			
			RenderingConfig config = new RenderingConfig(10, 0.25f, 8);
			Matrix2x3f transform = Matrix2x3f.createTranslate(new Vector2f(0, -this.descent)).multiply(Matrix2x3f.createScale(scale));
			PathModel model = glyph.getModel();
			if (model != null) {
				Weight redered = model.drawFill(calculateWidthRendering((int) uVal, fontSize), transform, 8, config);
				weight.fusion(redered, offsetWriting, 0);
			}
			offsetWriting += advenceXLocal;
			
		}
		return weight;
	}
	*/
}

record FontProperty(
		String fontName,
		float fontSize,
		boolean bold,
		boolean italic) {
	public static final FontProperty DEFAULT_FONT = new FontProperty("FreeSans", 15, false, false);

	public FontProperty withSize(final float fontSize) {
		return new FontProperty(this.fontName, fontSize, this.bold, this.italic);
	}
	public FontProperty withFontName(final String fontName) {
		return new FontProperty(fontName, this.fontSize, this.bold, this.italic);
	}
	public FontProperty withBold(final boolean bold) {
		return new FontProperty(this.fontName, this.fontSize, bold, this.italic);
	}
	public FontProperty withSize(final boolean italic) {
		return new FontProperty(this.fontName, this.fontSize, this.bold, italic);
	}
}

record TextSpan(
		Vector2f position,
		String text,
		FontProperty fontState,
		PaintState paintState) {}

/**
sample:
*/
