/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ESVG_H__
#define __ESVG_H__

#include <etk/types.h>
#include <vector>
#include <etk/math/Vector2D.h>
#include <etk/os/FSNode.h>

#include <esvg/Base.h>
#include <draw/Image.h>

namespace esvg {
	class Document : public esvg::Base {
		private:
			std::string m_fileName;
			bool m_loadOK;
			std::string m_version;
			std::string m_title;
			std::vector<esvg::Base *> m_subElementList;
			vec2 m_size;
			esvg::Renderer* m_renderedElement;
		public:
			Document(const std::string& _fileName);
			~Document();
			bool isLoadOk() { return m_loadOK; };
			void displayDebug();
			void generateTestFile();
			void generateAnImage(int32_t _sizeX, int32_t _sizeY);
			void generateAnImage(ivec2 _size, draw::Image& _output);
			void generateAnImage(draw::Image& _output);
			virtual void aggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
			uint8_t* getPointerOnData();
			uint32_t getSizeOnData();
			vec2 getDefinedSize() { return m_size;};
	};
};

#endif

