package org.atriasoft.esvg;

import org.atriasoft.etk.Color;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Pair;

public class PaintState {
	
	public Pair<Color, String> fill = new Pair<Color, String>(Color.BLACK, "");
	public boolean flagEvenOdd = false;
	public CapMode lineCap = CapMode.BUTT;
	public JoinMode lineJoin = JoinMode.MITER;
	public float miterLimit = 4.0f;
	public float opacity = 1.0f;
	public Pair<Color, String> stroke = new Pair<Color, String>(Color.NONE, "");
	public float strokeWidth = 1.0f;
	public Pair<Vector2f, Vector2f> viewPort = new Pair<>(Vector2f.ZERO, Vector2f.ZERO);
	
	public PaintState() {}
	
	public void clear() {
		this.fill = new Pair<Color, String>(Color.BLACK, "");
		this.stroke = new Pair<Color, String>(Color.NONE, "");
		this.strokeWidth = 1.0f;
		this.viewPort = new Pair<>(Vector2f.ZERO, Vector2f.ZERO);
		this.flagEvenOdd = false;
		this.lineJoin = JoinMode.MITER;
		this.lineCap = CapMode.BUTT;
		this.miterLimit = 4.0f;
		this.opacity = 1.0f;
	}
	
	public void clearFill() {
		this.fill = new Pair<Color, String>(Color.NONE, "");
	}
	
	public void clearStroke() {
		this.stroke = new Pair<Color, String>(Color.NONE, "");
	}
	
	@Override
	protected PaintState clone() {
		PaintState out = new PaintState();
		out.fill = this.fill;
		out.stroke = this.stroke;
		out.strokeWidth = this.strokeWidth;
		out.viewPort = this.viewPort;
		out.flagEvenOdd = this.flagEvenOdd;
		out.lineJoin = this.lineJoin;
		out.lineCap = this.lineCap;
		out.miterLimit = this.miterLimit;
		out.opacity = this.opacity;
		return out;
	}
	
	public Color getFill() {
		return this.fill.first;
	}
	
	public CapMode getLineCap() {
		return this.lineCap;
	}
	
	public JoinMode getLineJoin() {
		return this.lineJoin;
	}
	
	public float getMiterLimit() {
		return this.miterLimit;
	}
	
	public float getOpacity() {
		return this.opacity;
	}
	
	public Color getStroke() {
		return this.stroke.first;
	}
	
	public float getStrokeWidth() {
		return this.strokeWidth;
	}
	
	public void setFill(final Color color) {
		this.fill = new Pair<Color, String>(color, "");
	}
	
	public void setLineCap(final CapMode lineCap) {
		this.lineCap = lineCap;
	}
	
	public void setLineJoin(final JoinMode lineJoin) {
		this.lineJoin = lineJoin;
	}
	
	public void setMiterLimit(final float miterLimit) {
		this.miterLimit = miterLimit;
	}
	
	public void setOpacity(final float opacity) {
		this.opacity = opacity;
	}
	
	public void setStroke(final Color color) {
		this.stroke = new Pair<Color, String>(color, "");
	}
	
	public void setStrokeWidth(final float strokeWidth) {
		this.strokeWidth = strokeWidth;
	}
	
}
