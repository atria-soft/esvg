/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ESVG_DIMENSION_H__
#define __ESVG_DIMENSION_H__

#include <etk/types.h>
#include <etk/types.h>
#include <etk/math/Vector2D.h>

namespace esvg {
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
	};
	/**
	 * @brief in the dimention class we store the data as the more usefull unit (pixel) 
	 * but one case need to be dynamic the %, then when requested in % the register the % value
	 */
	class Dimension {
		private:
			vec2 m_data;
			enum distance m_type;
		public:
			/**
			 * @brief Constructor (default :0,0 mode pixel)
			 */
			Dimension();
			/**
			 * @brief Constructor
			 * @param[in] _size Requested dimention
			 * @param[in] _type Unit of the Dimention
			 */
			Dimension(const vec2& _size, enum esvg::distance _type=esvg::distance_pixel);
			/**
			 * @brief Constructor
			 * @param[in] _config dimension configuration.
			 */
			Dimension(const std::string& _config) :
			  m_data(0,0),
			  m_type(esvg::distance_pixel) {
				set(_config);
			};
			/**
			 * @brief Constructor
			 * @param[in] _configX dimension X configuration.
			 * @param[in] _configY dimension Y configuration.
			 */
			Dimension(const std::string& _configX, const std::string& _configY) :
			  m_data(0,0),
			  m_type(esvg::distance_pixel) {
				set(_configX, _configY);
			};
			/**
			 * @brief Destructor
			 */
			~Dimension();
			
			/**
			 * @brief string cast :
			 */
			operator std::string() const;
			
			/**
			 * @brief get the current dimention.
			 * @return dimention requested.
			 */
			const vec2& getValue() const {
				return m_data;
			}
			/**
			 * @breif get the dimension type
			 * @return the type
			 */
			enum distance getType() const {
				return m_type;
			};
			/**
			 * @brief set the current dimention in requested type
			 * @param[in] _size Dimention to set
			 * @param[in] _type Type of unit requested.
			 */
			void set(const vec2& _size, enum distance _type);
			
		public:
			/**
			 * @brief set the current dimention in requested type
			 * @param[in] _config dimension configuration.
			 */
			void set(std::string _config);
			/**
			 * @brief set the current dimention in requested type
			 * @param[in] _configX dimension X configuration.
			 * @param[in] _configY dimension Y configuration.
			 */
			void set(std::string _configX, std::string _configY);
		public:
			/**
			 * @brief get the current dimention in pixel
			 * @param[in] _upperSize Size in pixel of the upper value
			 * @return dimention in Pixel
			 */
			vec2 getPixel(const vec2& _upperSize) const;
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Dimension& operator= (const Dimension& _obj ) {
				if (this!=&_obj) {
					m_data = _obj.m_data;
					m_type = _obj.m_type;
				}
				return *this;
			}
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator ==  (const Dimension& _obj) const {
				if(    m_data == _obj.m_data
				    && m_type == _obj.m_type) {
					return true;
				}
				return false;
			}
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const Dimension& _obj) const {
				if(    m_data != _obj.m_data
				    || m_type != _obj.m_type) {
					return true;
				}
				return false;
			}
	};
	std::ostream& operator <<(std::ostream& _os, enum esvg::distance _obj);
	std::ostream& operator <<(std::ostream& _os, const esvg::Dimension& _obj);
	/**
	 * @brief in the dimention class we store the data as the more usefull unit (pixel) 
	 * but one case need to be dynamic the %, then when requested in % the register the % value
	 */
	class Dimension1D {
		private:
			float m_data;
			enum distance m_type;
		public:
			/**
			 * @brief Constructor (default :0,0 mode pixel)
			 */
			Dimension1D();
			/**
			 * @brief Constructor
			 * @param[in] _size Requested dimention
			 * @param[in] _type Unit of the Dimention
			 */
			Dimension1D(float _size, enum esvg::distance _type=esvg::distance_pixel);
			/**
			 * @brief Constructor
			 * @param[in] _config dimension configuration.
			 */
			Dimension1D(const std::string& _config) :
			  m_data(0.0f),
			  m_type(esvg::distance_pixel) {
				set(_config);
			};
			/**
			 * @brief Destructor
			 */
			~Dimension1D();
			
			/**
			 * @brief string cast :
			 */
			operator std::string() const;
			
			/**
			 * @brief get the current dimention.
			 * @return dimention requested.
			 */
			const float& getValue() const {
				return m_data;
			}
			/**
			 * @breif get the dimension type
			 * @return the type
			 */
			enum distance getType() const {
				return m_type;
			};
			/**
			 * @brief set the current dimention in requested type
			 * @param[in] _size Dimention to set
			 * @param[in] _type Type of unit requested.
			 */
			void set(float _size, enum distance _type);
			
		public:
			/**
			 * @brief set the current dimention in requested type
			 * @param[in] _config dimension configuration.
			 */
			void set(std::string _config);
		public:
			/**
			 * @brief get the current dimention in pixel
			 * @param[in] _upperSize Size in pixel of the upper value
			 * @return dimention in Pixel
			 */
			float getPixel(float _upperSize) const;
			/*****************************************************
			 *    = assigment
			 *****************************************************/
			const Dimension1D& operator= (const Dimension1D& _obj ) {
				if (this!=&_obj) {
					m_data = _obj.m_data;
					m_type = _obj.m_type;
				}
				return *this;
			}
			/*****************************************************
			 *    == operator
			 *****************************************************/
			bool operator ==  (const Dimension1D& _obj) const {
				if(    m_data == _obj.m_data
				    && m_type == _obj.m_type) {
					return true;
				}
				return false;
			}
			/*****************************************************
			 *    != operator
			 *****************************************************/
			bool operator!= (const Dimension1D& _obj) const {
				if(    m_data != _obj.m_data
				    || m_type != _obj.m_type) {
					return true;
				}
				return false;
			}
	};
	std::ostream& operator <<(std::ostream& _os, const esvg::Dimension1D& _obj);
};

#endif

