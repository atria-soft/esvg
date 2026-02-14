package test.atriasoft.esvg;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.esvg.render.SvgRenderBuffer;
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
		final BufferedImage data = doc.renderImage(null, ConfigTest.VISUAL_DEBUG);
		if (data == null) {
			LOGGER.error("No data generated ...");
		}
		LOGGER.debug("Save file in {}", uri.getPath());
		try {
			ImageIO.write(data, "png", new File(uri.getPath()));
		} catch (final IOException e) {
			LOGGER.error("Failed to store image: {}", uri.getPath(), e);
		}
	}

	public static void generateAnImage(final Weight weight, final Uri uri) {
		final SvgRenderBuffer buffer = new SvgRenderBuffer(weight.getWidth() + 2, weight.getHeight() + 2);
		for (int yyy = 0; yyy < weight.getHeight(); yyy++) {
			for (int xxx = 0; xxx < weight.getWidth(); xxx++) {
				final float elem = weight.get(new Vector2i(xxx, yyy));
				buffer.setColorFloat(xxx, yyy, 1.0f, 1.0f, 1.0f, elem);
			}
		}
		for (int yyy = 0; yyy < weight.getHeight() + 2; yyy++) {
			buffer.setColor(0, yyy, Color.ORANGE);
			buffer.setColor(weight.getWidth() + 1, yyy, Color.ORANGE);
		}
		for (int xxx = 0; xxx < weight.getWidth() + 2; xxx++) {
			buffer.setColor(xxx, 0, Color.ORANGE);
			buffer.setColor(xxx, weight.getHeight() + 1, Color.ORANGE);
		}
		LOGGER.debug("Save file in {}", uri.getPath());
		try {
			ImageIO.write(buffer.toBufferedImage(), "png", new File(uri.getPath()));
		} catch (final IOException e) {
			LOGGER.error("Failed to store image: {}", uri.getPath(), e);
		}
	}

	private ConfigTest() {}
}
