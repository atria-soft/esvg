package org.atriasoft.esvg.render;

import java.util.Arrays;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class Scanline {
	private final float[] data;
	
	public Scanline() {
		this(32);
	}
	
	public Scanline(final int size) {
		this.data = new float[size];
		Arrays.fill(this.data, 0);
	}
	
	void clear(final float fill) {
		Arrays.fill(this.data, 0);
	}
	
	float get(final int pos) {
		if (pos >= 0 && pos < this.data.length) {
			return this.data[pos];
		}
		return 0;
	}
	
	void set(final int pos, final float newColor) {
		if (pos >= 0 && pos < this.data.length) {
			this.data[pos] = newColor;
		}
	}
	
	public int size() {
		return this.data.length;
	}
}
