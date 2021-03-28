package org.atriasoft.esvg;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<etk/types.hpp>#include<etk/Vector.hpp>#include<etk/math/Vector2D.hpp>#include<etk/uri/uri.hpp>

#include<esvg/Base.hpp>

/**
 * Main esvg namespace
 */
namespace esvg{
class Document extends esvg::Base
{
		private:
			etk::Uri this.uri;
			boolean this.loadOK;
			etk::String this.version;
			etk::String this.title;
			List<ememory::SharedPtr<esvg::Base>> this.subElementList; //!< sub-element list
			List<ememory::SharedPtr<esvg::Base>> this.refList; //!< reference elements ...
			Vector2f this.size;
		public:
			Document();
			~Document();
	
	void clear();
	
	/**
			 * parse a string that contain an svg stream
			 * @param _data Data to parse
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			boolean parse(const etk::String& _data);
	
	/**
			 * generate a string that contain the created SVG
			 * @param _data Data where the svg is stored
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			boolean generate(etk::String& _data);
	
	/**
			 * Load the file that might contain the svg
			 * @param _uri File of the svg
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			boolean load(const etk::Uri& _uri);
	
	/**
			 * Store the SVG in the file
			 * @param _uri File of the svg
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			boolean store(const etk::Uri& _uri);
		protected:
			/**
			 * change all style in a xml atribute
			 */
			virtual
	
	boolean cleanStyleProperty(const exml::Element& _root);
			virtual
	
	boolean parseXMLData(const exml::Element& _root, boolean _isReference = false);
		public:
	
	boolean isLoadOk() {
				return this.loadOK;
			};
	
	/**
			 * Display all the node in the svg file.
			 */
			void displayDebug();
	
	// TODO: remove this fucntion : use generic function ...
	void generateAnImage(const etk::Uri& _uri, boolean _visualDebug=false);
	
	void generateAnImage(const Vector2i& _size, const etk::Uri& _uri, boolean _visualDebug=false);
			/**
			 * Generate Image in a specific format.
			 * @param[in,out] _size Size expected of the rendered image (value <=0 if it need to be automatic.) return the size generate
			 * @return Vector of the data used to display (simple vector: generic to transmit)
			 */
			List<etk::Color<float,4>> renderImageFloatRGBA(Vector2i& _size);
			//! @previous
			List<etk::Color<float,3>> renderImageFloatRGB(Vector2i& _size);
			//! @previous
			List<etk::Color<uint8_t,4>> renderImageU8RGBA(Vector2i& _size);
			//! @previous
			List<etk::Color<uint8_t,3>> renderImageU8RGB(Vector2i& _size);
	
	List<List<Vector2f>> getLines(final Vector2f _size=Vector2f(256,256));
		protected:
	
	void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int _level=0) override;
		public:
	
	Vector2f getDefinedSize() {
				return this.size;
			};ememory::SharedPtr<esvg::Base>
	
	getReference(const etk::String& _name);
		protected:
	
	void drawShapePoints(final List<List<Vector2f>>& _out,
			                     int _recurtionMax,
			                     float _threshold,
			                     mat2x3& _basicTrans,
			                     int _level=1) override;
	};
}
