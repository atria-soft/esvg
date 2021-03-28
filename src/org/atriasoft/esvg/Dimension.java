package org.atriasoft.esvg;
/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include<etk/types.hpp>#include<etk/math/Vector2D.hpp>

namespace esvg{
/**
 * in the dimention class we store the data as the more usefull unit (pixel) 
 * but one case need to be dynamic the %, then when requested in % the register the % value
 */
class Dimension {
	private:Vector2f this.data;
	enum distance this.type;
	public:
			/**
			 * Constructor (default :0,0 mode pixel)
			 */
			Dimension();
	
	/**
			 * Constructor
			 * @param _size Requested dimention
			 * @param _type Unit of the Dimention
			 */
			Dimension(const Vector2f& _size, enum esvg::distance _type=esvg::distance_pixel);
			/**
			 * Constructor
			 * @param _config dimension configuration.
			 */
			Dimension(const etk::String& _config) :
			  this.data(0,0),
			  this.type(esvg::distance_pixel) {
				set(_config);
			};
			/**
			 * Constructor
			 * @param _configX dimension X configuration.
			 * @param _configY dimension Y configuration.
			 */
			Dimension(const etk::String& _configX, const etk::String& _configY) :
			  this.data(0,0),
			  this.type(esvg::distance_pixel) {
				set(_configX, _configY);
			};
			/**
			 * Destructor
			 */
			~Dimension();
			
			/**
			 * string cast :
			 */
			operator etk::String() const;
			
			/**
			 * get the current dimention.
			 * @return dimention requested.
			 */
			const Vector2f& getValue() const {
				return this.data;
			}
			/**
			 * @breif get the dimension type
			 * @return the type
			 */
			enum distance getType() const {
				return this.type;
			};
			/**
			 * set the current dimention in requested type
			 * @param _size Dimention to set
			 * @param _type Type of unit requested.
			 */
			void set(const Vector2f& _size, enum distance _type);
			
		public:
			/**
			 * set the current dimention in requested type
			 * @param _config dimension configuration.
			 */
			void set(etk::String _config);
			/**
			 * set the current dimention in requested type
			 * @param _configX dimension X configuration.
			 * @param _configY dimension Y configuration.
			 */
			void set(etk::String _configX, etk::String _configY);
		public:
			/**
			 * get the current dimention in pixel
			 * @param _upperSize Size in pixel of the upper value
			 * @return dimention in Pixel
			 */
			Vector2f getPixel(const Vector2f& _upperSize) const;
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Dimension& operator= (const Dimension& _obj ) {
				if (this!=&_obj) {
					this.data = _obj.this.data;
					this.type = _obj.this.type;
				}
				return *this;
			}
			/*****************************************************
			 *    == operator
			 *****************************************************/
			boolean operator ==  (const Dimension& _obj) const {
				if(    this.data == _obj.this.data
				    && this.type == _obj.this.type) {
					return true;
				}
				return false;
			}
			/*****************************************************
			 *    != operator
			 *****************************************************/
			boolean operator!= (const Dimension& _obj) const {
				if(    this.data != _obj.this.data
				    || this.type != _obj.this.type) {
					return true;
				}
				return false;
			}
	};
	etk::Stream& operator <<(etk::Stream& _os, enum esvg::distance _obj);
	etk::Stream& operator <<(etk::Stream& _os, const esvg::Dimension& _obj);
	/**
	 * in the dimention class we store the data as the more usefull unit (pixel) 
	 * but one case need to be dynamic the %, then when requested in % the register the % value
	 */
	class Dimension1D {
		private:
			float this.data;
			enum distance this.type;
		public:
			/**
			 * Constructor (default :0,0 mode pixel)
			 */
			Dimension1D();
			/**
			 * Constructor
			 * @param _size Requested dimention
			 * @param _type Unit of the Dimention
			 */
			Dimension1D(float _size, enum esvg::distance _type=esvg::distance_pixel);
			/**
			 * Constructor
			 * @param _config dimension configuration.
			 */
			Dimension1D(const etk::String& _config) :
			  this.data(0.0f),
			  this.type(esvg::distance_pixel) {
				set(_config);
			};
			/**
			 * Destructor
			 */
			~Dimension1D();
			
			/**
			 * string cast :
			 */
			operator etk::String() const;
			
			/**
			 * get the current dimention.
			 * @return dimention requested.
			 */
			const float& getValue() const {
				return this.data;
			}
			/**
			 * @breif get the dimension type
			 * @return the type
			 */
			enum distance getType() const {
				return this.type;
			};
			/**
			 * set the current dimention in requested type
			 * @param _size Dimention to set
			 * @param _type Type of unit requested.
			 */
			void set(float _size, enum distance _type);
			
		public:
			/**
			 * set the current dimention in requested type
			 * @param _config dimension configuration.
			 */
			void set(etk::String _config);
		public:
			/**
			 * get the current dimention in pixel
			 * @param _upperSize Size in pixel of the upper value
			 * @return dimention in Pixel
			 */
			float getPixel(float _upperSize) const;
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Dimension1D& operator= (const Dimension1D& _obj ) {
				if (this!=&_obj) {
					this.data = _obj.this.data;
					this.type = _obj.this.type;
				}
				return *this;
			}
			/*****************************************************
			 *    == operator
			 *****************************************************/
			boolean operator ==  (const Dimension1D& _obj) const {
				if(    this.data == _obj.this.data
				    && this.type == _obj.this.type) {
					return true;
				}
				return false;
			}
			/*****************************************************
			 *    != operator
			 *****************************************************/
			boolean operator!= (const Dimension1D& _obj) const {
				if(    this.data != _obj.this.data
				    || this.type != _obj.this.type) {
					return true;
				}
				return false;
			}
	};
	etk::Stream& operator <<(etk::Stream& _os, const esvg::Dimension1D& _obj);
}

;
	enum distance {
		distance_pourcent=0, //!< "%"
		distance_pixel, //!< "px"
		distance_meter, //!< "m"
		distance_centimeter, //!< "cm"
		distance_millimeter, //!< "mm"
		distance_kilometer, //!< "km"
		distance_inch, //!< "in"
		distance_foot, //!< "ft"
		distance_element, //!< "em"
		distance_ex, //!< "ex"
		distance_point, //!< "pt"
		distance_pc //!< "pc"
	}