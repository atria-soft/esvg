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
import org.atriasoft.etk.math.Vector2i;
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
			String[] listElem,
			int offset) {
		Command(final char cmd, final String[] listElem, final int offset) {
			this.cmd = cmd;
			this.listElem = listElem;
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
			if (it == ' ' || it == '\t' || it == '\r') {
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
	private static Command extractCmd(final List<String> input, final int offset) {
		if (input.size() <= offset) {
			//			Log.warning("parse command : END");
			return null;
		}
		//		Log.warning("parse command : (rest) " + offset);
		//		for (int iii = offset; iii < input.size(); iii++) {
		//			Log.warning("        -[" + iii + "] '" + input.get(iii) + "'");
		//		}
		if (input.get(offset).length() != 1) {
			Log.error("Error in the SVG Path : '" + input.get(offset) + "' [" + offset);
			return null;
		}
		char cmd = input.get(offset).charAt(0);
		if (!((cmd <= 'Z' && cmd >= 'A') || (cmd <= 'z' && cmd >= 'a'))) {
			Log.error("Error in the SVG Path : '" + cmd + "' [" + offset);
			return null;
		}
		//Log.verbose("Find command : " + cmd);
		if (input.size() == offset) {
			return new Command(cmd, offset + 1);
		}
		int iii;
		for (iii = offset + 1; iii < input.size(); iii++) {
			char startElem = input.get(iii).charAt(0);
			if ((startElem <= 'Z' && startElem >= 'A') || (startElem <= 'z' && startElem >= 'a')) {
				// find end of elements
				break;
			}
		}
		int length = iii - (offset + 1);
		if (length == 0) {
			return new Command(cmd, null, iii + 1);
		}
		String[] outputList = new String[length];
		for (int jjj = 0; jjj < length; jjj++) {
			outputList[jjj] = input.get(offset + 1 + jjj);
		}
		return new Command(cmd, outputList, iii);
	}
	
	public PathModel listElement = new PathModel();
	
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
		List<String> commandsSplited = splitCommand(elementXML1);
		String[] listDot = null;
		
		// TODO REWORK this, can be done with a simple split and search in a list...
		for (Command sss = Path.extractCmd(commandsSplited, 0); sss != null; sss = Path.extractCmd(commandsSplited, sss.offset())) {
			boolean relative = false;
			listDot = sss.listElem();
			
			Log.error("Find new command : '" + sss.cmd + "'");
			if (listDot != null) {
				for (int jjj = 0; jjj < listDot.length; jjj++) {
					Log.error("            ->  '" + listDot[jjj] + "'");
				}
			} else {
				Log.error("            ->  no elements");
			}
			switch (sss.cmd) {
				case 'm': // Move to (relative)
					relative = true;
				case 'M': // Move to (absolute)
					if (listDot == null) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot);
						break;
					}
					// 2 Elements ...
					if (listDot.length >= 1) {
						this.listElement.moveTo(relative, Vector2f.valueOf(listDot[0]));
					}
					for (int iii = 1; iii < listDot.length; iii++) {
						this.listElement.lineTo(relative, Vector2f.valueOf(listDot[iii]));
					}
					break;
				case 'l': // Line to (relative)
					relative = true;
				case 'L': // Line to (absolute)
					if (listDot == null) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii++) {
						this.listElement.lineTo(relative, Vector2f.valueOf(listDot[iii]));
					}
					break;
				
				case 'v': // Vertical Line to (relative)
					relative = true;
				case 'V': // Vertical Line to (absolute)
					// 1 Element ...
					if (listDot == null) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii++) {
						this.listElement.lineToV(relative, Float.parseFloat(listDot[iii]));
					}
					break;
				
				case 'h': // Horizantal Line to (relative)
					relative = true;
				case 'H': // Horizantal Line to (absolute)
					// 1 Element ...
					if (listDot == null) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii++) {
						this.listElement.lineToH(relative, Float.parseFloat(listDot[iii]));
					}
					break;
				
				case 'q': // Quadratic Bezier curve (relative)
					relative = true;
				case 'Q': // Quadratic Bezier curve (absolute)
					if (listDot == null) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot);
						break;
					}
					// 4 Elements ...
					if (listDot.length % 2 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 2) {
						this.listElement.bezierCurveTo(relative, Vector2f.valueOf(listDot[iii]), Vector2f.valueOf(listDot[iii + 1]));
					}
					break;
				
				case 't': // smooth quadratic Bezier curve to (relative)
					relative = true;
				case 'T': // smooth quadratic Bezier curve to (absolute)
					// 2 Elements ...
					for (int iii = 0; iii < listDot.length; iii++) {
						this.listElement.bezierSmoothCurveTo(relative, Vector2f.valueOf(listDot[iii]));
					}
					break;
				
				case 'c': // curve to (relative)
					relative = true;
				case 'C': // curve to (absolute)
					if (listDot == null) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot);
						break;
					}
					// 6 Elements ...
					if (listDot.length % 3 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 3) {
						this.listElement.curveTo(relative, Vector2f.valueOf(listDot[iii]), Vector2f.valueOf(listDot[iii + 1]), Vector2f.valueOf(listDot[iii + 2]));
					}
					break;
				
				case 's': // smooth curve to (relative)
					relative = true;
				case 'S': // smooth curve to (absolute)
					if (listDot == null) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot);
						break;
					}
					// 4 Elements ...
					if (listDot.length % 2 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 2) {
						this.listElement.smoothCurveTo(relative, Vector2f.valueOf(listDot[iii]), Vector2f.valueOf(listDot[iii + 1]));
					}
					break;
				
				case 'a': // elliptical Arc (relative)
					relative = true;
				case 'A': // elliptical Arc (absolute)
					if (listDot == null) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot);
						break;
					}
					// 4 element ff,ff f i,i ff,ff  Elements ...
					if (listDot.length % 4 != 0) {
						Log.warning("the PATH command " + sss.cmd + " has not the good number of element = " + listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 7) {
						boolean largeArcFlag = true;
						boolean sweepFlag = true;
						Vector2i tmp = Vector2i.valueOf(listDot[iii + 2]);
						if (tmp.x() == 0) {
							largeArcFlag = false;
						}
						if (tmp.y() == 0) {
							sweepFlag = false;
						}
						this.listElement.ellipticTo(relative, Vector2f.valueOf(listDot[iii]), Float.parseFloat(listDot[iii + 1]), largeArcFlag, sweepFlag, Vector2f.valueOf(listDot[iii + 3]));
					}
					break;
				case 'z': // closepath (relative)
					relative = true;
				case 'Z': // closepath (absolute)
					// 0 Element ...
					if (listDot != null) {
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
	
	List<String> splitCommand(final String data) {
		List<String> out = new ArrayList<>();
		StringBuilder tmpString = new StringBuilder(20);
		boolean isText = false;
		boolean isNumber = false;
		for (char it : data.toCharArray()) {
			if (it == ' ' || it == '\t' || it == '\r') {
				String elements = tmpString.toString();
				if (!elements.isEmpty()) {
					out.add(elements);
				}
				tmpString.setLength(0);
				isText = false;
				isNumber = false;
			} else if (Tools.checkNumber(it, true) || it == ',' || it == '.') {
				if (isText) {
					out.add(tmpString.toString());
					tmpString.setLength(0);
				}
				isText = false;
				isNumber = true;
				tmpString.append(it);
			} else if ((it <= 'Z' && it >= 'A') || (it <= 'z' && it >= 'a')) {
				if (isNumber) {
					out.add(tmpString.toString());
					tmpString.setLength(0);
				}
				isText = true;
				isNumber = false;
				tmpString.append(it);
			} else {
				Log.error("Can not parse path : '" + it + "'");
			}
		}
		String elements = tmpString.toString();
		if (!elements.isEmpty()) {
			out.add(elements);
		}
		return out;
	}
	
}
