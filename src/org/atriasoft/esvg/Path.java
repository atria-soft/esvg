package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.internal.Log;
import org.atriasoft.esvg.render.PathModel;
import org.atriasoft.esvg.render.Point;
import org.atriasoft.esvg.render.PointList;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.esvg.render.DynamicColor;
import org.atriasoft.esvg.render.SegmentList;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.exml.model.XmlElement;
import org.atriasoft.exml.parser.Tools;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
public class Path extends Base {
	private record Command(
			char cmd,
			float[] listDot,
			int offset) {
		Command(final char cmd, final float[] listDot, final int offset) {
			this.cmd = cmd;
			this.listDot = listDot;
			this.offset = offset;
		}
		
		Command(final char cmd, final int offset) {
			this(cmd, null, offset);
		}
		
	}
	
	private static String cleanBadSpaces(final String input) {
		StringBuilder out = new StringBuilder(input.length());
		boolean haveSpace = false;
		for (char it : input.toCharArray()) {
			if (it == ' ' || it == '\t' || it == '\t' || it == '\r') {
				haveSpace = true;
			} else {
				if (haveSpace) {
					haveSpace = false;
					out.append(' ');
				}
				out.append(it);
			}
		}
		return out.toString();
	}
	
	//return the next char position ... (after 'X' or NULL)
	private static Command extractCmd(final char[] input, final int offset) {
		if (input[offset] == '\0') {
			return null;
		}
		char cmd = '\0';
		if (!((input[offset] <= 'Z' && input[offset] >= 'A') || (input[offset] <= 'z' && input[offset] >= 'a'))) {
			Log.error("Error in the SVG Path : '" + input + "' [" + offset);
			return null;
		}
		cmd = input[0];
		Log.verbose("Find command : " + cmd);
		if (input[offset + 1] == '\0') {
			return new Command(cmd, offset + 1);
		}
		
		StringBuilder tmpData = new StringBuilder();
		List<String> elements = new ArrayList<>();
		int iii;
		for (iii = offset; iii < input.length; iii++) {
			if (Tools.checkNumber(input[iii], iii == offset)) {
				tmpData.append(input[iii]);
				continue;
			}
			elements.add(tmpData.toString());
			tmpData.setLength(0);
			if (input[iii] == ' ' || input[iii] == '\t' || input[iii] == '\n' || input[iii] == '\r' || input[iii] == ',' || input[iii] == ';') {
				continue;
			}
			break;
		}
		float[] outputList = new float[elements.size()];
		int jjj = 0;
		for (String ekems : elements) {
			outputList[jjj++] = Float.parseFloat(ekems);
		}
		// remove after white space...
		for (; iii < input.length; iii++) {
			if (input[iii] == ' ' || input[iii] == '\t' || input[iii] == '\n' || input[iii] == '\r') {
				continue;
			}
			break;
		}
		return new Command(cmd, outputList, offset + 1);
	}
	
	public PathModel listElement;
	
	public Path(final PaintState parentPaintState) {
		super(parentPaintState);
	}
	
	@Override
	void display(final int spacing) {
		this.listElement.display(spacing);
	}
	
	@Override
	void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW esvg::Path");
		
		Matrix2x3f mtx = this.transformMatrix.multiply(basicTrans);
		
		PointList listPoints = new PointList();
		listPoints = this.listElement.generateListPoints(level, myRenderer.getInterpolationRecurtionMax(), myRenderer.getInterpolationThreshold());
		//listPoints.applyMatrix(mtx);
		SegmentList listSegmentFill = new SegmentList();
		SegmentList listSegmentStroke = new SegmentList();
		Weight tmpFill = new Weight();
		Weight tmpStroke = new Weight();
		DynamicColor colorFill = DynamicColor.createColor(this.paint.fill, mtx);
		DynamicColor colorStroke = null;
		if (this.paint.strokeWidth > 0.0f) {
			colorStroke = DynamicColor.createColor(this.paint.stroke, mtx);
		}
		// Check if we need to display background
		if (colorFill != null) {
			listSegmentFill.createSegmentList(listPoints);
			colorFill.setViewPort(listSegmentFill.getViewPort());
			listSegmentFill.applyMatrix(mtx);
			// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
			tmpFill.generate(myRenderer.getSize(), myRenderer.getNumberSubScanLine(), listSegmentFill);
		}
		// check if we need to display stroke:
		if (colorStroke != null) {
			listSegmentStroke.createSegmentListStroke(listPoints, this.paint.strokeWidth, this.paint.lineCap, this.paint.lineJoin, this.paint.miterLimit);
			colorStroke.setViewPort(listSegmentStroke.getViewPort());
			listSegmentStroke.applyMatrix(mtx);
			// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
			tmpStroke.generate(myRenderer.getSize(), myRenderer.getNumberSubScanLine(), listSegmentStroke);
		}
		// add on images:
		myRenderer.print(tmpFill, colorFill, tmpStroke, colorStroke, this.paint.opacity);
		//myRenderer.addDebugSegment(listSegmentFill);
		//myRenderer.addDebugSegment(listSegmentStroke);
		//this.listElement.debugInformation.applyMatrix(mtx);
		//myRenderer.addDebugSegment(this.listElement.debugInformation);
		
	}
	
	@Override
	void drawShapePoints(final List<List<Vector2f>> out, final int recurtionMax, final float threshold, final Matrix2x3f basicTrans, final int level) {
		Log.verbose(spacingDist(level) + "DRAW Shape esvg::Path");
		
		Matrix2x3f mtx = this.transformMatrix.multiply(basicTrans);
		
		PointList listPoints = new PointList();
		listPoints = this.listElement.generateListPoints(level, recurtionMax, threshold);
		listPoints.applyMatrix(mtx);
		for (List<Point> it : listPoints.data) {
			List<Vector2f> listPoint = new ArrayList<Vector2f>();
			for (Point itDot : it) {
				listPoint.add(itDot.pos);
			}
			out.add(listPoint);
		}
	}
	
	@Override
	boolean parseXML(final XmlElement element, final Matrix2x3f parentTrans, final Dynamic<Vector2f> sizeMax) {
		if (element == null) {
			return false;
		}
		parseTransform(element);
		parsePaintAttr(element);
		
		// add the property of the parrent modifications ...
		this.transformMatrix = this.transformMatrix.multiply(parentTrans);
		
		String elementXML1 = element.getAttribute("d", "");
		if (elementXML1.length() == 0) {
			Log.warning("path: missing 'd' attribute or empty");
			return false;
		}
		Log.verbose("Parse Path : \"" + elementXML1 + "\"");
		
		float[] listDot = null;
		elementXML1 = Path.cleanBadSpaces(elementXML1);
		char[] elementXML = elementXML1.toCharArray();
		
		// TODO REWORK this, can be done with a simple split and search in a list...
		for (Command sss = Path.extractCmd(elementXML, 0); sss != null; sss = Path.extractCmd(elementXML, sss.offset())) {
			boolean relative = false;
			listDot = sss.listDot();
			switch (sss.cmd) {
				case 'm': // Move to (relative)
					relative = true;
				case 'M': // Move to (absolute)
					// 2 Elements ...
					if (listDot.length % 2 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					if (listDot.length >= 2) {
						this.listElement.moveTo(relative, new Vector2f(listDot[0], listDot[1]));
					}
					for (int iii = 2; iii < listDot.length; iii += 2) {
						this.listElement.lineTo(relative, new Vector2f(listDot[iii], listDot[iii + 1]));
					}
					break;
				case 'l': // Line to (relative)
					relative = true;
				case 'L': // Line to (absolute)
					// 2 Elements ...
					if (listDot.length % 2 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 2) {
						this.listElement.lineTo(relative, new Vector2f(listDot[iii], listDot[iii + 1]));
					}
					break;
				
				case 'v': // Vertical Line to (relative)
					relative = true;
				case 'V': // Vertical Line to (absolute)
					// 1 Element ...
					if (listDot.length == 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 1) {
						this.listElement.lineToV(relative, listDot[iii]);
					}
					break;
				
				case 'h': // Horizantal Line to (relative)
					relative = true;
				case 'H': // Horizantal Line to (absolute)
					// 1 Element ...
					if (listDot.length == 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 1) {
						this.listElement.lineToH(relative, listDot[iii]);
					}
					break;
				
				case 'q': // Quadratic Bezier curve (relative)
					relative = true;
				case 'Q': // Quadratic Bezier curve (absolute)
					// 4 Elements ...
					if (listDot.length % 4 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 4) {
						this.listElement.bezierCurveTo(relative, new Vector2f(listDot[iii], listDot[iii + 1]), new Vector2f(listDot[iii + 2], listDot[iii + 3]));
					}
					break;
				
				case 't': // smooth quadratic Bezier curve to (relative)
					relative = true;
				case 'T': // smooth quadratic Bezier curve to (absolute)
					// 2 Elements ...
					if (listDot.length % 2 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 2) {
						this.listElement.bezierSmoothCurveTo(relative, new Vector2f(listDot[iii], listDot[iii + 1]));
					}
					break;
				
				case 'c': // curve to (relative)
					relative = true;
				case 'C': // curve to (absolute)
					// 6 Elements ...
					if (listDot.length % 6 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 6) {
						this.listElement.curveTo(relative, new Vector2f(listDot[iii], listDot[iii + 1]), new Vector2f(listDot[iii + 2], listDot[iii + 3]),
								new Vector2f(listDot[iii + 4], listDot[iii + 5]));
					}
					break;
				
				case 's': // smooth curve to (relative)
					relative = true;
				case 'S': // smooth curve to (absolute)
					// 4 Elements ...
					if (listDot.length % 4 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 4) {
						this.listElement.smoothCurveTo(relative, new Vector2f(listDot[iii], listDot[iii + 1]), new Vector2f(listDot[iii + 2], listDot[iii + 3]));
					}
					break;
				
				case 'a': // elliptical Arc (relative)
					relative = true;
				case 'A': // elliptical Arc (absolute)
					// 7 Elements ...
					if (listDot.length % 7 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 7) {
						boolean largeArcFlag = true;
						boolean sweepFlag = true;
						if (listDot[iii + 3] == 0.0f) {
							largeArcFlag = false;
						}
						if (listDot[iii + 4] == 0.0f) {
							sweepFlag = false;
						}
						this.listElement.ellipticTo(relative, new Vector2f(listDot[iii], listDot[iii + 1]), listDot[iii + 2], largeArcFlag, sweepFlag,
								new Vector2f(listDot[iii + 5], listDot[iii + 6]));
					}
					break;
				case 'z': // closepath (relative)
					relative = true;
				case 'Z': // closepath (absolute)
					// 0 Element ...
					if (listDot.length != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					this.listElement.close(relative);
					break;
				default:
					Log.error("Unknow error : '" + sss.cmd + "'");
			}
		}
		
		return true;
	}
	
}
