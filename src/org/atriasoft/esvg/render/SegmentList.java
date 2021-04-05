package org.atriasoft.esvg.render;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.etk.util.Pair;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.esvg.CapMode;
import org.atriasoft.esvg.JoinMode;
import org.atriasoft.esvg.internal.Log;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class SegmentList {
	static Vector2f getIntersect(final Vector2f point1, final Vector2f vect1, final Vector2f point2, final Vector2f vect2) {
		float diviseur = vect1.x() * vect2.y() - vect1.y() * vect2.x();
		if (diviseur != 0.0f) {
			float mmm = (vect1.x() * point1.y() - vect1.x() * point2.y() - vect1.y() * point1.x() + vect1.y() * point2.x()) / diviseur;
			return point2.add(vect2.multiply(mmm));
		}
		Log.error("Get divider / 0.0f");
		return point2;
	}
	
	public List<Segment> data = new ArrayList<>();
	
	public SegmentList() {}
	
	public void addSegment(final Point pos0, final Point pos1) {
		// Skip horizontal Segments
		if (pos0.pos.y() == pos1.pos.y()) {
			// remove /0 operation
			return;
		}
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
		for (Segment it : this.data) {
			it.applyMatrix(transformationMatrix);
		}
	}
	
	public void createSegmentList(final PointList listPoint) {
		for (List<Point> it : listPoint.data) {
			// Build Segments
			for (int iii = 0, jjj = it.size() - 1; iii < it.size(); jjj = iii++) {
				addSegment(it.get(jjj), it.get(iii));
			}
		}
	}
	
	public void createSegmentListStroke(final PointList listPoint, final float width, final CapMode cap, final JoinMode join, final float miterLimit) {
		for (List<Point> itListPoint : listPoint.data) {
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
			for (int idPevious = itListPoint.size() - 1, idCurrent = 0, idNext = 1; idCurrent < itListPoint.size(); idPevious = idCurrent++, idNext++) {
				if (idNext == itListPoint.size()) {
					idNext = 0;
				}
				if (itListPoint.get(idCurrent).type == PointType.join || itListPoint.get(idCurrent).type == PointType.interpolation) {
					if (idPevious < 0) {
						Log.error("an error occure a previous ID is < 0.... ");
						continue;
					}
					if (idNext >= itListPoint.size()) {
						Log.error("an error occure a next ID is >= nbPoint len .... ");
						continue;
					}
					//Log.debug("JOIN : id : prev/curr/next : " + idPevious + "/" + idCurrent + "/" + idNext);
					//Log.debug("JOIN : val : prev/curr/next : " + itListPoint.get(idPevious).pos + "/" + itListPoint.get(idCurrent).pos + "/" + itListPoint.get(idNext).pos);
					Vector2f vecA = itListPoint.get(idCurrent).pos.less(itListPoint.get(idPevious).pos);
					//Log.debug("JOIN : vecA : " + vecA);
					vecA = vecA.safeNormalize();
					Vector2f vecB = itListPoint.get(idNext).pos.less(itListPoint.get(idCurrent).pos);
					//Log.debug("JOIN : vecB : " + vecB);
					vecB = vecB.safeNormalize();
					Vector2f vecC = vecA.less(vecB);
					//Log.debug("JOIN : vecC : " + vecC);
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
					//Log.debug("JOIN : miterAxe " + itListPoint.get(idCurrent).miterAxe);
				} else if (itListPoint.get(idCurrent).type == PointType.start) {
					itListPoint.get(idCurrent).posNext = itListPoint.get(idNext).pos;
					Vector2f vecB = itListPoint.get(idNext).pos.less(itListPoint.get(idCurrent).pos);
					vecB = vecB.safeNormalize();
					itListPoint.get(idCurrent).miterAxe = new Vector2f(vecB.y(), -vecB.x());
					itListPoint.get(idCurrent).orthoAxePrevious = itListPoint.get(idCurrent).miterAxe;
					itListPoint.get(idCurrent).orthoAxeNext = itListPoint.get(idCurrent).miterAxe;
				} else if (itListPoint.get(idCurrent).type == PointType.stop) {
					if (idPevious < 0) {
						Log.error("an error occure a previous ID is < 0.... ");
						continue;
					}
					itListPoint.get(idCurrent).posPrevious = itListPoint.get(idPevious).pos;
					Vector2f vecA = itListPoint.get(idCurrent).pos.less(itListPoint.get(idPevious).pos);
					vecA = vecA.safeNormalize();
					itListPoint.get(idCurrent).miterAxe = new Vector2f(vecA.y(), -vecA.x());
					itListPoint.get(idCurrent).orthoAxePrevious = itListPoint.get(idCurrent).miterAxe;
					itListPoint.get(idCurrent).orthoAxeNext = itListPoint.get(idCurrent).miterAxe;
				} else {
					Log.todo("Unsupported type of point ....");
				}
			}
			// create segment list:
			boolean haveStartLine = false;
			
			Dynamic<Vector2f> leftPoint = new Dynamic<Vector2f>(Vector2f.ZERO);
			
			Dynamic<Vector2f> rightPoint = new Dynamic<Vector2f>(Vector2f.ZERO);
			if (itListPoint.size() > 0) {
				if (itListPoint.get(0).type == PointType.join) {
					Point it = itListPoint.get(itListPoint.size() - 1);
					// Calculate the perpendicular axis ...
					leftPoint.value = it.pos.add(it.orthoAxePrevious.multiply(width * 0.5f));
					rightPoint.value = it.pos.less(it.orthoAxePrevious.multiply(width * 0.5f));
					// cyclic path...
					if (it.type == PointType.interpolation) {
						leftPoint.value = SegmentList.getIntersect(leftPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
						rightPoint.value = SegmentList.getIntersect(rightPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
					} else if (it.type == PointType.join) {
						// Calculate the perpendicular axis ...
						leftPoint.value = it.pos.add(it.orthoAxePrevious.multiply(width * 0.5f));
						rightPoint.value = it.pos.less(it.orthoAxePrevious.multiply(width * 0.5f));
						// project on the miter Axis ...
						switch (join) {
							case MITER: {
								Vector2f left = SegmentList.getIntersect(leftPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
								Vector2f right = SegmentList.getIntersect(rightPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
								// Check the miter limit:
								float limitRight = (left.less(it.pos)).length() / width * 2.0f;
								float limitLeft = (right.less(it.pos)).length() / width * 2.0f;
								Log.verbose("    miter Limit: " + limitRight + " " + limitLeft + " <= " + miterLimit);
								if (limitRight <= miterLimit && limitLeft <= miterLimit) {
									leftPoint.value = left;
									rightPoint.value = right;
									break;
								}
							}
							case ROUND:
							case BEVEL: {
								Vector2f axePrevious = (it.pos.less(it.posPrevious)).safeNormalize();
								Vector2f axeNext = (it.posNext.less(it.pos)).safeNormalize();
								float cross = axePrevious.cross(axeNext);
								if (cross > 0.0f) {
									rightPoint.value = SegmentList.getIntersect(rightPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
									leftPoint.value = it.pos.add(it.orthoAxeNext.multiply(width * 0.5f));
								} else {
									leftPoint.value = SegmentList.getIntersect(leftPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
									rightPoint.value = it.pos.less(it.orthoAxeNext.multiply(width * 0.5f));
								}
								break;
							}
							default:
								break;
						}
					} else {
						Log.error("Start list point with a join, but last lement is not a join");
					}
				}
			}
			for (Point it : itListPoint) {
				switch (it.type) {
					case single:
						// just do nothing ....
						Log.verbose("Find Single " + it.pos);
						break;
					case start:
						Log.verbose("Find Start " + it.pos);
						if (haveStartLine) {
							// close previous :
							Log.warning(" find a non close path ...");
							addSegment(leftPoint.value, rightPoint.value);
						}
						haveStartLine = true;
						startStopPoint(leftPoint, rightPoint, it, cap, width, true);
						break;
					case stop:
						Log.verbose("Find Stop " + it.pos);
						if (!haveStartLine) {
							Log.warning("find close path without start part ...");
							break;
						}
						haveStartLine = false;
						startStopPoint(leftPoint, rightPoint, it, cap, width, false);
						break;
					case interpolation: {
						Log.verbose("Find interpolation " + it.pos);
						Vector2f left = SegmentList.getIntersect(leftPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
						Vector2f right = SegmentList.getIntersect(rightPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
						//Draw from previous point:
						addSegment(leftPoint.value, left);
						Log.verbose("    segment :" + leftPoint + " . " + left);
						addSegment(right, rightPoint.value);
						Log.verbose("    segment :" + right + " . " + rightPoint);
						leftPoint.value = left;
						rightPoint.value = right;
					}
						break;
					case join:
						Log.verbose("Find join " + it.pos);
						switch (join) {
							case MITER: {
								Vector2f left = SegmentList.getIntersect(leftPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
								Vector2f right = SegmentList.getIntersect(rightPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
								// Check the miter limit:
								float limitRight = left.less(it.pos).length() / width * 2.0f;
								float limitLeft = right.less(it.pos).length() / width * 2.0f;
								Log.verbose("    miter Limit: " + limitRight + " " + limitLeft + " <= " + miterLimit);
								if (limitRight <= miterLimit && limitLeft <= miterLimit) {
									//Draw from previous point:
									addSegment(leftPoint.value, left);
									Log.verbose("    segment :" + leftPoint + " . " + left);
									addSegment(right, rightPoint.value);
									Log.verbose("    segment :" + right + " . " + rightPoint);
									leftPoint.value = left;
									rightPoint.value = right;
									break;
								}
								Log.verbose("    Find miter Limit ... ==> create BEVEL");
							}
							case ROUND:
							case BEVEL: {
								Vector2f axePrevious = (it.pos.less(it.posPrevious)).safeNormalize();
								Vector2f axeNext = (it.posNext.less(it.pos)).safeNormalize();
								float cross = axePrevious.cross(axeNext);
								if (cross > 0.0f) {
									Vector2f right = SegmentList.getIntersect(rightPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
									Vector2f left1 = it.pos.add(it.orthoAxePrevious.multiply(width * 0.5f));
									Vector2f left2 = it.pos.add(it.orthoAxeNext.multiply(width * 0.5f));
									//Draw from previous point:
									addSegment(leftPoint.value, left1);
									Log.verbose("    segment :" + leftPoint + " . " + left1);
									if (join != JoinMode.ROUND) {
										// Miter and bevel:
										addSegment(left1, left2);
										Log.verbose("    segment :" + left1 + " . " + left2);
									} else {
										createSegmentListStroke(left1, left2, it.pos, width, false);
									}
									addSegment(right, rightPoint.value);
									Log.verbose("    segment :" + right + " . " + rightPoint);
									leftPoint.value = left2;
									rightPoint.value = right;
								} else {
									Vector2f left = SegmentList.getIntersect(leftPoint.value, it.pos.less(it.posPrevious), it.pos, it.miterAxe);
									Vector2f right1 = it.pos.less(it.orthoAxePrevious.multiply(width * 0.5f));
									Vector2f right2 = it.pos.less(it.orthoAxeNext.multiply(width * 0.5f));
									//Draw from previous point:
									addSegment(leftPoint.value, left);
									Log.verbose("    segment :" + leftPoint + " . " + left);
									addSegment(right1, rightPoint.value);
									Log.verbose("    segment :" + right1 + " . " + rightPoint);
									if (join != JoinMode.ROUND) {
										// Miter and bevel:
										addSegment(right2, right1);
										Log.verbose("    segment :" + right2 + " . " + right1);
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
	
	private void createSegmentListStroke(final Vector2f point1, final Vector2f point2, final Vector2f center, final float width, final boolean isStart) {
		int nbDot = (int) width;
		if (nbDot <= 2) {
			nbDot = 2;
		}
		float angleToDraw = FMath.acos((point1.less(center)).safeNormalize().dot((point2.less(center)).safeNormalize()));
		float baseAngle = angleToDraw / nbDot;
		float iii;
		Vector2f axe = (point1.less(center)).safeNormalize();
		
		Vector2f ppp1 = point1;
		
		Vector2f ppp2 = point2;
		for (iii = baseAngle; iii < angleToDraw; iii += baseAngle) {
			Matrix2x3f tmpMat = Matrix2x3f.IDENTITY;
			if (isStart) {
				tmpMat = Matrix2x3f.createRotate(-iii);
			} else {
				tmpMat = Matrix2x3f.createRotate(iii);
			}
			Vector2f axeRotate = tmpMat.multiply(axe);
			ppp2 = center.add(axeRotate.multiply(width * 0.5f));
			if (isStart) {
				addSegment(ppp2, ppp1);
				Log.verbose("    segment :" + ppp2 + " . " + ppp1);
			} else {
				addSegment(ppp1, ppp2);
				Log.verbose("    segment :" + ppp1 + " . " + ppp2);
			}
			ppp1 = ppp2;
		}
		if (isStart) {
			addSegment(point2, ppp1);
			Log.verbose("    segment :" + point2 + " . " + ppp1);
		} else {
			addSegment(ppp1, point2);
			Log.verbose("    segment :" + ppp1 + " . " + point2);
		}
	}
	
	public Pair<Vector2f, Vector2f> getViewPort() {
		
		Pair<Vector2f, Vector2f> out = new Pair<>(Vector2f.MAX_VALUE, Vector2f.MIN_VALUE);
		for (Segment it : this.data) {
			out = new Pair<>(Vector2f.min(out.first, it.p0, it.p1), Vector2f.max(out.second, it.p0, it.p1));
		}
		return out;
	}
	
	private void startStopPoint(final Dynamic<Vector2f> leftPoint, final Dynamic<Vector2f> rightPoint, final Point point, final CapMode cap, final float width, final boolean isStart) {
		switch (cap) {
			case BUTT: {
				Vector2f left = point.pos.add(point.miterAxe.multiply(width * 0.5f));
				Vector2f right = point.pos.less(point.miterAxe.multiply(width * 0.5f));
				if (!isStart) {
					//Draw from previous point:
					addSegment(leftPoint.value, left);
					Log.verbose("    segment :" + leftPoint + " . " + left);
					addSegment(right, rightPoint.value);
					Log.verbose("    segment :" + right + " . " + rightPoint);
				}
				leftPoint.value = left;
				rightPoint.value = right;
			}
				if (!isStart) {
					addSegment(leftPoint.value, rightPoint.value);
					Log.verbose("    segment :" + leftPoint + " . " + rightPoint);
				} else {
					addSegment(rightPoint.value, leftPoint.value);
					Log.verbose("    segment :" + rightPoint + " . " + leftPoint);
				}
				break;
			case ROUND: {
				if (!isStart) {
					Vector2f left = point.pos.add(point.miterAxe.multiply(width * 0.5f));
					Vector2f right = point.pos.less(point.miterAxe.multiply(width * 0.5f));
					if (!isStart) {
						//Draw from previous point:
						addSegment(leftPoint.value, left);
						Log.verbose("    segment :" + leftPoint + " . " + left);
						addSegment(right, rightPoint.value);
						Log.verbose("    segment :" + right + " . " + rightPoint);
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
				Matrix2x3f tmpMat = Matrix2x3f.createTranslate(nextAxe.safeNormalize().multiply(width * -0.5f));
				left = tmpMat.multiply(left);
				right = tmpMat.multiply(right);
				if (!isStart) {
					//Draw from previous point:
					addSegment(leftPoint.value, left);
					Log.verbose("    segment :" + leftPoint + " . " + left);
					addSegment(right, rightPoint.value);
					Log.verbose("    segment :" + right + " . " + rightPoint);
				}
				leftPoint.value = left;
				rightPoint.value = right;
				if (!isStart) {
					addSegment(leftPoint.value, rightPoint.value);
					Log.verbose("    segment :" + leftPoint + " . " + rightPoint);
				} else {
					addSegment(rightPoint.value, leftPoint.value);
					Log.verbose("    segment :" + rightPoint + " . " + leftPoint);
				}
				Log.verbose("    segment :" + leftPoint + " . " + rightPoint);
			}
				break;
			default:
				Log.error(" Undefined CAP TYPE");
				break;
		}
	}
	
}
