package org.atriasoft.esvg;

import java.util.ArrayList;
import java.util.List;

import org.atriasoft.esvg.render.DynamicColor;
import org.atriasoft.esvg.render.PathModel;
import org.atriasoft.esvg.render.Point;
import org.atriasoft.esvg.render.PointList;
import org.atriasoft.esvg.render.SegmentList;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.Tools;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.util.Dynamic;
import org.atriasoft.esvg.internal.XmlHelper;
import org.w3c.dom.Element;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
public class Path extends Base {
	static final Logger LOGGER = LoggerFactory.getLogger(Path.class);
	
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

	public static PathModel createPathModel(final String d) {
		final PathModel out = new PathModel();
		LOGGER.trace("Parse Path : \"{}\"", d);
		final List<String> commandsSplited = Path.splitCommand(d);
		String[] listDot = null;

		// TODO REWORK this, can be done with a simple split and search in a list...
		for (Command sss = Path.extractCmd(commandsSplited, 0); sss != null;
				sss = Path.extractCmd(commandsSplited, sss.offset())) {
			boolean relative = false;
			listDot = sss.listElem();

			//			LOGGER.trace("Find new command : '" + sss.cmd + "'");
			//			if (listDot != null) {
			//				for (int jjj = 0; jjj < listDot.length; jjj++) {
			//					LOGGER.trace("            ->  '" + listDot[jjj] + "'");
			//				}
			//			} else {
			//				LOGGER.trace("            ->  no elements");
			//			}
			switch (sss.cmd) {
				case 'm': // Move to (relative)
					relative = true;
				case 'M': // Move to (absolute)
					if (listDot == null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot);
						break;
					}
					if (listDot.length % 2 != 0) {
						LOGGER.warn("the PATH command {} must be a multiple of 2", sss.cmd);
						break;
					}
					// 2 Elements ...
					if (listDot.length >= 2) {
						out.moveTo(relative, new Vector2f(Float.parseFloat(listDot[0]), Float.parseFloat(listDot[1])));
					}
					for (int iii = 2; iii < listDot.length; iii += 2) {
						out.lineTo(relative,
								new Vector2f(Float.parseFloat(listDot[iii]), Float.parseFloat(listDot[iii + 1])));
					}
					break;
				case 'l': // Line to (relative)
					relative = true;
				case 'L': // Line to (absolute)
					if (listDot == null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot);
						break;
					}
					if (listDot.length % 2 != 0) {
						LOGGER.warn("the PATH command {} must be a multiple of 2", sss.cmd);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 2) {
						out.lineTo(relative,
								new Vector2f(Float.parseFloat(listDot[iii]), Float.parseFloat(listDot[iii + 1])));
					}
					break;

				case 'v': // Vertical Line to (relative)
					relative = true;
				case 'V': // Vertical Line to (absolute)
					// 1 Element ...
					if (listDot == null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot);
						break;
					}
					for (final String element : listDot) {
						out.lineToV(relative, Float.parseFloat(element));
					}
					break;

				case 'h': // Horizantal Line to (relative)
					relative = true;
				case 'H': // Horizantal Line to (absolute)
					// 1 Element ...
					if (listDot == null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot);
						break;
					}
					for (final String element : listDot) {
						out.lineToH(relative, Float.parseFloat(element));
					}
					break;

				case 'q': // Quadratic Bezier curve (relative)
					relative = true;
				case 'Q': // Quadratic Bezier curve (absolute)
					if (listDot == null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot);
						break;
					}
					// 4 Elements ...
					if (listDot.length % 4 != 0) {
						LOGGER.warn("the PATH command {} has not the good number of element = {} (must have 4 numbers)", sss.cmd, listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 4) {
						out.bezierCurveTo(relative,
								new Vector2f(Float.parseFloat(listDot[iii]), Float.parseFloat(listDot[iii + 1])),
								new Vector2f(Float.parseFloat(listDot[iii + 2]), Float.parseFloat(listDot[iii + 3])));
					}
					break;

				case 't': // smooth quadratic Bezier curve to (relative)
					relative = true;
				case 'T': // smooth quadratic Bezier curve to (absolute)
					if (listDot == null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot);
						break;
					}
					// 4 Elements ...
					if (listDot.length % 2 != 0) {
						LOGGER.warn("the PATH command {} has not the good number of element = {} (must have 2 numbers)", sss.cmd, listDot.length);
						break;
					}
					// 2 Elements ...
					for (int iii = 0; iii < listDot.length; iii += 2) {
						out.bezierSmoothCurveTo(relative,
								new Vector2f(Float.parseFloat(listDot[iii]), Float.parseFloat(listDot[iii + 1])));
					}
					break;

				case 'c': // curve to (relative)
					relative = true;
				case 'C': // curve to (absolute)
					if (listDot == null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot);
						break;
					}
					// 6 Elements ...
					if (listDot.length % 6 != 0) {
						LOGGER.warn("the PATH command {} has not the good number of element = {} (Must be a multiple of 6)", sss.cmd, listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 6) {
						out.curveTo(relative,
								new Vector2f(Float.parseFloat(listDot[iii]), Float.parseFloat(listDot[iii + 1])),
								new Vector2f(Float.parseFloat(listDot[iii + 2]), Float.parseFloat(listDot[iii + 3])),
								new Vector2f(Float.parseFloat(listDot[iii + 4]), Float.parseFloat(listDot[iii + 5])));
					}
					break;

				case 's': // smooth curve to (relative)
					relative = true;
				case 'S': // smooth curve to (absolute)
					if (listDot == null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot);
						break;
					}
					// 4 Elements ...
					if (listDot.length % 4 != 0) {
						LOGGER.warn("the PATH command {} has not the good number of element = {} (Must be a multiple of 4)", sss.cmd, listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 4) {
						out.smoothCurveTo(relative,
								new Vector2f(Float.parseFloat(listDot[iii]), Float.parseFloat(listDot[iii + 1])),
								new Vector2f(Float.parseFloat(listDot[iii + 2]), Float.parseFloat(listDot[iii + 3])));
					}
					break;

				case 'a': // elliptical Arc (relative)
					relative = true;
				case 'A': // elliptical Arc (absolute)
					if (listDot == null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot);
						break;
					}
					// 4 element ff,ff f i,i ff,ff  Elements ...
					if (listDot.length % 7 != 0) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot.length);
						break;
					}
					for (int iii = 0; iii < listDot.length; iii += 7) {
						boolean largeArcFlag = true;
						boolean sweepFlag = true;
						if (Integer.parseInt(listDot[iii + 3]) == 0) {
							largeArcFlag = false;
						}
						if (Integer.parseInt(listDot[iii + 4]) == 0) {
							sweepFlag = false;
						}
						out.ellipticTo(relative,
								new Vector2f(Float.parseFloat(listDot[iii]), Float.parseFloat(listDot[iii + 1])),
								Float.parseFloat(listDot[iii + 2]), largeArcFlag, sweepFlag,
								new Vector2f(Float.parseFloat(listDot[iii + 5]), Float.parseFloat(listDot[iii + 6])));
					}
					break;
				case 'z': // closepath (relative)
					relative = true;
				case 'Z': // closepath (absolute)
					// 0 Element ...
					if (listDot != null) {
						LOGGER.warn("the PATH command {} has not the good number of element = {}", sss.cmd, listDot.length);
						break;
					}
					out.close(relative);
					break;
				default:
					LOGGER.error("Unknow error : '{}'", sss.cmd);
			}
		}
		return out;
	}

	//return the next char position ... (after 'X' or NULL)
	private static Command extractCmd(final List<String> input, final int offset) {
		if (input.size() <= offset) {
			//			LOGGER.warn("parse command : END");
			return null;
		}
		//		LOGGER.warn("parse command : (rest) " + offset);
		//		for (int iii = offset; iii < input.size(); iii++) {
		//			LOGGER.warn("        -[" + iii + "] '" + input.get(iii) + "'");
		//		}
		if (input.get(offset).length() != 1) {
			LOGGER.error("Error in the SVG Path : '{}' [{}]", input.get(offset), offset);
			return null;
		}
		final char cmd = input.get(offset).charAt(0);
		if (!((cmd <= 'Z' && cmd >= 'A') || (cmd <= 'z' && cmd >= 'a'))) {
			LOGGER.error("Error in the SVG Path : '{}' [{}]", cmd, offset);
			return null;
		}
		//LOGGER.trace("Find command : " + cmd);
		if (input.size() == offset) {
			return new Command(cmd, offset + 1);
		}
		int iii;
		for (iii = offset + 1; iii < input.size(); iii++) {
			final char startElem = input.get(iii).charAt(0);
			if ((startElem <= 'Z' && startElem >= 'A') || (startElem <= 'z' && startElem >= 'a')) {
				// find end of elements
				break;
			}
		}
		final int length = iii - (offset + 1);
		if (length == 0) {
			return new Command(cmd, null, iii);
		}
		final String[] outputList = new String[length];
		for (int jjj = 0; jjj < length; jjj++) {
			outputList[jjj] = input.get(offset + 1 + jjj);
		}
		return new Command(cmd, outputList, iii);
	}

	static List<String> splitCommand(final String data) {
		final List<String> out = new ArrayList<>();
		final StringBuilder tmpString = new StringBuilder(20);
		boolean isNumber = false;
		for (final char it : data.toCharArray()) {
			// ',' is here beause some people oprefer the ' ' instead of ','
			if (it == ' ' || it == '\t' || it == '\r' || it == '\n' || it == ',') {
				final String elements = tmpString.toString();
				if (!elements.isEmpty()) {
					out.add(elements);
				}
				tmpString.setLength(0);
				isNumber = false;
			} else if (Tools.checkNumber(it, true) || it == '.') {
				isNumber = true;
				tmpString.append(it);
			} else if ((it <= 'Z' && it >= 'A') || (it <= 'z' && it >= 'a')) {
				if (isNumber) {
					out.add(tmpString.toString());
					tmpString.setLength(0);
				}
				isNumber = false;
				out.add(Character.toString(it));
			} else {
				LOGGER.error("Can not parse path : '{}'", it);
			}
		}
		final String elements = tmpString.toString();
		if (!elements.isEmpty()) {
			out.add(elements);
		}
		return out;
	}

	public PathModel listElement = new PathModel();

	public Path(final PaintState parentPaintState) {
		super(parentPaintState);
	}

	public Path(final PathModel elements, final PaintState parentPaintState) {
		super(parentPaintState);
		this.listElement = elements;
	}

	@Override
	void display(final int spacing) {
		this.listElement.display(spacing);
	}

	@Override
	void draw(final Renderer myRenderer, final Matrix2x3f basicTrans, final int level) {
		LOGGER.trace("{}DRAW esvg::Path", spacingDist(level));

		final Matrix2x3f mtx = this.transformMatrix.multiply(basicTrans);

		PointList listPoints = new PointList();
		listPoints = this.listElement.generateListPoints(level, myRenderer.getInterpolationRecurtionMax(),
				myRenderer.getInterpolationThreshold());
		//listPoints.applyMatrix(mtx);
		final SegmentList listSegmentFill = new SegmentList();
		final SegmentList listSegmentStroke = new SegmentList();
		final Weight tmpFill = new Weight();
		final Weight tmpStroke = new Weight();
		final DynamicColor colorFill = DynamicColor.createColor(this.paint.fill, mtx);
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
			listSegmentStroke.createSegmentListStroke(listPoints, this.paint.strokeWidth, this.paint.lineCap,
					this.paint.lineJoin, this.paint.miterLimit);
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
	void drawShapePoints(
			final List<List<Vector2f>> out,
			final int recurtionMax,
			final float threshold,
			final Matrix2x3f basicTrans,
			final int level) {
		LOGGER.trace("{}DRAW Shape esvg::Path", spacingDist(level));

		final Matrix2x3f mtx = this.transformMatrix.multiply(basicTrans);

		PointList listPoints = new PointList();
		listPoints = this.listElement.generateListPoints(level, recurtionMax, threshold);
		listPoints.applyMatrix(mtx);
		for (final List<Point> it : listPoints.data) {
			final List<Vector2f> listPoint = new ArrayList<>();
			for (final Point itDot : it) {
				listPoint.add(itDot.pos);
			}
			out.add(listPoint);
		}
	}

	@Override
	boolean parseXML(final Element element, final Matrix2x3f parentTrans, final Dynamic<Vector2f> sizeMax) {
		if (element == null) {
			return false;
		}
		parseTransform(element);
		parsePaintAttr(element);

		// add the property of the parrent modifications ...
		this.transformMatrix = this.transformMatrix.multiply(parentTrans);

		final String elementXML1 = XmlHelper.attr(element, "d", "");
		if (elementXML1.length() == 0) {
			LOGGER.warn("path: missing 'd' attribute or empty");
			return false;
		}
		this.listElement = Path.createPathModel(elementXML1);
		return this.listElement != null;
	}

}
