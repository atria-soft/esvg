package org.atriasoft.esvg;

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

class Base {
	public static float kappa90; //!< proportional lenght to the radius of a bezier handle for 90° arcs.
	protected PaintState paint;
	protected mat2x3 transformMatrix; //!< specific render of the curent element
	
	protected String spacingDist(int _spacing);
	
	public Base() {};
	
	Base(PaintState _parentPaintState);
	
	/**
	 * parse all the element needed in the basic node
	 * @param _element standart XML node
	 * @return true if no problem arrived
	 */
	boolean parseXML(const exml::Element& _element, mat2x3& _parentTrans, Vector2f& _sizeMax);
	
	/**
	 * Draw the form in the renderer
	 * @param _myRenderer Renderer engine
	 * @param _basicTrans Parant transformation of the environement
	 * @param _level Level of the tree
	 */
	void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level=1);
	
	/**
	 * Draw rhe shape with all points
	 * @param _out where the lines are added
	 * @param _recurtionMax interpolation recurtion max
	 * @param _threshold threshold to stop recurtion
	 * @param _basicTrans Parant transformation of the environement
	 * @param _level Level of the tree
	 */
	void drawShapePoints(final List<List<Vector2f>> _out,
		                             final int _recurtionMax,
		                             final float _threshold,
		                             final mat2x3 _basicTrans,
		                             final int _level=1);
	
	void display(final int _spacing) {};
	
	void parseTransform(const exml::Element& _element);
	
	/**
	 * parse x, y, width, height attribute of the xml node
	 * @param _element XML node
	 * @param _pos parsed position
	 * @param _size parsed dimention
	 */
	void parsePosition(const exml::Element& _element, Vector2f &_pos, Vector2f &_size);
	
	/**
	 * parse a lenght of the xml element
	 * @param _dataInput Data C String with the printed lenght
	 * @return standard number of pixels
	 */
	float parseLength(const etk::String& _dataInput);
	Pair<float, enum esvg::distance> parseLength2(const etk::String& _dataInput);
	/**
	 * parse a Painting attribute of a specific node
	 * @param _element Basic node of the XML that might be parsed
	 */
	void parsePaintAttr(exml::Element _element);
	/**
	 * parse a color specification from the svg file
	 * @param _inputData Data C String with the xml definition
	 * @return The parsed color (color used and the link if needed)
	 */
	Pair<Color, String> parseColor(String _inputData);
	protected String id; //!< unique ID of the element.
		
	/**
	 * Get the ID of the Element
	 * @return UniqueId in the svg file
	 */
	public String getId() {
		return this.id;
	}
	/**
	 * Set the ID of the Element
	 * @param _newId New Id of the element
	 */
	public void setId(String _newId) {
		this.id = _newId;
	}
}
