/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_RENDERER_PATH_H__
#define __ESVG_RENDERER_PATH_H__

#include <etk/types.h>
#include <etk/math/Vector2D.h>


namespace esvg {
	class RenderPath {
		public:
			std::vector<vec2> m_points;
		public:
			RenderPath() {
				
			}
			
			~RenderPath() {
				
			}
			void clear();
			void stop();
			void addPoint(const vec2& _pos);
			
			void moveTo(bool _relative, vec2 _pos);
			void lineTo(bool _relative, vec2 _pos);
			void curve4To(bool _relative, vec2 _pos1, vec2 _pos2, vec2 _pos);
			void curve4SmoothTo(bool _relative, vec2 _pos2, vec2 _pos);
			void curve3To(bool _relative, vec2 _pos1, vec2 _pos);
			void curve3SmoothTo(bool _relative, vec2 _pos);
			//void ellipticTo(bool _relative, 7 values ...);
			
			vec2 relativeToAbsolute(const vec2& _value);
			void display();
	};
};

#endif
