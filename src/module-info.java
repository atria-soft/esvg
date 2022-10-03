/** Basic module interface.
 *
 * @author Edouard DUPIN */

open module org.atriasoft.esvg {
	exports org.atriasoft.esvg;
	exports org.atriasoft.esvg.font;
	exports org.atriasoft.esvg.render;
	
	requires transitive org.atriasoft.reggol;
	requires transitive org.atriasoft.etk;
	requires transitive org.atriasoft.exml;
	requires org.atriasoft.pngencoder;
	requires java.desktop;
	requires org.atriasoft.egami;
}
