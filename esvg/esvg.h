/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_H__
#define __ESVG_H__

#include <etk/types.h>
#include <vector>
#include <etk/math/Vector2D.h>
#include <etk/os/FSNode.h>

#include <esvg/Base.h>
//#include <draw/Image.h>

namespace esvg {
	class Document : public esvg::Base {
		private:
			std::string m_fileName;
			bool m_loadOK;
			std::string m_version;
			std::string m_title;
			std::vector<esvg::Base*> m_subElementList;
			vec2 m_size;
			esvg::Renderer* m_renderedElement;
		public:
			Document();
			Document(const std::string& _fileName);
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
			bool parseXMLData(const std::shared_ptr<exml::Element>& _root);
		public:
			bool isLoadOk() {
				return m_loadOK;
			};
			void displayDebug();
			void generateTestFile();
			void generateAnImage(const ivec2& _size, const std::string& _fileName, bool _visualDebug=false);
			//void generateAnImage(ivec2 _size, draw::Image& _output);
			//void generateAnImage(draw::Image& _output);
			virtual void draw(esvg::Renderer& _myRenderer, mat2& _basicTrans);
			uint8_t* getPointerOnData();
			uint32_t getSizeOnData();
			vec2 getDefinedSize() {
				return m_size;
			};
	};
};

#endif

