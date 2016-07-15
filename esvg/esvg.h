/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <vector>
#include <etk/math/Vector2D.h>
#include <etk/os/FSNode.h>

#include <esvg/Base.h>

namespace esvg {
	class Document : public esvg::Base {
		private:
			std::string m_fileName;
			bool m_loadOK;
			std::string m_version;
			std::string m_title;
			std::vector<ememory::SharedPtr<esvg::Base>> m_subElementList; //!< sub-element list
			std::vector<ememory::SharedPtr<esvg::Base>> m_refList; //!< reference elements ...
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
			bool parse(const std::string& _data);
			/**
			 * @brief generate a string that contain the created SVG
			 * @param[out] _data Data where the svg is stored
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool generate(std::string& _data);
			/**
			 * @brief Load the file that might contain the svg
			 * @param[in] _file Filename of the svg (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool load(const std::string& _file);
			/**
			 * @brief Store the SVG in the file
			 * @param[in] _file Filename of the svg (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool store(const std::string& _file);
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
			void generateAnImage(const std::string& _fileName, bool _visualDebug=false);
			void generateAnImage(const ivec2& _size, const std::string& _fileName, bool _visualDebug=false);
			/**
			 * @brief Generate Image in a specific format.
			 * @param[in,out] _size Size expected of the rendered image (value <=0 if it need to be automatic.) return the size generate
			 * @return Vector of the data used to display (simple vector: generic to transmit)
			 */
			std::vector<etk::Color<float,4>> renderImageFloatRGBA(ivec2& _size);
			//! @previous
			std::vector<etk::Color<float,3>> renderImageFloatRGB(ivec2& _size);
			//! @previous
			std::vector<etk::Color<uint8_t,4>> renderImageU8RGBA(ivec2& _size);
			//! @previous
			std::vector<etk::Color<uint8_t,3>> renderImageU8RGB(ivec2& _size);
		protected:
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans, int32_t _level=0);
		public:
			vec2 getDefinedSize() {
				return m_size;
			};
			ememory::SharedPtr<esvg::Base> getReference(const std::string& _name);
	};
}

