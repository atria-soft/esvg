package org.atriasoft.esvg.render;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Pair;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class PointList {
	static final Logger LOGGER = LoggerFactory.getLogger(PointList.class);
	public List<List<Point>> data = new ArrayList<>();

	public PointList() {

	}

	public void addList(final List<Point> list) {
		this.data.add(list);
		// TODO : Add a checker of correct list ...
	}

	public void applyMatrix(final Matrix2x3f transformationMatrix) {
		for (final List<Point> it : this.data) {
			for (final Point val : it) {
				val.pos = transformationMatrix.multiply(val.pos);
			}
		}
	}

	public void display() {
		LOGGER.trace(" Display list of points : size=" + this.data.size());
		for (final List<Point> it : this.data) {
			LOGGER.trace("    Find List " + it.size() + " members");
			for (int iii = 0; iii < it.size(); ++iii) {
				final Point elem = it.get(iii);
				LOGGER.trace("        [" + iii + "] Find " + elem.type + " " + elem.pos);
			}
		}
	}

	public Pair<Vector2f, Vector2f> getViewPort() {
		Pair<Vector2f, Vector2f> out = new Pair<>(Vector2f.MAX_VALUE, Vector2f.MIN_VALUE);
		for (final List<Point> it : this.data) {
			for (final Point it2 : it) {
				out = new Pair<>(Vector2f.min(out.first, it2.pos), Vector2f.max(out.second, it2.pos));
			}
		}
		return out;
	}
}
