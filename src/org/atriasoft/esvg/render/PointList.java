package org.atriasoft.esvg.render;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.internal.Log;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Pair;

public class PointList {
	public List<List<Point>> data = new ArrayList<>();
	
	public PointList() {
		
	}
	
	public void addList(final List<Point> list) {
		this.data.add(list);
		// TODO : Add a checker of correct list ...
	}
	
	public void applyMatrix(final Matrix2x3f transformationMatrix) {
		for (List<Point> it : this.data) {
			for (Point val : it) {
				val.pos = transformationMatrix.multiply(val.pos);
			}
		}
	}
	
	public void display() {
		Log.verbose(" Display list of points : size=" + this.data.size());
		for (List<Point> it : this.data) {
			Log.verbose("    Find List " + it.size() + " members");
			for (int iii = 0; iii < it.size(); ++iii) {
				Point elem = it.get(iii);
				Log.verbose("        [" + iii + "] Find " + elem.type + " " + elem.pos);
			}
		}
	}
	
	public Pair<Vector2f, Vector2f> getViewPort() {
		Pair<Vector2f, Vector2f> out = new Pair<>(Vector2f.MAX_VALUE, Vector2f.MIN_VALUE);
		for (List<Point> it : this.data) {
			for (Point it2 : it) {
				out = new Pair<>(Vector2f.min(out.first, it2.pos), Vector2f.max(out.second, it2.pos));
			}
		}
		return out;
	}
}
