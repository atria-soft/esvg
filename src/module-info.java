/** Basic module interface.
 *
 * @author Edouard DUPIN */

open module org.atriasoft.esvg {
	exports org.atriasoft.esvg;
	exports org.atriasoft.esvg.font;
	exports org.atriasoft.esvg.render;
	
	requires transitive io.scenarium.logger;
	requires transitive org.atriasoft.etk;
	requires transitive org.atriasoft.exml;
	requires com.pngencoder;
	requires java.desktop;
}
