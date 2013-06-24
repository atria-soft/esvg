/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __SVG_PARSER_H__
#define __SVG_PARSER_H__

#include <etk/types.h>
#include <etk/Vector.h>
#include <etk/math/Vector2D.h>
#include <etk/os/FSNode.h>

#include <parserSVG/Base.h>
#include <draw/Image.h>

namespace svg
{
	class Parser : public svg::Base
	{
		private:
			etk::UString m_fileName;
			bool m_loadOK;
			etk::UString m_version;
			etk::UString m_title;
			etk::Vector<svg::Base *> m_subElementList;
			vec2 m_size;
			svg::Renderer* m_renderedElement;
	
		public:
			Parser(etk::UString _fileName);
			~Parser(void);
			bool IsLoadOk(void) { return m_loadOK; };
			void DisplayDebug(void);
			void GenerateTestFile(void);
			void GenerateAnImage(int32_t _sizeX, int32_t _sizeY);
			void GenerateAnImage(ivec2 _size, draw::Image& _output);
			void GenerateAnImage(draw::Image& _output);
			virtual void AggDraw(svg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
			uint8_t* GetPointerOnData(void);
			uint32_t GetSizeOnData(void);
			vec2 GetDefinedSize(void) { return m_size;};
	};
};

#endif

