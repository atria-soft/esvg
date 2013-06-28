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
#include <etk/Vector.h>
#include <etk/math/Vector2D.h>
#include <etk/os/FSNode.h>

#include <esvg/Base.h>
#include <draw/Image.h>

namespace esvg
{
	class Document : public esvg::Base
	{
		private:
			etk::UString m_fileName;
			bool m_loadOK;
			etk::UString m_version;
			etk::UString m_title;
			etk::Vector<esvg::Base *> m_subElementList;
			vec2 m_size;
			esvg::Renderer* m_renderedElement;
	
		public:
			Document(const etk::UString& _fileName);
			~Document(void);
			bool IsLoadOk(void) { return m_loadOK; };
			void DisplayDebug(void);
			void GenerateTestFile(void);
			void GenerateAnImage(int32_t _sizeX, int32_t _sizeY);
			void GenerateAnImage(ivec2 _size, draw::Image& _output);
			void GenerateAnImage(draw::Image& _output);
			virtual void AggDraw(esvg::Renderer& _myRenderer, agg::trans_affine& _basicTrans);
			uint8_t* GetPointerOnData(void);
			uint32_t GetSizeOnData(void);
			vec2 GetDefinedSize(void) { return m_size;};
	};
};

#endif
