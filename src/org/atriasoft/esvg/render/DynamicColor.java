package org.atriasoft.esvg.render;

import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.util.Pair;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Color;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public interface DynamicColor {
	public static DynamicColor createColor(final Pair<Color, String> color, final Matrix2x3f mtx) {
		// Check if need to create a color:
		if (color.first.a() == 0 && color.second.isEmpty()) {
			return null;
		}
		if (color.second.isEmpty()) {
			return new DynamicColorUni(color.first);
		}
		return new DynamicColorSpecial(color.second, mtx);
	}
	
	void generate(EsvgDocument document);
	
	public Color getColor(Vector2i pos);
	
	public void setViewPort(Pair<Vector2f, Vector2f> viewPort);
	
}
