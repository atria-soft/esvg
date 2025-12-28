package org.atriasoft.esvg.render;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.atriasoft.esvg.CapMode;
import org.atriasoft.esvg.JoinMode;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.etk.util.Pair;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class SegmentList {
	static final Logger LOGGER = LoggerFactory.getLogger(SegmentList.class);

	static Vector2f getIntersect(
			final Vector2f point1,
			final Vector2f vect1,
			final Vector2f point2,
			final Vector2f vect2) {
		final float diviseur = vect1.x() * vect2.y() - vect1.y() * vect2.x();
		if (diviseur != 0.0f) {
			final float mmm = (vect1.x() * point1.y() - vect1.x() * point2.y() - vect1.y() * point1.x()
					+ vect1.y() * point2.x()) / diviseur;
			return point2.add(vect2.multiply(mmm));
		}
		LOGGER.warn("Get divider / 0.0f");
		return point2;
	}
	
	public List<Segment> data = new ArrayList<>();
	
	public SegmentList() {}
	
	public void addSegment(final Point pos0, final Point pos1) {
		this.data.add(new Segment(pos0.pos, pos1.pos));
	}
	
	public void addSegment(final Point pos0, final Point pos1, final boolean disableHorizontal) {
		// Skip horizontal Segments
		if (disableHorizontal && pos0.pos.y() == pos1.pos.y()) {
			// remove /0 operation
			return;
		}
		this.data.add(new Segment(pos0.pos, pos1.pos));
	}
	
	void addSegment(final Vector2f pos0, final Vector2f pos1) {
		if (pos0.y() == pos1.y()) {
			return;
		}
		this.data.add(new Segment(pos0, pos1));
	}
	
	public void applyMatrix(final Matrix2x3f transformationMatrix) {
		for (final Segment it : this.data) {
			it.applyMatrix(transformationMatrix);
		}
	}
	
	public void clearHorizontals() {
		// TODO Auto-generated method stub
		final Iterator<Segment> itr = this.data.iterator();
		while (itr.hasNext()) {
			final Segment seg = itr.next();
			if (seg.p0.y() == seg.p1.y()) {
				itr.remove();
			}
		}
	}
	
	public void createSegmentList(final PointList listPoint) {
		for (final List<Point> it : listPoint.data) {
			// Build Segments
			for (int iii = 0, jjj = it.size() - 1; iii < it.size(); jjj = iii++) {
				addSegment(it.get(jjj), it.get(iii));
			}
		}
	}
	
	public void createSegmentListStroke(
			final PointList listPoint,
			final float width,
			final CapMode cap,
			final JoinMode join,
			final float miterLimit) {
		for (final List<Point> itListPoint : listPoint.data) {
			// generate for every point all the orthogonal elements
			//
			//     normal edge             *                 end path
			//      (mitter)             * | *                      * * * * * * * * * * * * *
			//                         *   |<--*----this                            |       *
			//                       *     |     *                          this -->|       *
			//                     *       *       *                                |       *
			//                   *       . | .       *              . . . . . . . . *       *
			//                 *       .   |   .       *                            |       *
			//               *     A .     |     . B     *                          |       *
			//                     .       *       .                                |       *
			//                   .       *   *       .              * * * * * * * * * * * * *
			//                         *       *
			//                       *           *
			for (int idPevious = itListPoint.size() - 1, idCurrent = 0, idNext = 1; idCurrent < itListPoint.size();
					idPevious = idCurrent++, idNext++) {
				if (idNext == itListPoint.size()) {
					idNext = 0;
				}
				if (itListPoint.get(idCurrent).type == PointType.join
						|| itListPoint.get(idCurrent).type == PointType.interpolation) {
					if (idPevious < 0) {
						LOGGER.error("an error occurred: previous ID is < 0");
						continue;
					}
					if (idNext >= itListPoint.size()) {
						LOGGER.error("an error occurred: next ID is >= nbPoint len");
						continue;
					}
					//LOGGER.debug("JOIN : id : prev/curr/next : " + idPevious + "/" + idCurrent + "/" + idNext);
					//LOGGER.debug("JOIN : val : prev/curr/next : " + itListPoint.get(idPevious).pos + "/" + itListPoint.get(idCurrent).pos + "/" + itListPoint.get(idNext).pos);
					Vector2f vecA = itListPoint.get(idCurrent).pos.less(itListPoint.get(idPevious).pos);
					//LOGGER.debug("JOIN : vecA : " + vecA);
					vecA = vecA.safeNormalize();
					Vector2f vecB = itListPoint.get(idNext).pos.less(itListPoint.get(idCurrent).pos);
					//LOGGER.debug("JOIN : vecB : " + vecB);
					vecB = vecB.safeNormalize();
					Vector2f vecC = vecA.less(vecB);
					//LOGGER.debug("JOIN : vecC : " + vecC);
					if (vecC.isZero()) {
						// special case: 1 line ...
						itListPoint.get(idCurrent).miterAxe = new Vector2f(vecA.y(), vecA.x());
					} else {
						vecC = vecC.safeNormalize();
						itListPoint.get(idCurrent).miterAxe = vecC;
					}
					itListPoint.get(idCurrent).posPrevious = itListPoint.get(idPevious).pos;
					itListPoint.get(idCurrent).posNext = itListPoint.get(idNext).pos;
					vecB = itListPoint.get(idNext).pos.less(itListPoint.get(idCurrent).pos);
					vecB = vecB.safeNormalize();
					itListPoint.get(idCurrent).orthoAxeNext = new Vector2f(vecB.y(), -vecB.x());
					vecB = itListPoint.get(idCurrent).pos.less(itListPoint.get(idPevious).pos);
					vecB = vecB.safeNormalize();
					itListPoint.get(idCurrent).orthoAxePrevious = new Vector2f(vecB.y(), -vecB.x());
					//LOGGER.debug("JOIN : miterAxe " + itListPoint.get(idCurrent).miterAxe);
				} else if (itListPoint.get(idCurrent).type == PointType.start) {
					itListPoint.get(idCurrent).posNext = itListPoint.get(idNext).pos;
					Vector2f vecB = itListPoint.get(idNext).pos.less(itListPoint.get(idCurrent).pos);
					vecB = vecB.safeNormalize();
					itListPoint.get(idCurrent).miterAxe = new Vector2f(vecB.y(), -vecB.x());
					itListPoint.get(idCurrent).orthoAxePrevious = itListPoint.get(idCurrent).miterAxe;
					itListPoint.get(idCurrent).orthoAxeNext = itListPoint.get(idCurrent).miterAxe;
				} else if (itListPoint.get(idCurrent).type == PointType.stop) {
					if (idPevious < 0) {
						LOGGER.error("an error occurred: previous ID is < 0");
						continue;
					}
					itListPoint.get(idCurrent).posPrevious = itListPoint.get(idPevious).pos;
					Vector2f vecA = itListPoint.get(idCurrent).pos.less(itListPoint.get(idPevious).pos);
					vecA = vecA.safeNormalize();
					itListPoint.get(idCurrent).miterAxe = new Vector2f(vecA.y(), -vecA.x());
					itListPoint.get(idCurrent).orthoAxePrevious = itListPoint.get(idCurrent).miterAxe;
					itListPoint.get(idCurrent).orthoAxeNext = itListPoint.get(idCurrent).miterAxe;
				} else {
					LOGGER.info("TODO: Unsupported type of point ....");
				}
			}
			// create segment list:
			boolean haveStartLine = false;
			
			final Dynamic<Vector2f> leftPoint = new Dynamic<>(Vector2f.ZERO);
			
			final Dynamic<Vector2f> rightPoint = new Dynamic<>(Vector2f.ZERO);
			if (itListPoint.size() > 0) {
				if (itListPoint.get(0).type == PointType.join) {
					final Point it = itListPoint.get(itListPoint.size() - 1);
					// Calculate the perpendicular axis ...
					leftPoint.value = it.pos.add(it.orthoAxePrevious.multiply(width * 0.5f));
					rightPoint.value = it.pos.less(it.orthoAxePrevious.multiply(width * 0.5f));
					// cyclic path...
					if (it.type == PointType.interpolation) {
						leftPoint.value = SegmentList.getIntersect(leftPoint.value, it.pos.less(it.posPrevious), it.pos,
								it.miterAxe);
						rightPoint.value = SegmentList.getIntersect(rightPoint.value, it.pos.less(it.posPrevious),
								it.pos, it.miterAxe);
					} else if (it.type == PointType.join) {
						// Calculate the perpendicular axis ...
						leftPoint.value = it.pos.add(it.orthoAxePrevious.multiply(width * 0.5f));
						rightPoint.value = it.pos.less(it.orthoAxePrevious.multiply(width * 0.5f));
						// project on the miter Axis ...
						switch (join) {
							case MITER: {
								final Vector2f left = SegmentList.getIntersect(leftPoint.value,
										it.pos.less(it.posPrevious), it.pos, it.miterAxe);
								final Vector2f right = SegmentList.getIntersect(rightPoint.value,
										it.pos.less(it.posPrevious), it.pos, it.miterAxe);
								// Check the miter limit:
								final float limitRight = (left.less(it.pos)).length() / width * 2.0f;
								final float limitLeft = (right.less(it.pos)).length() / width * 2.0f;
								LOGGER.trace("    miter Limit: {} {} <= {}", limitRight, limitLeft, miterLimit);
								if (limitRight <= miterLimit && limitLeft <= miterLimit) {
									leftPoint.value = left;
									rightPoint.value = right;
									break;
								}
							}
							case ROUND:
							case BEVEL: {
								final Vector2f axePrevious = (it.pos.less(it.posPrevious)).safeNormalize();
								final Vector2f axeNext = (it.posNext.less(it.pos)).safeNormalize();
								final float cross = axePrevious.cross(axeNext);
								if (cross > 0.0f) {
									rightPoint.value = SegmentList.getIntersect(rightPoint.value,
											it.pos.less(it.posPrevious), it.pos, it.miterAxe);
									leftPoint.value = it.pos.add(it.orthoAxeNext.multiply(width * 0.5f));
								} else {
									leftPoint.value = SegmentList.getIntersect(leftPoint.value,
											it.pos.less(it.posPrevious), it.pos, it.miterAxe);
									rightPoint.value = it.pos.less(it.orthoAxeNext.multiply(width * 0.5f));
								}
								break;
							}
							default:
								break;
						}
					} else {
						LOGGER.error("Start list point with a join, but last lement is not a join");
					}
				}
			}
			for (final Point it : itListPoint) {
				switch (it.type) {
					case single:
						// just do nothing ....
						LOGGER.trace("Find Single {}", it.pos);
						break;
					case start:
						LOGGER.trace("Find Start {}", it.pos);
						if (haveStartLine) {
							// close previous :
							LOGGER.warn(" find a non close path ...");
							addSegment(leftPoint.value, rightPoint.value);
						}
						haveStartLine = true;
						startStopPoint(leftPoint, rightPoint, it, cap, width, true);
						break;
					case stop:
						LOGGER.trace("Find Stop {}", it.pos);
						if (!haveStartLine) {
							LOGGER.warn("find close path without start part ...");
							break;
						}
						haveStartLine = false;
						startStopPoint(leftPoint, rightPoint, it, cap, width, false);
						break;
					case interpolation: {
						LOGGER.trace("Find interpolation {}", it.pos);
						final Vector2f left = SegmentList.getIntersect(leftPoint.value, it.pos.less(it.posPrevious),
								it.pos, it.miterAxe);
						final Vector2f right = SegmentList.getIntersect(rightPoint.value, it.pos.less(it.posPrevious),
								it.pos, it.miterAxe);
						//Draw from previous point:
						addSegment(leftPoint.value, left);
						LOGGER.trace("    segment: {} . {}", leftPoint, left);
						addSegment(right, rightPoint.value);
						LOGGER.trace("    segment: {} . {}", right, rightPoint);
						leftPoint.value = left;
						rightPoint.value = right;
					}
						break;
					case join:
						LOGGER.trace("Find join {}", it.pos);
						switch (join) {
							case MITER: {
								final Vector2f left = SegmentList.getIntersect(leftPoint.value,
										it.pos.less(it.posPrevious), it.pos, it.miterAxe);
								final Vector2f right = SegmentList.getIntersect(rightPoint.value,
										it.pos.less(it.posPrevious), it.pos, it.miterAxe);
								// Check the miter limit:
								final float limitRight = left.less(it.pos).length() / width * 2.0f;
								final float limitLeft = right.less(it.pos).length() / width * 2.0f;
								LOGGER.trace("    miter Limit: {} {} <= {}", limitRight, limitLeft, miterLimit);
								if (limitRight <= miterLimit && limitLeft <= miterLimit) {
									//Draw from previous point:
									addSegment(leftPoint.value, left);
									LOGGER.trace("    segment: {} . {}", leftPoint, left);
									addSegment(right, rightPoint.value);
									LOGGER.trace("    segment: {} . {}", right, rightPoint);
									leftPoint.value = left;
									rightPoint.value = right;
									break;
								}
								LOGGER.trace("    Find miter Limit ... ==> create BEVEL");
							}
							case ROUND:
							case BEVEL: {
								final Vector2f axePrevious = (it.pos.less(it.posPrevious)).safeNormalize();
								final Vector2f axeNext = (it.posNext.less(it.pos)).safeNormalize();
								final float cross = axePrevious.cross(axeNext);
								if (cross > 0.0f) {
									final Vector2f right = SegmentList.getIntersect(rightPoint.value,
											it.pos.less(it.posPrevious), it.pos, it.miterAxe);
									final Vector2f left1 = it.pos.add(it.orthoAxePrevious.multiply(width * 0.5f));
									final Vector2f left2 = it.pos.add(it.orthoAxeNext.multiply(width * 0.5f));
									//Draw from previous point:
									addSegment(leftPoint.value, left1);
									LOGGER.trace("    segment: {} . {}", leftPoint, left1);
									if (join != JoinMode.ROUND) {
										// Miter and bevel:
										addSegment(left1, left2);
										LOGGER.trace("    segment: {} . {}", left1, left2);
									} else {
										createSegmentListStroke(left1, left2, it.pos, width, false);
									}
									addSegment(right, rightPoint.value);
									LOGGER.trace("    segment: {} . {}", right, rightPoint);
									leftPoint.value = left2;
									rightPoint.value = right;
								} else {
									final Vector2f left = SegmentList.getIntersect(leftPoint.value,
											it.pos.less(it.posPrevious), it.pos, it.miterAxe);
									final Vector2f right1 = it.pos.less(it.orthoAxePrevious.multiply(width * 0.5f));
									final Vector2f right2 = it.pos.less(it.orthoAxeNext.multiply(width * 0.5f));
									//Draw from previous point:
									addSegment(leftPoint.value, left);
									LOGGER.trace("    segment: {} . {}", leftPoint, left);
									addSegment(right1, rightPoint.value);
									LOGGER.trace("    segment: {} . {}", right1, rightPoint);
									if (join != JoinMode.ROUND) {
										// Miter and bevel:
										addSegment(right2, right1);
										LOGGER.trace("    segment: {} . {}", right2, right1);
									} else {
										createSegmentListStroke(right1, right2, it.pos, width, true);
									}
									leftPoint.value = left;
									rightPoint.value = right2;
								}
							}
								break;
							default:
								break;
						}
						break;
					default:
						break;
				}
			}
		}
		
	}
	
	private void createSegmentListStroke(
			final Vector2f point1,
			final Vector2f point2,
			final Vector2f center,
			final float width,
			final boolean isStart) {
		int nbDot = (int) width;
		if (nbDot <= 2) {
			nbDot = 2;
		}
		final float angleToDraw = FMath
				.acos((point1.less(center)).safeNormalize().dot((point2.less(center)).safeNormalize()));
		final float baseAngle = angleToDraw / nbDot;
		float iii;
		final Vector2f axe = (point1.less(center)).safeNormalize();
		
		Vector2f ppp1 = point1;
		
		Vector2f ppp2 = point2;
		for (iii = baseAngle; iii < angleToDraw; iii += baseAngle) {
			Matrix2x3f tmpMat = Matrix2x3f.IDENTITY;
			if (isStart) {
				tmpMat = Matrix2x3f.createRotate(-iii);
			} else {
				tmpMat = Matrix2x3f.createRotate(iii);
			}
			final Vector2f axeRotate = tmpMat.multiply(axe);
			ppp2 = center.add(axeRotate.multiply(width * 0.5f));
			if (isStart) {
				addSegment(ppp2, ppp1);
				LOGGER.trace("    segment: {} . {}", ppp2, ppp1);
			} else {
				addSegment(ppp1, ppp2);
				LOGGER.trace("    segment: {} . {}", ppp1, ppp2);
			}
			ppp1 = ppp2;
		}
		if (isStart) {
			addSegment(point2, ppp1);
			LOGGER.trace("    segment: {} . {}", point2, ppp1);
		} else {
			addSegment(ppp1, point2);
			LOGGER.trace("    segment: {} . {}", ppp1, point2);
		}
	}
	
	public Pair<Vector2f, Vector2f> getViewPort() {
		
		Pair<Vector2f, Vector2f> out = new Pair<>(Vector2f.MAX_VALUE, Vector2f.MIN_VALUE);
		for (final Segment it : this.data) {
			out = new Pair<>(Vector2f.min(out.first, it.p0, it.p1), Vector2f.max(out.second, it.p0, it.p1));
		}
		return out;
	}
	
	private void startStopPoint(
			final Dynamic<Vector2f> leftPoint,
			final Dynamic<Vector2f> rightPoint,
			final Point point,
			final CapMode cap,
			final float width,
			final boolean isStart) {
		switch (cap) {
			case BUTT: {
				final Vector2f left = point.pos.add(point.miterAxe.multiply(width * 0.5f));
				final Vector2f right = point.pos.less(point.miterAxe.multiply(width * 0.5f));
				if (!isStart) {
					//Draw from previous point:
					addSegment(leftPoint.value, left);
					LOGGER.trace("    segment: {} . {}", leftPoint, left);
					addSegment(right, rightPoint.value);
					LOGGER.trace("    segment: {} . {}", right, rightPoint);
				}
				leftPoint.value = left;
				rightPoint.value = right;
			}
				if (!isStart) {
					addSegment(leftPoint.value, rightPoint.value);
					LOGGER.trace("    segment: {} . {}", leftPoint, rightPoint);
				} else {
					addSegment(rightPoint.value, leftPoint.value);
					LOGGER.trace("    segment: {} . {}", rightPoint, leftPoint);
				}
				break;
			case ROUND: {
				if (!isStart) {
					final Vector2f left = point.pos.add(point.miterAxe.multiply(width * 0.5f));
					final Vector2f right = point.pos.less(point.miterAxe.multiply(width * 0.5f));
					if (!isStart) {
						//Draw from previous point:
						addSegment(leftPoint.value, left);
						LOGGER.trace("    segment: {} . {}", leftPoint, left);
						addSegment(right, rightPoint.value);
						LOGGER.trace("    segment: {} . {}", right, rightPoint);
					}
					leftPoint.value = left;
					rightPoint.value = right;
				}
				int nbDot = (int) width;
				if (nbDot <= 2) {
					nbDot = 2;
				}
				leftPoint.value = point.pos.add(point.miterAxe.multiply(width * 0.5f));
				rightPoint.value = point.pos.less(point.miterAxe.multiply(width * 0.5f));
				createSegmentListStroke(leftPoint.value, rightPoint.value, point.pos, width, isStart);
			}
				break;
			case SQUARE: {
				Vector2f nextAxe;
				if (isStart) {
					nextAxe = point.posNext.less(point.pos);
				} else {
					nextAxe = point.posPrevious.less(point.pos);
				}
				Vector2f left = point.pos.add(point.miterAxe.multiply(width * 0.5f));
				Vector2f right = point.pos.less(point.miterAxe.multiply(width * 0.5f));
				final Matrix2x3f tmpMat = Matrix2x3f.createTranslate(nextAxe.safeNormalize().multiply(width * -0.5f));
				left = tmpMat.multiply(left);
				right = tmpMat.multiply(right);
				if (!isStart) {
					//Draw from previous point:
					addSegment(leftPoint.value, left);
					LOGGER.trace("    segment: {} . {}", leftPoint, left);
					addSegment(right, rightPoint.value);
					LOGGER.trace("    segment: {} . {}", right, rightPoint);
				}
				leftPoint.value = left;
				rightPoint.value = right;
				if (!isStart) {
					addSegment(leftPoint.value, rightPoint.value);
					LOGGER.trace("    segment: {} . {}", leftPoint, rightPoint);
				} else {
					addSegment(rightPoint.value, leftPoint.value);
					LOGGER.trace("    segment: {} . {}", rightPoint, leftPoint);
				}
				LOGGER.trace("    segment: {} . {}", leftPoint, rightPoint);
			}
				break;
			default:
				LOGGER.error(" Undefined CAP TYPE");
				break;
		}
	}
	
}
