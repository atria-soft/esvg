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
}
