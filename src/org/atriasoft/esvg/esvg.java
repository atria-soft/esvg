/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/Vector.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/uri/uri.hpp>

#include <esvg/Base.hpp>

/**
 * @brief Main esvg namespace
 */
namespace esvg {
	class Document : public esvg::Base {
		private:
			etk::Uri m_uri;
			bool m_loadOK;
			etk::String m_version;
			etk::String m_title;
			etk::Vector<ememory::SharedPtr<esvg::Base>> m_subElementList; //!< sub-element list
			etk::Vector<ememory::SharedPtr<esvg::Base>> m_refList; //!< reference elements ...
			vec2 m_size;
		public:
			Document();
			~Document();
			void clear();
			/**
			 * @brief parse a string that contain an svg stream
			 * @param[in] _data Data to parse
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool parse(const etk::String& _data);
			/**
			 * @brief generate a string that contain the created SVG
			 * @param[out] _data Data where the svg is stored
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool generate(etk::String& _data);
			/**
			 * @brief Load the file that might contain the svg
			 * @param[in] _uri File of the svg
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool load(const etk::Uri& _uri);
			/**
			 * @brief Store the SVG in the file
			 * @param[in] _uri File of the svg
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool store(const etk::Uri& _uri);
		protected:
			/**
			 * @brief change all style in a xml atribute
			 */
			virtual bool cleanStyleProperty(const exml::Element& _root);
			virtual bool parseXMLData(const exml::Element& _root, bool _isReference = false);
		public:
			bool isLoadOk() {
				return m_loadOK;
			};
			/**
			 * @brief Display all the node in the svg file.
			 */
			void displayDebug();
			// TODO: remove this fucntion : use generic function ...
			void generateAnImage(const etk::Uri& _uri, bool _visualDebug=false);
			void generateAnImage(const ivec2& _size, const etk::Uri& _uri, bool _visualDebug=false);
			/**
			 * @brief Generate Image in a specific format.
			 * @param[in,out] _size Size expected of the rendered image (value <=0 if it need to be automatic.) return the size generate
			 * @return Vector of the data used to display (simple vector: generic to transmit)
			 */
			etk::Vector<etk::Color<float,4>> renderImageFloatRGBA(ivec2& _size);
			//! @previous
			etk::Vector<etk::Color<float,3>> renderImageFloatRGB(ivec2& _size);
			//! @previous
			etk::Vector<etk::Color<uint8_t,4>> renderImageU8RGBA(ivec2& _size);
			//! @previous
			etk::Vector<etk::Color<uint8_t,3>> renderImageU8RGB(ivec2& _size);
			etk::Vector<etk::Vector<vec2>> getLines(vec2 _size=vec2(256,256));
		protected:
			void draw(esvg::Renderer& _myRenderer, mat2x3& _basicTrans, int32_t _level=0) override;
		public:
			vec2 getDefinedSize() {
				return m_size;
			};
			ememory::SharedPtr<esvg::Base> getReference(const etk::String& _name);
		protected:
			void drawShapePoints(etk::Vector<etk::Vector<vec2>>& _out,
			                     int32_t _recurtionMax,
			                     float _threshold,
			                     mat2x3& _basicTrans,
			                     int32_t _level=1) override;
	};
}

