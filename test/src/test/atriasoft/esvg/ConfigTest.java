package test.atriasoft.esvg;

import org.atriasoft.egami.ImageFloatRGBA;
import org.atriasoft.egami.Image;
import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.esvg.internal.Log;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.Uri;
import org.atriasoft.etk.math.Vector2i;

import org.atriasoft.pngencoder.PngEncoder;

public class ConfigTest {
	public static final String BASE_PATH = "./testResult/";//"~/dev/workspace-game/atriasoft/esvg/";
	public static final boolean VISUAL_DEBUG = true;
	
	public static void generateAnImage(final EsvgDocument doc, final Uri uri) {
		Image data = doc.renderImageFloatRGBA(null, ConfigTest.VISUAL_DEBUG);
		if (data == null) {
			Log.critical("No data generated ...");
		}
		Log.warning("Save file in " + uri.getPath());
		byte[] outElem = new PngEncoder().withBufferedImage(data).withCompressionLevel(9).toBytes();
		Log.warning("outsize = " + outElem.length);
		new PngEncoder().withBufferedImage(data).withCompressionLevel(9).toFile(uri.getPath());
	}
	
	public static void generateAnImage(final Weight weight, final Uri uri) {
		ImageFloatRGBA image = new ImageFloatRGBA(weight.getWidth() + 2, weight.getHeight() + 2);
		for (int yyy = 0; yyy < weight.getHeight(); yyy++) {
			for (int xxx = 0; xxx < weight.getWidth(); xxx++) {
				float elem = weight.get(new Vector2i(xxx, yyy));
				image.setColorFloat(xxx, yyy, 1.0f, 1.0f, 1.0f, elem);
			}
		}
		for (int yyy = 0; yyy < weight.getHeight() + 2; yyy++) {
			image.setColor(0, yyy, Color.ORANGE);
			image.setColor(weight.getWidth() + 1, yyy, Color.ORANGE);
		}
		for (int xxx = 0; xxx < weight.getWidth() + 2; xxx++) {
			image.setColor(xxx, 0, Color.ORANGE);
			image.setColor(xxx, weight.getHeight() + 1, Color.ORANGE);
		}
		Log.warning("Save file in " + uri.getPath());
		byte[] outElem = new PngEncoder().withBufferedImage(image).withCompressionLevel(9).toBytes();
		Log.warning("outsize = " + outElem.length);
		new PngEncoder().withBufferedImage(image).withCompressionLevel(9).toFile(uri.getPath());
	}
	
	private ConfigTest() {}
}
