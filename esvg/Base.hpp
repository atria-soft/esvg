/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <esvg/join.hpp>
#include <esvg/cap.hpp>

#pragma once

#include <etk/types.hpp>
#include <vector>
#include <etk/math/Vector2D.hpp>
#include <etk/math/Matrix2.hpp>
#include <etk/Color.hpp>
#include <esvg/render/Path.hpp>

#include <exml/exml.hpp>
#include <esvg/Renderer.hpp>
#include <esvg/Dimension.hpp>

namespace esvg {
	extern const float kappa90; //!< proportional lenght to the radius of a bezier handle for 90° arcs.
	/**
	 * @brief Painting mode of the Object:
	 */
	enum paint {
		paint_none, //!< No painting.
		paint_color, //!< Painting a color.
		paint_gradientLinear, //!< Painting a linear gradient.
		paint_gradientRadial //!< Painting a radial gradient.
	};
	
	class PaintState {
		public:
			PaintState();
			void clear();
		public:
			std::pair<etk::Color<float,4>, std::string> fill;
			std::pair<etk::Color<float,4>, std::string> stroke;
			float strokeWidth;
			bool flagEvenOdd; //!< Fill rules
			enum esvg::cap lineCap;
			enum esvg::join lineJoin;
			float miterLimit;
			std::pair<vec2, vec2> viewPort; //!< min pos, max pos
			float opacity;
	};
	
	class Base {
		protected:
			PaintState m_paint;
			mat2 m_transformMatrix; //!< specific render of the curent element
			const char * spacingDist(int32_t _spacing);
		public:
			Base() {};
			Base(PaintState _parentPaintState);
			virtual ~Base() { };
			/**
			 * @brief parse all the element needed in the basic node
			 * @param[in] _element standart XML node
			 * @return true if no problem arrived
			 */
			virtual bool parseXML(const exml::Element& _element, mat2& _parentTrans, vec2& _sizeMax);
			/**
			 * @brief Draw the form in the renderer
			 * @param[in] _myRenderer Renderer engine
			 * @param[in] _basicTrans Parant transformation of the environement
			 * @param[in] _level Level of the tree
			 */
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level=1);
			/**
			 * @brief Draw rhe shape with all points
			 * @param[in] _out where the lines are added
			 * @param[in] _recurtionMax interpolation recurtion max
			 * @param[in] _threshold threshold to stop recurtion
			 * @param[in] _basicTrans Parant transformation of the environement
			 * @param[in] _level Level of the tree
			 */
			virtual void drawShapePoints(std::vector<std::vector<vec2>>& _out,
			                             int32_t _recurtionMax,
			                             float _threshold,
			                             mat2& _basicTrans,
			                             int32_t _level=1);
			
			virtual void display(int32_t _spacing) { };
			void parseTransform(const exml::Element& _element);
			/**
			 * @brief parse x, y, width, height attribute of the xml node
			 * @param[in] _element XML node
			 * @param[out] _pos parsed position
			 * @param[out] _size parsed dimention
			 */
			void parsePosition(const exml::Element& _element, vec2 &_pos, vec2 &_size);
			/**
			 * @brief parse a lenght of the xml element
			 * @param[in] _dataInput Data C String with the printed lenght
			 * @return standard number of pixels
			 */
			float parseLength(const std::string& _dataInput);
			std::pair<float, enum esvg::distance> parseLength2(const std::string& _dataInput);
			/**
			 * @brief parse a Painting attribute of a specific node
			 * @param[in] _element Basic node of the XML that might be parsed
			 */
			void parsePaintAttr(const exml::Element& _element);
			/**
			 * @brief parse a color specification from the svg file
			 * @param[in] _inputData Data C String with the xml definition
			 * @return The parsed color (color used and the link if needed)
			 */
			std::pair<etk::Color<float,4>, std::string> parseColor(const std::string& _inputData);
		protected:
			std::string m_id; //!< unique ID of the element.
		public:
			/**
			 * @brief Get the ID of the Element
			 * @return UniqueId in the svg file
			 */
			const std::string& getId() const;
			/**
			 * @brief Set the ID of the Element
			 * @param[in] _newId New Id of the element
			 */
			void setId(const std::string& _newId);
	};
};
