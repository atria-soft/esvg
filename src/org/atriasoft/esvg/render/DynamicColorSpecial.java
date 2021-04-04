package org.atriasoft.esvg.render;

import java.util.List;

import org.atriasoft.esvg.SpreadMethod;
import org.atriasoft.esvg.Base;
import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.esvg.GradientUnits;
import org.atriasoft.esvg.LinearGradient;
import org.atriasoft.esvg.RadialGradient;
import org.atriasoft.esvg.internal.Log;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.Dimension;
import org.atriasoft.etk.Dimension1D;
import org.atriasoft.etk.Distance;
import org.atriasoft.etk.math.FMath;
import org.atriasoft.etk.math.Vector2f;
import org.atriasoft.etk.math.Vector2i;
import org.atriasoft.etk.math.Matrix2x3f;
import org.atriasoft.etk.util.Pair;

public class DynamicColorSpecial implements DynamicColor {
	protected static Vector2f getIntersect(final Vector2f point1, final Vector2f vect1, final Vector2f point2, final Vector2f vect2) {
		float diviseur = vect1.x() * vect2.y() - vect1.y() * vect2.x();
		if (diviseur != 0.0f) {
			float mmm = (vect1.x() * point1.y() - vect1.x() * point2.y() - vect1.y() * point1.x() + vect1.y() * point2.x()) / diviseur;
			return point2.add(vect2.multiply(mmm));
		}
		Log.error("Get divider / 0.0f");
		return point2;
	}
	
	protected static Pair<Vector2f, Vector2f> intersectLineToCircle(final Vector2f pos1, final Vector2f pos2) {
		return DynamicColorSpecial.intersectLineToCircle(pos1, pos2, Vector2f.ZERO);
	}
	
	protected static Pair<Vector2f, Vector2f> intersectLineToCircle(final Vector2f pos1, final Vector2f pos2, final Vector2f center) {
		return DynamicColorSpecial.intersectLineToCircle(pos1, pos2, center, 1.0f);
	}
	
	protected static Pair<Vector2f, Vector2f> intersectLineToCircle(final Vector2f pos1, final Vector2f pos2, final Vector2f center, final float radius) {
		Vector2f v1;
		Vector2f v2;
		//vector2D from point 1 to point 2
		v1 = pos2.less(pos1);
		//vector2D from point 1 to the circle's center
		v2 = center.less(pos1);
		
		float dot = v1.dot(v2);
		Vector2f proj1 = new Vector2f(((dot / (v1.length2())) * v1.x()), ((dot / (v1.length2())) * v1.y()));
		Vector2f midpt = pos1.add(proj1);
		
		float distToCenter = midpt.less(center).length2();
		if (distToCenter > radius * radius) {
			return new Pair<>(Vector2f.ZERO, Vector2f.ZERO);
		}
		if (distToCenter == radius * radius) {
			return new Pair<>(midpt, midpt);
		}
		float distToIntersection;
		if (distToCenter == 0.0f) {
			distToIntersection = radius;
		} else {
			distToCenter = FMath.sqrt(distToCenter);
			distToIntersection = FMath.sqrt(radius * radius - distToCenter * distToCenter);
		}
		// normalize...
		v1.safeNormalize();
		v1 = v1.multiply(distToIntersection);
		return new Pair<>(midpt.add(v1), midpt.less(v1));
	}
	
	public Vector2f axeX;
	public Vector2f axeY;
	public Vector2f baseSize;
	public boolean centerIsFocal;
	public boolean clipOut;
	public String colorName;
	public List<Pair<Float, Color>> data;
	public Vector2f focal; // Specific radius
	public float focalLength;
	public boolean linear;
	public Matrix2x3f matrix;
	
	public Vector2f pos1; // in radius ==> center
	
	public Vector2f pos2; // in radius ==> radius end position
	
	public SpreadMethod spread;
	
	public GradientUnits unit;
	
	public Pair<Vector2f, Vector2f> viewPort;
	
	public DynamicColorSpecial(final String link, final Matrix2x3f mtx) {
		this.linear = true;
		this.colorName = link;
		this.matrix = mtx;
		this.viewPort = new Pair<>(Vector2f.MAX_VALUE, Vector2f.MAX_VALUE);
	}
	
	@Override
	public void generate(final EsvgDocument document) {
		if (document == null) {
			Log.error("Get null input for document");
		}
		Base base = document.getReference(this.colorName);
		if (base == null) {
			Log.error("Can not get base : '" + this.colorName + "'");
			return;
		}
		// Now we can know if we use linear or radial gradient ...
		if (base instanceof LinearGradient gradient) {
			this.linear = true;
			Log.verbose("get for color linear:");
			gradient.display(2);
			this.unit = gradient.unit;
			this.spread = gradient.spread;
			Log.verbose("    viewport = {" + this.viewPort.first + "," + this.viewPort.second + "}");
			Vector2f size = this.viewPort.second.less(this.viewPort.first);
			
			Dimension dimPos1 = gradient.getPosition1();
			this.pos1 = dimPos1.getPixel(size);
			if (dimPos1.getType() == Distance.POURCENT) {
				this.pos1 = this.pos1.add(this.viewPort.first);
			}
			Dimension dimPos2 = gradient.getPosition2();
			this.pos2 = dimPos2.getPixel(size);
			if (dimPos2.getType() == Distance.POURCENT) {
				this.pos2 = this.pos2.add(this.viewPort.first);
			}
			// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
			Vector2f delta = this.pos2.less(this.pos1);
			if (delta.x() < 0.0f) {
				this.axeX = new Vector2f(-1.0f, 0.0f);
			} else {
				this.axeX = new Vector2f(1.0f, 0.0f);
			}
			if (delta.y() < 0.0f) {
				this.axeY = new Vector2f(0.0f, -1.0f);
			} else {
				this.axeY = new Vector2f(0.0f, 1.0f);
			}
			// Move the positions ...
			this.pos1 = this.matrix.multiply(this.pos1);
			this.pos2 = this.matrix.multiply(this.pos2);
			this.axeX = this.matrix.applyScaleRotation(this.axeX);
			this.axeY = this.matrix.applyScaleRotation(this.axeY);
			// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
			Vector2f intersecX = DynamicColorSpecial.getIntersect(this.pos1, this.axeX, this.pos2, this.axeY);
			Vector2f intersecY = DynamicColorSpecial.getIntersect(this.pos1, this.axeY, this.pos2, this.axeX);
			this.baseSize = new Vector2f((this.pos1.less(intersecX)).length(), (this.pos1.less(intersecY)).length());
			// get all the colors
			this.data = gradient.getColors(document);
		} else {
			this.linear = false;
			if (!(base instanceof RadialGradient gradient)) {
				Log.error("Can not cast in a linear gradient: '" + this.colorName + "' ==> wrong type");
				return;
			}
			Log.verbose("get for color Radial:");
			gradient.display(2);
			this.unit = gradient.unit;
			this.spread = gradient.spread;
			Log.verbose("    viewport = {" + this.viewPort.first + "," + this.viewPort.second + "}");
			Vector2f size = this.viewPort.second.less(this.viewPort.first);
			
			Dimension dimCenter = gradient.getCenter();
			Vector2f center = dimCenter.getPixel(size);
			if (dimCenter.getType() == Distance.POURCENT) {
				center = center.add(this.viewPort.first);
			}
			Dimension dimFocal = gradient.getFocal();
			Vector2f focal = dimFocal.getPixel(size);
			if (dimFocal.getType() == Distance.POURCENT) {
				focal = focal.add(this.viewPort.first);
			}
			Dimension1D dimRadius = gradient.getRadius();
			// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object)..
			if (center == focal) {
				this.centerIsFocal = true;
				this.pos2 = new Vector2f(dimRadius.getPixel(size.x()), dimRadius.getPixel(size.y()));
				this.pos2 = this.pos2.add(center);
				Vector2f delta = center.less(this.pos2);
				if (delta.x() < 0.0f) {
					this.axeX = new Vector2f(-1.0f, 0.0f);
				} else {
					this.axeX = new Vector2f(1.0f, 0.0f);
				}
				if (delta.y() < 0.0f) {
					this.axeY = new Vector2f(0.0f, -1.0f);
				} else {
					this.axeY = new Vector2f(0.0f, 1.0f);
				}
				this.pos1 = center;
			} else {
				this.centerIsFocal = false;
				this.axeX = center.less(focal).safeNormalize();
				this.axeY = new Vector2f(this.axeX.y(), -this.axeX.x());
				
				this.pos2 = this.axeX.multiply(dimRadius.getPixel(size.x())).add(this.axeY.multiply(dimRadius.getPixel(size.y())));
				this.pos2 = this.pos2.add(center);
				this.pos1 = center;
			}
			// Move the positions ...
			this.pos1 = this.matrix.multiply(this.pos1);
			center = this.matrix.multiply(center);
			this.pos2 = this.matrix.multiply(this.pos2);
			this.axeX = this.matrix.applyScaleRotation(this.axeX);
			this.axeY = this.matrix.applyScaleRotation(this.axeY);
			// in the basic version of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
			Vector2f intersecX = DynamicColorSpecial.getIntersect(this.pos1, this.axeX, this.pos2, this.axeY);
			Vector2f intersecY = DynamicColorSpecial.getIntersect(this.pos1, this.axeY, this.pos2, this.axeX);
			this.baseSize = new Vector2f((intersecX.less(this.pos1)).length(), (intersecY.less(this.pos1)).length());
			if (!this.centerIsFocal) {
				this.focalLength = (center.less(this.matrix.multiply(focal))).length();
				if (this.focalLength >= this.baseSize.x()) {
					Log.debug("Change position of the Focal ... ==> set it inside the circle");
					this.focalLength = this.baseSize.x() * 0.999998f;
					this.clipOut = true;
				} else {
					this.clipOut = false;
				}
			}
			Log.verbose("baseSize=" + this.baseSize + " this.pos1=" + this.pos1 + " dim=" + dimCenter + " this.focal=" + this.focal + " this.pos2=" + this.pos2 + " dim=" + dimRadius);
			// get all the colors
			this.data = gradient.getColors(document);
		}
	}
	
	@Override
	public Color getColor(final Vector2i pos) {
		if (this.data.size() < 2) {
			return Color.PURPLE;
		}
		if (this.linear) {
			return getColorLinear(pos);
		}
		return getColorRadial(pos);
	}
	
	private Color getColorLinear(final Vector2i pos) {
		float ratio = 0.0f;
		if (this.unit == GradientUnits.gradientUnitsuserSpaceOnUse) {
			Vector2f vectorBase = this.pos2.less(this.pos1);
			Vector2f vectorOrtho = new Vector2f(vectorBase.y(), -vectorBase.x());
			Vector2f intersec = DynamicColorSpecial.getIntersect(this.pos1, vectorBase, new Vector2f(pos.x(), pos.y()), vectorOrtho);
			float baseSize = vectorBase.length();
			Vector2f vectorBaseDraw = intersec.less(this.pos1);
			float baseDraw = vectorBaseDraw.length();
			ratio = baseDraw / baseSize;
			switch (this.spread) {
				default:
				case PAD:
					if (vectorBase.dot(vectorBaseDraw) < 0) {
						ratio *= -1.0;
					}
					break;
				case REFLECT:
					ratio -= ((int) (ratio) >> 1) + 1;
					if (ratio > 1.0f) {
						ratio = 2.0f - ratio;
					}
					break;
				case REPEAT:
					if (vectorBase.dot(vectorBaseDraw) < 0) {
						ratio *= -1.0;
					}
					ratio -= ((int) (ratio));
					
					if (ratio < 0.0f) {
						ratio = 1.0f - FMath.abs(ratio);
					}
					break;
			}
		} else {
			// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object..
			Vector2f intersecX = DynamicColorSpecial.getIntersect(this.pos1, this.axeX, new Vector2f(pos.x(), pos.y()), this.axeY);
			Vector2f intersecY = DynamicColorSpecial.getIntersect(this.pos1, this.axeY, new Vector2f(pos.x(), pos.y()), this.axeX);
			Vector2f vectorBaseDrawX = intersecX.less(this.pos1);
			Vector2f vectorBaseDrawY = intersecY.less(this.pos1);
			float baseDrawX = vectorBaseDrawX.length();
			float baseDrawY = vectorBaseDrawY.length();
			if (this.axeX.dot(vectorBaseDrawX) < 0) {
				baseDrawX *= -1.0f;
			}
			if (this.axeY.dot(vectorBaseDrawY) < 0) {
				baseDrawY *= -1.0f;
			}
			if (this.baseSize.x() + this.baseSize.y() != 0.0f) {
				if (this.baseSize.x() != 0.0f && this.baseSize.y() != 0.0f) {
					ratio = (baseDrawX * this.baseSize.y() + baseDrawY * this.baseSize.x()) / (this.baseSize.x() * this.baseSize.y() * 2.0f);
				} else if (this.baseSize.x() != 0.0f) {
					ratio = baseDrawX / this.baseSize.x();
				} else {
					ratio = baseDrawY / this.baseSize.y();
				}
			} else {
				ratio = 1.0f;
			}
			switch (this.spread) {
				default:
				case PAD:
					// nothing to do ...
					break;
				case REFLECT:
					ratio = FMath.abs(ratio);
					ratio -= ((int) (ratio) >> 1) + 1;
					if (ratio > 1.0f) {
						ratio = 2.0f - ratio;
					}
					break;
				case REPEAT:
					ratio -= ((int) (ratio));
					if (ratio < 0.0f) {
						ratio = 1.0f - FMath.abs(ratio);
					}
					break;
			}
		}
		if (ratio <= this.data.get(0).first * 0.01f) {
			return this.data.get(0).second;
		}
		if (ratio >= this.data.get(this.data.size() - 1).first * 0.01f) {
			return this.data.get(this.data.size() - 1).second;
		}
		for (int iii = 1; iii < this.data.size(); ++iii) {
			if (ratio <= this.data.get(iii).first * 0.01f) {
				float localRatio = ratio - this.data.get(iii - 1).first * 0.01f;
				localRatio = localRatio / ((this.data.get(iii).first - this.data.get(iii - 1).first) * 0.01f);
				return new Color(this.data.get(iii - 1).second.r() * (1.0 - localRatio) + this.data.get(iii).second.r() * localRatio,
						this.data.get(iii - 1).second.g() * (1.0 - localRatio) + this.data.get(iii).second.g() * localRatio,
						this.data.get(iii - 1).second.b() * (1.0 - localRatio) + this.data.get(iii).second.b() * localRatio,
						this.data.get(iii - 1).second.a() * (1.0 - localRatio) + this.data.get(iii).second.a() * localRatio);
			}
		}
		return Color.GREEN;
	}
	
	private Color getColorRadial(final Vector2i pos) {
		float ratio = 0.0f;
		// in the basic vertion of the gradient the color is calculated with the ration in X and Y in the bonding box associated (it is rotate with the object)..
		Vector2f intersecX = DynamicColorSpecial.getIntersect(this.pos1, this.axeX, new Vector2f(pos.x(), pos.y()), this.axeY);
		Vector2f intersecY = DynamicColorSpecial.getIntersect(this.pos1, this.axeY, new Vector2f(pos.x(), pos.y()), this.axeX);
		Vector2f vectorBaseDrawX = intersecX.less(this.pos1);
		Vector2f vectorBaseDrawY = intersecY.less(this.pos1);
		float baseDrawX = vectorBaseDrawX.length();
		float baseDrawY = vectorBaseDrawY.length();
		// specal case when focal == center (this is faster ...)
		if (this.centerIsFocal) {
			ratio = (new Vector2f(baseDrawX, baseDrawY)).length();
			if (this.baseSize.x() + this.baseSize.y() != 0.0f) {
				if (this.baseSize.x() != 0.0f && this.baseSize.y() != 0.0f) {
					ratio = new Vector2f(baseDrawX / this.baseSize.x(), baseDrawY / this.baseSize.y()).length();
				} else if (this.baseSize.x() != 0.0f) {
					ratio = baseDrawX / this.baseSize.x();
				} else {
					ratio = baseDrawY / this.baseSize.y();
				}
			} else {
				ratio = 1.0f;
			}
		} else {
			// set the sense of the elements:
			if (this.axeX.dot(vectorBaseDrawX) < 0) {
				baseDrawX *= -1.0f;
			}
			if (this.axeY.dot(vectorBaseDrawY) < 0) {
				baseDrawY *= -1.0f;
			}
			if (this.baseSize.y() != 0.0f) {
				baseDrawY /= this.baseSize.y();
			}
			// normalize to 1.0f
			baseDrawX /= this.baseSize.x();
			if (this.clipOut && baseDrawX <= -1.0f) {
				ratio = 1.0f;
			} else {
				float tmpLength = -this.focalLength / this.baseSize.x();
				Vector2f focalCenter = new Vector2f(tmpLength, 0.0f);
				Vector2f currentPoint = new Vector2f(baseDrawX, baseDrawY);
				if (focalCenter == currentPoint) {
					ratio = 0.0f;
				} else {
					Pair<Vector2f, Vector2f> positions = DynamicColorSpecial.intersectLineToCircle(focalCenter, currentPoint);
					float lenghtBase = currentPoint.less(focalCenter).length();
					float lenghtBorder1 = positions.first.less(focalCenter).length();
					//float lenghtBorder2 = positions.second.less(focalCenter).length();
					ratio = lenghtBase / lenghtBorder1;
				}
			}
		}
		switch (this.spread) {
			default:
			case PAD:
				// nothing to do ...
				break;
			case REFLECT:
				ratio -= ((int) (ratio) >> 1) + 1;
				if (ratio > 1.0f) {
					ratio = 2.0f - ratio;
				}
				break;
			case REPEAT:
				ratio -= ((int) (ratio));
				if (ratio < 0.0f) {
					ratio = 1.0f - FMath.abs(ratio);
				}
				break;
		}
		if (ratio <= this.data.get(0).first * 0.01f) {
			return this.data.get(0).second;
		}
		if (ratio >= this.data.get(this.data.size() - 1).first * 0.01f) {
			return this.data.get(this.data.size() - 1).second;
		}
		for (int iii = 1; iii < this.data.size(); ++iii) {
			if (ratio <= this.data.get(iii).first * 0.01f) {
				float localRatio = ratio - this.data.get(iii - 1).first * 0.01f;
				localRatio = localRatio / ((this.data.get(iii).first - this.data.get(iii - 1).first) * 0.01f);
				return new Color(this.data.get(iii - 1).second.r() * (1.0 - localRatio) + this.data.get(iii).second.r() * localRatio,
						this.data.get(iii - 1).second.g() * (1.0 - localRatio) + this.data.get(iii).second.g() * localRatio,
						this.data.get(iii - 1).second.b() * (1.0 - localRatio) + this.data.get(iii).second.b() * localRatio,
						this.data.get(iii - 1).second.a() * (1.0 - localRatio) + this.data.get(iii).second.a() * localRatio);
			}
		}
		return Color.GREEN;
	}
	
	@Override
	public void setViewPort(final Pair<Vector2f, Vector2f> viewPort) {
		this.viewPort = viewPort;
	}
}