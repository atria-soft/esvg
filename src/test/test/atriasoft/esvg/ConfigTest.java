package test.atriasoft.esvg;

import java.io.IOException;
import java.nio.file.Path;

import org.atriasoft.egami.Image;
import org.atriasoft.egami.ImageFloatRGBA;
import org.atriasoft.egami.ToolImage;
import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.esvg.render.Weight;
import org.atriasoft.etk.Color;
import org.atriasoft.etk.Uri;
import org.atriasoft.etk.math.Vector2i;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ConfigTest {
	static final Logger LOGGER = LoggerFactory.getLogger(ConfigTest.class);
	public static final String BASE_PATH = "./testResult/";//"~/dev/workspace-game/atriasoft/esvg/";
	public static final boolean VISUAL_DEBUG = true;

	public static void generateAnImage(final EsvgDocument doc, final Uri uri) {
		final Image data = doc.renderImageFloatRGBA(null, ConfigTest.VISUAL_DEBUG);
		if (data == null) {
			LOGGER.error("No data generated ...");
		}
		LOGGER.debug("Save file in {}", uri.getPath());
		try {
			ToolImage.storeImage(Path.of(uri.getPath()), data);
		} catch (final IOException e) {
			LOGGER.error("Failed to store image: {}", uri.getPath(), e);
		}
	}

	public static void generateAnImage(final Weight weight, final Uri uri) {
		final ImageFloatRGBA image = new ImageFloatRGBA(weight.getWidth() + 2, weight.getHeight() + 2);
		for (int yyy = 0; yyy < weight.getHeight(); yyy++) {
			for (int xxx = 0; xxx < weight.getWidth(); xxx++) {
				final float elem = weight.get(new Vector2i(xxx, yyy));
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
		LOGGER.debug("Save file in {}", uri.getPath());
		try {
			ToolImage.storeImage(Path.of(uri.getPath()), image);
		} catch (final IOException e) {
			LOGGER.error("Failed to store image: {}", uri.getPath(), e);
		}
	}

	private ConfigTest() {}
}
