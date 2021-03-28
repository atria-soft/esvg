package org.atriasoft.esvg;

import org.atriasoft.etk.Color;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Pair;

public class PaintState {
	
	public Pair<Color, String> fill;
	public Pair<Color, String> stroke;
	public float strokeWidth;
	public boolean flagEvenOdd;
	public CapMode lineCap;
	public JoinMode lineJoin; //!< Fill rules
	public float miterLimit;
	public Pair<Vector2f, Vector2f> viewPort;
	public float opacity;
	
	public PaintState() {
		this.fill = new Pair<Color, String>(new Color(0, 0, 0, 1), "");
		this.stroke = new Pair<Color, String>(new Color(0, 0, 0, 0), "");
		this.strokeWidth = 1.0f;
		this.viewPort.first.setValue(0.0f, 0.0f);
		this.viewPort.first.setValue(0.0f, 0.0f);
		this.flagEvenOdd = false;
		this.lineJoin = JoinMode.MITER;
		this.lineCap = CapMode.BUTT;
		this.miterLimit = 4.0f;
		this.opacity = 1.0f;
	}
	
	public void clear() {
		this.fill = new Pair<Color, String>(new Color(0, 0, 0, 1), "");
		this.stroke = new Pair<Color, String>(new Color(0, 0, 0, 0), "");
		this.strokeWidth = 1.0f;
		this.viewPort.first.setValue(0.0f, 0.0f);
		this.viewPort.first.setValue(0.0f, 0.0f);
		this.flagEvenOdd = false;
		this.lineJoin = JoinMode.MITER;
		this.lineCap = CapMode.BUTT;
		this.miterLimit = 4.0f;
		this.opacity = 1.0f;
	}
}
