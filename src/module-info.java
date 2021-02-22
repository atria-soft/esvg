/** Basic module interface.
 *
 * @author Edouard DUPIN */

open module org.atriasoft.esvg {
	exports org.atriasoft.esvg;
	exports org.atriasoft.esvg.render;
	
	requires transitive io.scenarium.logger;
}
