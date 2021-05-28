package org.atriasoft.esvg;

import org.atriasoft.egami.ImageByte;
import org.atriasoft.egami.ToolImage;
import org.atriasoft.esvg.internal.Log;
import org.atriasoft.esvg.render.PathModel;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.Configs;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;

/**
 * Graphic context is used to manage dynamic 
 * @author heero
 *
 */
public class GraphicContext {
	private EsvgDocument document = new EsvgDocument();
	PaintState paintState;
	private PathModel path = null;
	private Vector2i size = Vector2i.VALUE_32;
	
	public GraphicContext() {
		clear();
	}
	
	public Vector2i calculateTextSize(final String data) {
		return FontCache.getFont(Configs.getConfigFonts().getName(), false, false).calculateTextSize(Configs.getConfigFonts().getSize(), data);
	}
	
	public void circle(final Vector2f position, final float radius) {
		this.document.addElement(new Circle(position, radius, this.paintState.clone()));
	}
	
	public void clear() {
		this.document = new EsvgDocument(this.size);
		this.paintState = new PaintState();
	}
	
	/**
	 * Clear the fill color (disable fill ==> better that set it transparent)
	 */
	public void clearColorFill() {
		this.paintState.fill = null;
	}
	
	/**
	 * Clear the Stroke color (disable stroke)
	 */
	public void clearColorStroke() {
		this.paintState.clearStroke();
	}
	
	public void ellipse(final Vector2f center, final Vector2f radius) {
		this.document.addElement(new Ellipse(center, radius, this.paintState.clone()));
	}
	
	/**
	 * Get the fill color.
	 * @return fill color.
	 */
	public Color getColorFill() {
		return this.paintState.getFill();
	}
	
	/**
	 * Get the stroke color.
	 * @return Stroke color.
	 */
	public Color getColorStroke() {
		return this.paintState.getStroke();
	}
	
	public CapMode getLineCap() {
		return this.paintState.getLineCap();
	}
	
	public JoinMode getLineJoin() {
		return this.paintState.getLineJoin();
	}
	
	public float getMiterLimit() {
		return this.paintState.getMiterLimit();
	}
	
	public float getOpacity() {
		return this.paintState.getOpacity();
	}
	
	public float getStrokeWidth() {
		return this.paintState.getStrokeWidth();
	}
	
	public int getTextHeight() {
		return getTextHeight(Configs.getConfigFonts().getSize());
	}
	public int getTextSize() {
		return Configs.getConfigFonts().getSize();
	}
	
	
	public int getTextHeight(final float height) {
		return FontCache.getFont(Configs.getConfigFonts().getName(), false, false).calculateFontRealHeight((int) height);
	}
	
	public void line(final Vector2f origin, final Vector2f destination) {
		this.document.addElement(new Line(origin, destination, this.paintState.clone()));
	}
	
	public void lineRel(final Vector2f origin, final Vector2f relativeDestination) {
		this.document.addElement(new Line(origin, origin.add(relativeDestination), this.paintState.clone()));
	}
	
	public void pathLine(final Vector2f pos) {
		if (this.path == null) {
			Log.error("Empty path... Need call pathStart() before");
			return;
		}
		this.path.lineTo(false, pos);
	}
	
	public void pathLineTo(final Vector2f pos) {
		if (this.path == null) {
			Log.error("Empty path... Need call pathStart() before");
			return;
		}
		this.path.lineTo(true, pos);
		
	}
	
	public void pathMove(final Vector2f pos) {
		if (this.path == null) {
			Log.error("Empty path... Need call pathStart() before");
			return;
		}
		this.path.moveTo(false, pos);
	}
	
	public void pathMoveTo(final Vector2f pos) {
		if (this.path == null) {
			Log.error("Empty path... Need call pathStart() before");
			return;
		}
		this.path.moveTo(true, pos);
	}
	
	public void pathStart() {
		pathStop();
		this.path = new PathModel();
	}
	
	public void pathStop() {
		if (this.path == null) {
			return;
		}
		this.path.close(false);
		this.document.addElement(new Path(this.path, this.paintState.clone()));
		this.path = null;
	}
	
	public void pathStopLinked() {
		if (this.path == null) {
			return;
		}
		this.path.close(true);
		this.document.addElement(new Path(this.path, this.paintState.clone()));
		this.path = null;
	}
	
	public void rectangle(final Vector2f position, final Vector2f destination) {
		if (this.path != null) {
			Log.error("Path not empty ... Need call pathStart() before");
			pathStop();
		}
		this.document.addElement(new Rectangle(position, destination.less(position), this.paintState.clone()));
	}
	
	public void rectangleRounded(final Vector2f position, final Vector2f destination, final Vector2f ruound) {
		if (this.path != null) {
			Log.error("Path not empty ... Need call pathStart() before");
			pathStop();
		}
		this.document.addElement(new Rectangle(position, destination.less(position), ruound, this.paintState.clone()));
	}
	
	public void rectangleRoundedWidth(final Vector2f position, final Vector2f width, final Vector2f ruound) {
		if (this.path != null) {
			Log.error("Path not empty ... Need call pathStart() before");
			pathStop();
		}
		this.document.addElement(new Rectangle(position, width, ruound, this.paintState.clone()));
	}
	
	public void rectangleWidth(final Vector2f position, final Vector2f width) {
		if (this.path != null) {
			Log.error("Path not empty ... Need call pathStart() before");
			pathStop();
		}
		this.document.addElement(new Rectangle(position, width, this.paintState.clone()));
	}
	
	public ImageByte render() {
		return ToolImage.convertImageByte(this.document.renderImageFloatRGBA(null));
	}
	
	/**
	 * set the fill color
	 * @param color Color to set on fill
	 * @apiNote use clearFill() if you want to remove drawing of fill
	 */
	public void setColorFill(final Color color) {
		this.paintState.setFill(color);
	}
	
	/**
	 * set the stroke color
	 * @param color Color to set on stroke
	 * @apiNote use clearStroke() if you want to remove drawing of stroke
	 */
	public void setColorStroke(final Color color) {
		this.paintState.setStroke(color);
	}
	
	public void setLineCap(final CapMode lineCap) {
		this.paintState.setLineCap(lineCap);
	}
	
	public void setLineJoin(final JoinMode lineJoin) {
		this.paintState.setLineJoin(lineJoin);
	}
	
	public void setMiterLimit(final float miterLimit) {
		this.paintState.setMiterLimit(miterLimit);
	}
	
	public void setOpacity(final float opacity) {
		this.paintState.setOpacity(opacity);
	}
	
	/**
	 * Set global size of the Graphic context (output render size)
	 * @param xxx Width of the image
	 * @param yyy Height of the image
	 * @apiNote It will clear the current context.
	 */
	public void setSize(final int xxx, final int yyy) {
		setSize(new Vector2i(xxx, yyy));
	}
	
	/**
	 * Set global size of the Graphic contexct (output render size)
	 * @param vector2i New size of the image
	 * @apiNote It will clear the current context.
	 */
	private void setSize(final Vector2i size) {
		this.size = size;
		clear();
	}
	
	public void setStrokeWidth(final float strokeWidth) {
		this.paintState.setStrokeWidth(strokeWidth);
	}
	
	public void text(final Vector2f position, final float height, final String data) {
		this.document.addElement(new Text(position, Configs.getConfigFonts().getName(), height, data, this.paintState.clone()));
	}
	
	public void text(final Vector2f position, final String data) {
		text(position, Configs.getConfigFonts().getSize(), data);
	}
	
}
