package test.atriasoft.esvg;

import java.awt.image.BufferedImage;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.esvg.internal.Log;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.Uri;

import com.pngencoder.PngEncoder;

public class ConfigTest {
	public static final String BASE_PATH = "./";//"~/dev/workspace-game/atriasoft/esvg/";
	public static final boolean VISUAL_DEBUG = true;
	
	public static void generateAnImage(final EsvgDocument doc, final Uri uri) {
		Color[][] data = doc.renderImageFloatRGBA(null, ConfigTest.VISUAL_DEBUG);
		BufferedImage bufferedImage = new BufferedImage(data[0].length, data.length, BufferedImage.TYPE_INT_ARGB);
		for (int yyy = 0; yyy < data.length; yyy++) {
			for (int xxx = 0; xxx < data[yyy].length; xxx++) {
				Color elem = data[yyy][xxx];
				int tmpColor = ((int) (elem.a() * 255.0f) << 24) + ((int) (elem.r() * 255.0f) << 16) + ((int) (elem.g() * 255.0f) << 8) + ((int) (elem.b() * 255.0f));
				bufferedImage.setRGB(xxx, yyy, tmpColor);
			}
		}
		Log.warning("Save file in " + uri.getPath());
		byte[] outElem = new PngEncoder().withBufferedImage(bufferedImage).withCompressionLevel(9).toBytes();
		Log.warning("outsize = " + outElem.length);
		new PngEncoder().withBufferedImage(bufferedImage).withCompressionLevel(9).toFile(uri.getPath());
	}
	
	private ConfigTest() {}
}
