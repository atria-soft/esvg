package org.atriasoft.esvg.render;

import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.Pair;
import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Color;

public class DynamicColorUni implements DynamicColor {
	public Color color;
	
	public DynamicColorUni(final Color color) {
		this.color = color;
	}
	
	@Override
	public void generate(final EsvgDocument document) {
		// nothing to do ...
	}
	
	@Override
	public Color getColor(final Vector2i pos) {
		return this.color;
	}
	
	@Override
	public void setViewPort(final Pair<Vector2f, Vector2f> viewPort) {
		// nothing to do ...
	}
}
