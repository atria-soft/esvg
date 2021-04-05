package org.atriasoft.esvg.render;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.internal.Log;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

public class PathModel {
	private static void interpolateCubicBezier(final List<Point> listPoint, final int recurtionMax, final float threshold, final Vector2f pos1, final Vector2f pos2, final Vector2f pos3,
			final Vector2f pos4, final int level, final PointType type) {
		if (level > recurtionMax) {
			return;
		}
		Vector2f pos12 = pos1.add(pos2).multiply(0.5f);
		Vector2f pos23 = pos2.add(pos3).multiply(0.5f);
		Vector2f pos34 = pos3.add(pos4).multiply(0.5f);
		
		Vector2f delta = pos4.less(pos1);
		float distance2 = Math.abs(((pos2.x() - pos4.x()) * delta.y() - (pos2.y() - pos4.y()) * delta.x()));
		float distance3 = Math.abs(((pos3.x() - pos4.x()) * delta.y() - (pos3.y() - pos4.y()) * delta.x()));
		
		if ((distance2 + distance3) * (distance2 + distance3) < threshold * delta.length2()) {
			listPoint.add(new Point(pos4, type));
			return;
		}
		Vector2f pos123 = pos12.add(pos23).multiply(0.5f);
		Vector2f pos234 = pos23.add(pos34).multiply(0.5f);
		Vector2f pos1234 = pos123.add(pos234).multiply(0.5f);
		
		PathModel.interpolateCubicBezier(listPoint, recurtionMax, threshold, pos1, pos12, pos123, pos1234, level + 1, PointType.interpolation);
		PathModel.interpolateCubicBezier(listPoint, recurtionMax, threshold, pos1234, pos234, pos34, pos4, level + 1, type);
	}
	
	/**
	 *  add indentation of the string input.
	 * @param data String where the indentation is done.
	 * @param indent Number of tab to add at the string.
	 */
	public static String spacingDist(final int indent) {
		final StringBuilder data = new StringBuilder();
		for (int iii = 0; iii < indent; iii++) {
			data.append("\t");
		}
		return data.toString();
	}
	
	private static float vectorAngle(Vector2f uuu, Vector2f vvv) {
		uuu = uuu.safeNormalize();
		vvv = vvv.safeNormalize();
		return (float) Math.atan2(uuu.cross(vvv), uuu.dot(vvv));
	}
	
	SegmentList debugInformation;
	
	public List<Element> listElement = new ArrayList<>();
	
	public PathModel() {
		
	}
	
	public void bezierCurveTo(final boolean relative, final Vector2f pos1, final Vector2f pos) {
		this.listElement.add(new ElementBezierCurveTo(relative, pos1, pos));
	}
	
	public void bezierSmoothCurveTo(final boolean relative, final Vector2f pos) {
		this.listElement.add(new ElementBezierSmoothCurveTo(relative, pos));
	}
	
	public void clear() {
		this.listElement.clear();
	}
	
	public void close() {
		close(false);
	}
	
	public void close(final boolean relative) {
		this.listElement.add(new ElementClose(relative));
	}
	
	public void curveTo(final boolean relative, final Vector2f pos1, final Vector2f pos2, final Vector2f pos) {
		this.listElement.add(new ElementCurveTo(relative, pos1, pos2, pos));
	}
	
	public void display(final int spacing) {
		Log.warning(PathModel.spacingDist(spacing) + "Path");
		for (Element it : this.listElement) {
			if (it == null) {
				continue;
			}
			Log.warning(PathModel.spacingDist(spacing + 1) + it);
		}
	}
	
	public void ellipticTo(final boolean relative, final Vector2f radius, final float angle, final boolean largeArcFlag, final boolean sweepFlag, final Vector2f pos) {
		this.listElement.add(new ElementElliptic(relative, radius, angle, largeArcFlag, sweepFlag, pos));
	}
	
	public PointList generateListPoints(final int level) {
		return generateListPoints(level, 10);
	}
	
	public PointList generateListPoints(final int level, final int recurtionMax) {
		return generateListPoints(level, recurtionMax, 0.25f);
	}
	
	public PointList generateListPoints(final int level, final int recurtionMax, final float threshold) {
		Log.verbose(PathModel.spacingDist(level) + "Generate List Points ... from a path");
		PointList out = new PointList();
		List<Point> tmpListPoint = new ArrayList<>();
		Vector2f lastPosition = Vector2f.ZERO;
		Vector2f lastAngle = Vector2f.ZERO;
		// Foreach element, we move in the path:
		for (Element it : this.listElement) {
			if (it == null) {
				continue;
			}
			Log.verbose(PathModel.spacingDist(level + 1) + " Draw : " + it.toString());
			switch (it.getType()) {
				case stop:
					if (tmpListPoint.size() != 0) {
						if (tmpListPoint.size() == 0) {
							Log.warning(PathModel.spacingDist(level + 1) + " Request path stop of not starting path ...");
						} else {
							tmpListPoint.get(tmpListPoint.size() - 1).setEndPath();
							out.addList(tmpListPoint);
							tmpListPoint = new ArrayList<>();
						}
					}
					lastAngle = Vector2f.ZERO;
					// nothing alse to do ...
					break;
				case close:
					if (tmpListPoint.size() != 0) {
						if (tmpListPoint.size() == 0) {
							Log.warning(PathModel.spacingDist(level + 1) + " Request path close of not starting path ...");
						} else {
							// find the previous tart of the path ...
							tmpListPoint.get(0).type = PointType.join;
							// Remove the last point if it is the same position...
							Vector2f delta = (tmpListPoint.get(0).pos.less(tmpListPoint.get(tmpListPoint.size() - 1).pos)).abs();
							if (delta.x() <= 0.00001 && delta.y() <= 0.00001) {
								Log.verbose("        Remove point Z property : " + tmpListPoint.get(tmpListPoint.size() - 1).pos + " with delta=" + delta);
								tmpListPoint.remove(tmpListPoint.size() - 1);
							}
							out.addList(tmpListPoint);
							tmpListPoint = new ArrayList<>();
						}
					}
					lastAngle = Vector2f.ZERO;
					// nothing alse to do ...
					break;
				case moveTo:
					// stop last path
					if (tmpListPoint.size() != 0) {
						tmpListPoint.get(tmpListPoint.size() - 1).setEndPath();
						out.addList(tmpListPoint);
						tmpListPoint = new ArrayList<>();
					}
					// create a new one
					if (!it.getRelative()) {
						lastPosition = Vector2f.ZERO;
					}
					lastPosition = lastPosition.add(it.getPos());
					tmpListPoint.add(new Point(lastPosition, PointType.start));
					lastAngle = lastPosition;
					break;
				case lineTo:
					// If no previous point, we need to create the last point has start ...
					if (tmpListPoint.size() == 0) {
						tmpListPoint.add(new Point(lastPosition, PointType.start));
					}
					if (!it.getRelative()) {
						lastPosition = Vector2f.ZERO;
					}
					lastPosition = lastPosition.add(it.getPos());
					tmpListPoint.add(new Point(lastPosition, PointType.join));
					lastAngle = lastPosition;
					break;
				case lineToH:
					// If no previous point, we need to create the last point has start ...
					if (tmpListPoint.size() == 0) {
						tmpListPoint.add(new Point(lastPosition, PointType.start));
					}
					if (!it.getRelative()) {
						lastPosition = Vector2f.ZERO;
					}
					lastPosition = lastPosition.add(it.getPos());
					tmpListPoint.add(new Point(lastPosition, PointType.join));
					lastAngle = lastPosition;
					break;
				case lineToV:
					// If no previous point, we need to create the last point has start ...
					if (tmpListPoint.size() == 0) {
						tmpListPoint.add(new Point(lastPosition, PointType.start));
					}
					if (!it.getRelative()) {
						lastPosition = Vector2f.ZERO;
					}
					lastPosition = lastPosition.add(it.getPos());
					tmpListPoint.add(new Point(lastPosition, PointType.join));
					lastAngle = lastPosition;
					break;
				case curveTo:
					// If no previous point, we need to create the last point has start ...
					if (tmpListPoint.size() == 0) {
						tmpListPoint.add(new Point(lastPosition, PointType.join));
					} {
					Vector2f lastPosStore = lastPosition;
					if (!it.getRelative()) {
						lastPosition = Vector2f.ZERO;
					}
					Vector2f pos1 = lastPosition.add(it.getPos1());
					Vector2f pos2 = lastPosition.add(it.getPos2());
					Vector2f pos = lastPosition.add(it.getPos());
					PathModel.interpolateCubicBezier(tmpListPoint, recurtionMax, threshold, lastPosStore, pos1, pos2, pos, 0, PointType.join);
					lastPosition = pos;
					lastAngle = pos2;
				}
					break;
				case smoothCurveTo:
					// If no previous point, we need to create the last point has start ...
					if (tmpListPoint.size() == 0) {
						tmpListPoint.add(new Point(lastPosition, PointType.join));
					} {
					Vector2f lastPosStore = lastPosition;
					if (!it.getRelative()) {
						lastPosition = Vector2f.ZERO;
					}
					Vector2f pos2 = lastPosition.add(it.getPos2());
					Vector2f pos = lastPosition.add(it.getPos());
					// generate Pos 1
					Vector2f pos1 = lastPosStore.multiply(2.0f).less(lastAngle);
					PathModel.interpolateCubicBezier(tmpListPoint, recurtionMax, threshold, lastPosStore, pos1, pos2, pos, 0, PointType.join);
					lastPosition = pos;
					lastAngle = pos2;
				}
					break;
				case bezierCurveTo:
					// If no previous point, we need to create the last point has start ...
					if (tmpListPoint.size() == 0) {
						tmpListPoint.add(new Point(lastPosition, PointType.join));
					} {
					Vector2f lastPosStore = lastPosition;
					if (!it.getRelative()) {
						lastPosition = Vector2f.ZERO;
					}
					Vector2f pos = lastPosition.add(it.getPos());
					Vector2f tmp1 = lastPosition.add(it.getPos1());
					// generate pos1 and pos2
					Vector2f pos1 = lastPosStore.add(tmp1.less(lastPosStore).multiply(0.666666666f));
					Vector2f pos2 = pos.add(tmp1.less(pos).multiply(0.666666666f));
					PathModel.interpolateCubicBezier(tmpListPoint, recurtionMax, threshold, lastPosStore, pos1, pos2, pos, 0, PointType.join);
					lastPosition = pos;
					lastAngle = tmp1;
				}
					break;
				case bezierSmoothCurveTo:
					// If no previous point, we need to create the last point has start ...
					if (tmpListPoint.size() == 0) {
						tmpListPoint.add(new Point(lastPosition, PointType.join));
					} {
					Vector2f lastPosStore = lastPosition;
					if (!it.getRelative()) {
						lastPosition = Vector2f.ZERO;
					}
					Vector2f pos = lastPosition.add(it.getPos());
					Vector2f tmp1 = lastPosStore.multiply(2.0f).less(lastAngle);
					// generate pos1 and pos2
					Vector2f pos1 = lastPosStore.add(tmp1.less(lastPosStore).multiply(0.666666666f));
					Vector2f pos2 = pos.add(tmp1.less(pos).multiply(0.66666666f));
					PathModel.interpolateCubicBezier(tmpListPoint, recurtionMax, threshold, lastPosStore, pos1, pos2, pos, 0, PointType.join);
					lastPosition = pos;
					lastAngle = tmp1;
				}
					break;
				case elliptic:
					// If no previous point, we need to create the last point has start ...
					if (tmpListPoint.size() == 0) {
						tmpListPoint.add(new Point(lastPosition, PointType.join));
					} {
					ElementElliptic tmpIt = (ElementElliptic) it;
					Log.todo(PathModel.spacingDist(level + 1) + " Elliptic arc: radius=" + tmpIt.getPos1());
					Log.todo(PathModel.spacingDist(level + 1) + "               angle=" + tmpIt.angle);
					Log.todo(PathModel.spacingDist(level + 1) + "               this.largeArcFlag=" + tmpIt.largeArcFlag);
					Log.todo(PathModel.spacingDist(level + 1) + "               this.sweepFlag=" + tmpIt.sweepFlag);
					
					Vector2f lastPosStore = lastPosition;
					if (!it.getRelative()) {
						lastPosition = Vector2f.ZERO;
					}
					Vector2f pos = lastPosition.add(it.getPos());
					float rotationX = tmpIt.angle * ((float) Math.PI / 180.0f);
					Vector2f radius = tmpIt.getPos1();
					
					//this.debugInformation.addSegment(lastPosStore, pos);
					Vector2f delta = lastPosStore.less(pos);
					float ddd = delta.length();
					if (ddd < 1e-6f || radius.x() < 1e-6f || radius.y() < 1e-6f) {
						Log.warning("Degenerate arc in Line");
						if (tmpListPoint.size() == 0) {
							tmpListPoint.add(new Point(lastPosition, PointType.join));
						}
						tmpListPoint.add(new Point(pos, PointType.join));
					} else {
						// Convert to center point parameterization.
						// http://www.w3.org/TR/SVG11/implnote.html#ArcImplementationNotes
						// procedure describe here : http://www.w3.org/TR/SVG11/implnote.html#ArcConversionCenterToEndpoint
						// Compute delta'
						Matrix2x3f matrixRotationCenter = Matrix2x3f.createRotate(-rotationX);
						Vector2f deltaPrim = matrixRotationCenter.multiply(delta.multiply(0.5f));
						ddd = (deltaPrim.x() * deltaPrim.x()) / (radius.x() * radius.x()) + (deltaPrim.y() * deltaPrim.y()) / (radius.y() * radius.y());
						if (ddd > 1.0f) {
							ddd = (float) Math.sqrt(ddd);
							radius = radius.multiply(ddd);
						}
						// Compute center'
						float sss = 0.0f;
						float ssa = radius.x() * radius.x() * radius.y() * radius.y() - radius.x() * radius.x() * deltaPrim.y() * deltaPrim.y()
								- radius.y() * radius.y() * deltaPrim.x() * deltaPrim.x();
						float ssb = radius.x() * radius.x() * deltaPrim.y() * deltaPrim.y() + radius.y() * radius.y() * deltaPrim.x() * deltaPrim.x();
						if (ssa < 0.0f) {
							ssa = 0.0f;
						}
						if (ssb > 0.0f) {
							sss = (float) Math.sqrt(ssa / ssb);
						}
						if (tmpIt.largeArcFlag == tmpIt.sweepFlag) {
							sss *= -1.0f;
						}
						Vector2f centerPrime = new Vector2f(sss * radius.x() * deltaPrim.y() / radius.y(), sss * -radius.y() * deltaPrim.x() / radius.x());
						// Compute center from center'
						Matrix2x3f matrix = Matrix2x3f.createRotate(rotationX);
						Vector2f center = lastPosStore.multiply(pos).multiply(0.5f).add(matrix.multiply(centerPrime));
						//this.debugInformation.addSegment(center-Vector2f(3.0,3.0), center+Vector2f(3.0,3.0));
						//	this.debugInformation.addSegment(center-Vector2f(3.0,-3.0), center+Vector2f(3.0,-3.0));
						// Calculate theta1, and delta theta.
						Vector2f vectorA = deltaPrim.less(centerPrime).devide(radius);
						Vector2f vectorB = deltaPrim.add(centerPrime).devide(radius.multiply(-1.0f));
						//this.debugInformation.addSegment(center, center+vectorA*radius.x());
						//this.debugInformation.addSegment(center, center+vectorB*radius.y());
						// Initial angle
						float theta1 = PathModel.vectorAngle(new Vector2f(1.0f, 0.0f), vectorA);
						// Delta angle
						float deltaTheta = PathModel.vectorAngle(vectorA, vectorB);
						// special case of invert angle...
						if ((deltaTheta == (float) Math.PI || deltaTheta == -(float) Math.PI) && !tmpIt.sweepFlag) {
							deltaTheta *= -1.0f;
						}
						if (tmpIt.largeArcFlag) {
							// Choose large arc
							if (deltaTheta > 0.0f) {
								deltaTheta -= 2.0f * (float) Math.PI;
							} else {
								deltaTheta += 2.0f * (float) Math.PI;
							}
						}
						// Approximate the arc using cubic spline segments.
						matrix.translate(center);
						// Split arc into max 90 degree segments.
						// The loop assumes an iteration per end point (including start and end), this +1.
						int ndivs = (int) (Math.abs(deltaTheta) / ((float) Math.PI * 0.5f)) + 1;
						
						float hda = (deltaTheta / ndivs) * 0.5f;
						float kappa = (float) Math.abs(4.0f / 3.0f * (1.0f - Math.cos(hda)) / Math.sin(hda));
						if (deltaTheta < 0.0f) {
							kappa = -kappa;
						}
						Vector2f pointPosPrevious = Vector2f.ZERO;
						Vector2f tangentPrevious = Vector2f.ZERO;
						for (int iii = 0; iii <= ndivs; ++iii) {
							float a = theta1 + deltaTheta * ((float) iii / (float) ndivs);
							delta = new Vector2f(FMath.cos(a), FMath.sin(a));
							// position
							Vector2f pointPos = matrix.multiply(new Vector2f(delta.x() * radius.x(), delta.y() * radius.y()));
							// tangent
							Vector2f tangent = matrix.applyScaleRotation(new Vector2f(-delta.y() * radius.x() * kappa, delta.x() * radius.y() * kappa));
							if (iii > 0) {
								Vector2f zlastPosStore = lastPosition;
								if (!it.getRelative()) {
									lastPosition = Vector2f.ZERO;
								}
								Vector2f zpos1 = pointPosPrevious.add(tangentPrevious);
								Vector2f zpos2 = pointPos.less(tangent);
								Vector2f zpos = pointPos;
								PathModel.interpolateCubicBezier(tmpListPoint, recurtionMax, threshold, zlastPosStore, zpos1, zpos2, zpos, 0, PointType.join);
								lastPosition = zpos;
								lastAngle = zpos2;
							}
							pointPosPrevious = pointPos;
							tangentPrevious = tangent;
						}
					}
					lastPosition = pos;
				}
					break;
				default:
					Log.error(PathModel.spacingDist(level + 1) + " Unknow PATH commant (internal error)");
					break;
			}
		}
		// special case : No request end of path ==> open path:
		if (tmpListPoint.size() != 0) {
			Log.verbose("Auto-end PATH");
			tmpListPoint.get(tmpListPoint.size() - 1).setEndPath();
			out.addList(tmpListPoint);
			tmpListPoint = new ArrayList<>();
		}
		out.display();
		return out;
	}
	
	public void lineTo(final boolean relative, final Vector2f pos) {
		this.listElement.add(new ElementLineTo(relative, pos));
	}
	
	public void lineToH(final boolean relative, final float posX) {
		this.listElement.add(new ElementLineToH(relative, posX));
	}
	
	public void lineToV(final boolean relative, final float posY) {
		this.listElement.add(new ElementLineToV(relative, posY));
	}
	
	public void moveTo(final boolean relative, final Vector2f pos) {
		this.listElement.add(new ElementMoveTo(relative, pos));
	}
	
	public void smoothCurveTo(final boolean relative, final Vector2f pos2, final Vector2f pos) {
		this.listElement.add(new ElementSmoothCurveTo(relative, pos2, pos));
	}
	
	public void stop() {
		this.listElement.add(new ElementStop());
	}
	
}
