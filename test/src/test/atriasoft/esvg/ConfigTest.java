package test.atriasoft.esvg;

import java.awt.image.BufferedImage;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.esvg.internal.Log;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.Uri;
import org.atriasoft.etk.math.Vector2i;

import com.pngencoder.PngEncoder;

public class ConfigTest {
	public static final String BASE_PATH = "./testResult/";//"~/dev/workspace-game/atriasoft/esvg/";
	public static final boolean VISUAL_DEBUG = true;
	
	public static void generateAnImage(final EsvgDocument doc, final Uri uri) {
		Color[][] data = doc.renderImageFloatRGBA(null, ConfigTest.VISUAL_DEBUG);
		if (data.length == 0) {
			Log.critical("No data generated ...");
		}
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
	
	public static void generateAnImage(final Weight weight, final Uri uri) {
		BufferedImage bufferedImage = new BufferedImage(weight.getWidth() + 2, weight.getHeight() + 2, BufferedImage.TYPE_INT_ARGB);
		for (int yyy = 0; yyy < weight.getHeight(); yyy++) {
			for (int xxx = 0; xxx < weight.getWidth(); xxx++) {
				float elem = weight.get(new Vector2i(xxx, yyy));
				int tmpColor = (0xFF << 24) + ((int) (elem * 255.0f) << 16) + ((int) (elem * 255.0f) << 8) + ((int) (elem * 255.0f));
				bufferedImage.setRGB(xxx + 1, 1 + weight.getHeight() - 1 - yyy, tmpColor);
			}
		}
		for (int yyy = 0; yyy < weight.getHeight() + 2; yyy++) {
			bufferedImage.setRGB(0, yyy, 0xFFFF0000);
			bufferedImage.setRGB(weight.getWidth() + 1, yyy, 0xFFFF0000);
		}
		for (int xxx = 0; xxx < weight.getWidth() + 2; xxx++) {
			bufferedImage.setRGB(xxx, 0, 0xFFFF0000);
			bufferedImage.setRGB(xxx, weight.getHeight() + 1, 0xFFFF0000);
		}
		Log.warning("Save file in " + uri.getPath());
		byte[] outElem = new PngEncoder().withBufferedImage(bufferedImage).withCompressionLevel(9).toBytes();
		Log.warning("outsize = " + outElem.length);
		new PngEncoder().withBufferedImage(bufferedImage).withCompressionLevel(9).toFile(uri.getPath());
	}
	
	private ConfigTest() {}
}
