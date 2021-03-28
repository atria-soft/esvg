/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <esvg/debug.hpp>
#include <esvg/render/PointList.hpp>

esvg::render::PointList::PointList() {
	// nothing to do ...
}

void esvg::render::PointList::addList(List<esvg::render::Point>& _list) {
	this.data.pushBack(_list);
	// TODO : Add a checker of correct list ...
}

void esvg::render::PointList::applyMatrix(const mat2x3& _transformationMatrix) {
	for (auto &it : this.data) {
		for (auto &val : it) {
			val.this.pos = _transformationMatrix * val.this.pos;
		}
	}
}

Pair<Vector2f, Vector2f> esvg::render::PointList::getViewPort() {
	Pair<Vector2f, Vector2f> out(Vector2f(9999999999.0,9999999999.0),Vector2f(-9999999999.0,-9999999999.0));
	for (auto &it : this.data) {
		for (auto &it2 : it) {
			out.first.setMin(it2.this.pos);
			out.second.setMax(it2.this.pos);
		}
	}
	return out;
}

void esvg::render::PointList::display() {
	Log.verbose(" Display list of points : size=" << this.data.size());
	for (auto &it : this.data) {
		Log.verbose("    Find List " << it.size() << " members");
		for (size_t iii=0;
		     iii < it.size();
		     ++iii) {
			switch (it[iii].this.type) {
				case esvg::render::Point::type::single:
					Log.verbose("        [" << iii << "] Find Single " << it[iii].this.pos);
					break;
				case esvg::render::Point::type::start:
					Log.verbose("        [" << iii << "] Find Start " << it[iii].this.pos);
					break;
				case esvg::render::Point::type::stop:
					Log.verbose("        [" << iii << "] Find Stop " << it[iii].this.pos);
					break;
				case esvg::render::Point::type::interpolation:
					Log.verbose("        [" << iii << "] Find interpolation " << it[iii].this.pos);
					break;
				case esvg::render::Point::type::join:
					Log.verbose("        [" << iii << "] Find Join " << it[iii].this.pos);
					break;
			}
		}
	}
}
