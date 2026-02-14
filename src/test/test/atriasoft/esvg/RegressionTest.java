package test.atriasoft.esvg;

import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.esvg.render.SvgRenderBuffer;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Tests de non-regression visuels pour ESVG.
 * Compare les images generees avec des images de reference pixel par pixel.
 */
class RegressionTest {
	static final Logger LOGGER = LoggerFactory.getLogger(RegressionTest.class);

	public static final String REFERENCE_PATH = "./testReference/";
	public static final String RESULT_PATH = "./testResult/";

	// Tolerance pour la comparaison des couleurs (0-255)
	// Une petite tolerance est necessaire pour les differences de precision float
	public static final int COLOR_TOLERANCE = 1;

	// Pourcentage maximum de pixels differents autorise
	public static final double MAX_DIFF_PERCENT = 0.0;

	@BeforeAll
	static void setup() {
		// Creer les repertoires si necessaire
		new File(REFERENCE_PATH).mkdirs();
		new File(RESULT_PATH).mkdirs();
	}

	/**
	 * Represente un cas de test SVG
	 */
	record TestCase(String name, String svgData) {}

	/**
	 * Retourne tous les cas de test SVG
	 */
	static List<TestCase> getAllTestCases() {
		List<TestCase> cases = new ArrayList<>();

		// Circle tests
		cases.add(new TestCase("circle_fill", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<circle cx='50' cy='50' r='40' fill='red' />
				</svg>"""));

		cases.add(new TestCase("circle_stroke", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' />
				</svg>"""));

		cases.add(new TestCase("circle_fill_stroke", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<circle cx='50' cy='50' r='40' stroke='green' stroke-width='3' fill='red' />
				</svg>"""));

		// Rectangle tests
		cases.add(new TestCase("rect_fill", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<rect x='10' y='10' width='80' height='60' fill='blue' />
				</svg>"""));

		cases.add(new TestCase("rect_stroke", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<rect x='10' y='10' width='80' height='60' stroke='orange' stroke-width='4' />
				</svg>"""));

		cases.add(new TestCase("rect_rounded", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<rect x='10' y='10' width='80' height='60' rx='10' ry='10' fill='purple' />
				</svg>"""));

		// Ellipse tests
		cases.add(new TestCase("ellipse_fill", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<ellipse cx='50' cy='50' rx='45' ry='25' fill='cyan' />
				</svg>"""));

		// Line tests
		cases.add(new TestCase("line_basic", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<line x1='10' y1='10' x2='90' y2='90' stroke='black' stroke-width='2' />
				</svg>"""));

		// Path tests - Bezier curves
		cases.add(new TestCase("path_bezier_cubic", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<path d='m 50,50 c -12.426,0 -22.5,10.072 -22.5,22.5 0,12.426 10.074,22.5 22.5,22.5 12.428,0 22.5,-10.074 22.5,-22.5 0,-12.427 -10.072,-22.5 -22.5,-22.5 z' fill='red' />
				</svg>"""));

		cases.add(new TestCase("path_bezier_quadratic", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<path d='m 50,50 q -30,1 -20,20 z' fill='red' />
				</svg>"""));

		cases.add(new TestCase("path_smooth_curve", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<path d='m 50,50 s -30,0 -20,20 z' fill='red' />
				</svg>"""));

		// Polygon tests
		cases.add(new TestCase("polygon_triangle", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<polygon points='50,10 90,90 10,90' fill='yellow' stroke='black' stroke-width='2' />
				</svg>"""));

		cases.add(new TestCase("polygon_star", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<polygon points='50,5 61,40 98,40 68,62 79,97 50,75 21,97 32,62 2,40 39,40' fill='gold' />
				</svg>"""));

		// Polyline tests
		cases.add(new TestCase("polyline_basic", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<polyline points='10,90 30,30 50,60 70,20 90,50' fill='none' stroke='red' stroke-width='3' />
				</svg>"""));

		// Gradient tests - Linear
		cases.add(new TestCase("gradient_linear_horizontal", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad1' x1='0%' y1='0%' x2='100%' y2='0%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<ellipse cx='50' cy='50' rx='45' ry='25' fill='url(#grad1)' />
				</svg>"""));

		cases.add(new TestCase("gradient_linear_diagonal", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<linearGradient id='grad2' x1='0%' y1='0%' x2='100%' y2='100%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='50%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<rect x='10' y='10' width='80' height='80' fill='url(#grad2)' />
				</svg>"""));

		// Gradient tests - Radial
		cases.add(new TestCase("gradient_radial", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<defs>
						<radialGradient id='grad3' cx='50%' cy='50%' r='50%'>
							<stop offset='0%' style='stop-color:rgb(255,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
						</radialGradient>
					</defs>
					<circle cx='50' cy='50' r='40' fill='url(#grad3)' />
				</svg>"""));

		// Transform tests
		cases.add(new TestCase("transform_rotate", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<rect x='25' y='25' width='50' height='30' fill='green' transform='rotate(45 50 50)' />
				</svg>"""));

		cases.add(new TestCase("transform_scale", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<rect x='20' y='30' width='30' height='20' fill='blue' transform='scale(1.5 1.5)' />
				</svg>"""));

		cases.add(new TestCase("transform_translate", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<circle cx='20' cy='20' r='15' fill='red' transform='translate(30 30)' />
				</svg>"""));

		// Stroke cap tests
		cases.add(new TestCase("stroke_cap_butt", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<line x1='20' y1='50' x2='80' y2='50' stroke='black' stroke-width='10' stroke-linecap='butt' />
				</svg>"""));

		cases.add(new TestCase("stroke_cap_round", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<line x1='20' y1='50' x2='80' y2='50' stroke='black' stroke-width='10' stroke-linecap='round' />
				</svg>"""));

		cases.add(new TestCase("stroke_cap_square", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<line x1='20' y1='50' x2='80' y2='50' stroke='black' stroke-width='10' stroke-linecap='square' />
				</svg>"""));

		// Stroke join tests
		cases.add(new TestCase("stroke_join_miter", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<polyline points='20,80 50,20 80,80' fill='none' stroke='black' stroke-width='10' stroke-linejoin='miter' />
				</svg>"""));

		cases.add(new TestCase("stroke_join_round", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<polyline points='20,80 50,20 80,80' fill='none' stroke='black' stroke-width='10' stroke-linejoin='round' />
				</svg>"""));

		cases.add(new TestCase("stroke_join_bevel", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<polyline points='20,80 50,20 80,80' fill='none' stroke='black' stroke-width='10' stroke-linejoin='bevel' />
				</svg>"""));

		// Opacity tests
		cases.add(new TestCase("opacity_fill", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<rect x='10' y='10' width='50' height='50' fill='red' />
					<rect x='40' y='40' width='50' height='50' fill='blue' fill-opacity='0.5' />
				</svg>"""));

		// Group tests
		cases.add(new TestCase("group_transform", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<g transform='translate(20,20)'>
						<circle cx='30' cy='30' r='20' fill='red' />
						<rect x='40' y='20' width='30' height='30' fill='blue' />
					</g>
				</svg>"""));

		// Complex path with arc
		cases.add(new TestCase("path_arc", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='100' width='100'>
					<path d='M20,50 a30,30 0 0,1 60,0 a30,30 0 0,1 -60,0' fill='none' stroke='red' stroke-width='3' />
				</svg>"""));

		return cases;
	}

	/**
	 * Genere une image a partir d'un SVG (retourne le buffer float pour comparaison precise)
	 */
	static SvgRenderBuffer renderSvg(final String svgData) {
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(svgData);
		return doc.renderSvgBuffer(null, false);
	}

	/**
	 * Sauvegarde un buffer de rendu au format PNG
	 */
	static void saveImage(final SvgRenderBuffer buffer, final String path) {
		try {
			ImageIO.write(buffer.toBufferedImage(), "png", new File(path));
		} catch (final IOException e) {
			throw new RuntimeException("Failed to store image: " + path, e);
		}
	}

	/**
	 * Charge une image depuis un fichier PNG
	 */
	static BufferedImage loadImage(final String path) throws IOException {
		return ImageIO.read(new File(path));
	}

	/**
	 * Compare deux images pixel par pixel
	 * Compare l'image generee avec l'image de reference chargee depuis PNG
	 * @return Le pourcentage de pixels differents
	 */
	static ComparisonResult compareImages(final SvgRenderBuffer generated, final BufferedImage reference) {
		if (generated == null) {
			return new ComparisonResult(100.0, "Generated image is null");
		}

		if (generated.getWidth() != reference.getWidth() ||
			generated.getHeight() != reference.getHeight()) {
			return new ComparisonResult(100.0,
				String.format("Size mismatch: generated=%dx%d, reference=%dx%d",
					generated.getWidth(), generated.getHeight(),
					reference.getWidth(), reference.getHeight()));
		}

		int totalPixels = generated.getWidth() * generated.getHeight();
		int diffPixels = 0;
		int maxDiff = 0;

		for (int y = 0; y < generated.getHeight(); y++) {
			for (int x = 0; x < generated.getWidth(); x++) {
				// Get generated image pixel - convert float to byte
				int genR = Math.round(generated.getRFloat(x, y) * 255) & 0xFF;
				int genG = Math.round(generated.getGFloat(x, y) * 255) & 0xFF;
				int genB = Math.round(generated.getBFloat(x, y) * 255) & 0xFF;
				int genA = Math.round(generated.getAFloat(x, y) * 255) & 0xFF;

				// Get reference image pixel
				int refRgb = reference.getRGB(x, y);
				int refR = (refRgb >> 16) & 0xFF;
				int refG = (refRgb >> 8) & 0xFF;
				int refB = refRgb & 0xFF;
				int refA = (refRgb >> 24) & 0xFF;

				int diffR = Math.abs(genR - refR);
				int diffG = Math.abs(genG - refG);
				int diffB = Math.abs(genB - refB);
				int diffA = Math.abs(genA - refA);

				int pixelMaxDiff = Math.max(Math.max(diffR, diffG), Math.max(diffB, diffA));
				maxDiff = Math.max(maxDiff, pixelMaxDiff);

				if (diffR > COLOR_TOLERANCE || diffG > COLOR_TOLERANCE ||
					diffB > COLOR_TOLERANCE || diffA > COLOR_TOLERANCE) {
					diffPixels++;
				}
			}
		}

		double diffPercent = (diffPixels * 100.0) / totalPixels;
		return new ComparisonResult(diffPercent,
			String.format("%.2f%% pixels differ (%d/%d), max diff=%d",
				diffPercent, diffPixels, totalPixels, maxDiff));
	}

	/**
	 * Compare deux SvgRenderBuffer directement (pour tests de non-regression apres optimisation)
	 */
	static ComparisonResult compareImages(final SvgRenderBuffer generated, final SvgRenderBuffer reference) {
		if (generated == null || reference == null) {
			return new ComparisonResult(100.0, "Image is null");
		}

		if (generated.getWidth() != reference.getWidth() ||
			generated.getHeight() != reference.getHeight()) {
			return new ComparisonResult(100.0,
				String.format("Size mismatch: generated=%dx%d, reference=%dx%d",
					generated.getWidth(), generated.getHeight(),
					reference.getWidth(), reference.getHeight()));
		}

		int totalPixels = generated.getWidth() * generated.getHeight();
		int diffPixels = 0;
		float maxDiff = 0;

		for (int y = 0; y < generated.getHeight(); y++) {
			for (int x = 0; x < generated.getWidth(); x++) {
				float diffR = Math.abs(generated.getRFloat(x, y) - reference.getRFloat(x, y));
				float diffG = Math.abs(generated.getGFloat(x, y) - reference.getGFloat(x, y));
				float diffB = Math.abs(generated.getBFloat(x, y) - reference.getBFloat(x, y));
				float diffA = Math.abs(generated.getAFloat(x, y) - reference.getAFloat(x, y));

				float pixelMaxDiff = Math.max(Math.max(diffR, diffG), Math.max(diffB, diffA));
				maxDiff = Math.max(maxDiff, pixelMaxDiff);

				// Tolerance of 0.01 for floating point comparison
				if (diffR > 0.01f || diffG > 0.01f || diffB > 0.01f || diffA > 0.01f) {
					diffPixels++;
				}
			}
		}

		double diffPercent = (diffPixels * 100.0) / totalPixels;
		return new ComparisonResult(diffPercent,
			String.format("%.2f%% pixels differ (%d/%d), max diff=%.4f",
				diffPercent, diffPixels, totalPixels, maxDiff));
	}

	record ComparisonResult(double diffPercent, String message) {}

	/**
	 * Test de non-regression principal
	 */
	@Test
	void testAllSvgRendering() throws IOException {
		List<TestCase> testCases = getAllTestCases();
		List<String> failures = new ArrayList<>();
		int generated = 0;
		int compared = 0;
		int passed = 0;

		for (TestCase tc : testCases) {
			String refPath = REFERENCE_PATH + tc.name() + ".png";
			String resultPath = RESULT_PATH + tc.name() + ".png";

			// Generer l'image
			SvgRenderBuffer buffer = renderSvg(tc.svgData());

			if (buffer == null) {
				failures.add(tc.name() + ": Failed to render SVG");
				continue;
			}

			// Sauvegarder le resultat
			saveImage(buffer, resultPath);

			File refFile = new File(refPath);
			if (!refFile.exists()) {
				// Pas d'image de reference, on la cree
				saveImage(buffer, refPath);
				LOGGER.debug("Created reference image: {}", refPath);
				generated++;
			} else {
				// Comparer avec la reference
				compared++;
				BufferedImage reference = loadImage(refPath);
				ComparisonResult result = compareImages(buffer, reference);

				if (result.diffPercent() > MAX_DIFF_PERCENT) {
					failures.add(tc.name() + ": " + result.message());
				} else {
					passed++;
					LOGGER.debug("PASS: {} - {}", tc.name(), result.message());
				}
			}
		}

		// Rapport
		LOGGER.info("=== Regression Test Report ===");
		LOGGER.info("Total test cases: {}", testCases.size());
		LOGGER.info("New references generated: {}", generated);
		LOGGER.info("Compared with references: {}", compared);
		LOGGER.info("Passed: {}", passed);
		LOGGER.info("Failed: {}", failures.size());

		if (!failures.isEmpty()) {
			LOGGER.error("=== Failures ===");
			for (String failure : failures) {
				LOGGER.error(failure);
			}
			Assertions.fail("Regression tests failed:\n" + String.join("\n", failures));
		}
	}

	/**
	 * Test de performance - mesure le temps de rendu
	 */
	@Test
	void testRenderingPerformance() {
		String complexSvg = """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='200' width='200'>
					<defs>
						<linearGradient id='grad1' x1='0%' y1='0%' x2='100%' y2='100%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='50%' style='stop-color:rgb(0,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<circle cx='100' cy='100' r='80' fill='url(#grad1)' stroke='black' stroke-width='2' />
					<rect x='60' y='60' width='80' height='80' fill='yellow' fill-opacity='0.5' transform='rotate(45 100 100)' />
					<path d='M100,20 L120,80 L180,80 L130,120 L150,180 L100,140 L50,180 L70,120 L20,80 L80,80 Z' fill='gold' />
				</svg>""";

		EsvgDocument doc = new EsvgDocument();
		doc.parse(complexSvg);

		// Warmup
		for (int i = 0; i < 3; i++) {
			doc.renderSvgBuffer(null, false);
		}

		// Mesure
		int iterations = 10;
		long startTime = System.nanoTime();

		for (int i = 0; i < iterations; i++) {
			doc.renderSvgBuffer(null, false);
		}

		long endTime = System.nanoTime();
		double avgTimeMs = (endTime - startTime) / 1_000_000.0 / iterations;

		LOGGER.info("=== Performance Test ===");
		LOGGER.info("Average render time: {} ms", String.format("%.2f", avgTimeMs));
		LOGGER.info("Renders per second: {}", String.format("%.1f", 1000.0 / avgTimeMs));
	}

	/**
	 * Test de profilage detaille - identifie les goulots d'etranglement
	 */
	@Test
	void testProfilingDetailedBreakdown() {
		LOGGER.info("=== Profiling Breakdown Test ===");

		// Test 1: Simple circle (forme simple, pas de gradient)
		testProfileShape("circle_simple", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='200' width='200'>
					<circle cx='100' cy='100' r='80' fill='red' />
				</svg>""");

		// Test 2: Circle with stroke
		testProfileShape("circle_stroke", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='200' width='200'>
					<circle cx='100' cy='100' r='80' fill='red' stroke='black' stroke-width='5' />
				</svg>""");

		// Test 3: Circle with linear gradient
		testProfileShape("circle_gradient", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='200' width='200'>
					<defs>
						<linearGradient id='grad1' x1='0%' y1='0%' x2='100%' y2='100%'>
							<stop offset='0%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(0,0,255);stop-opacity:1' />
						</linearGradient>
					</defs>
					<circle cx='100' cy='100' r='80' fill='url(#grad1)' />
				</svg>""");

		// Test 4: Complex path (star)
		testProfileShape("path_star", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='200' width='200'>
					<path d='M100,20 L120,80 L180,80 L130,120 L150,180 L100,140 L50,180 L70,120 L20,80 L80,80 Z' fill='gold' />
				</svg>""");

		// Test 5: Multiple shapes
		testProfileShape("multiple_shapes", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='200' width='200'>
					<circle cx='50' cy='50' r='30' fill='red' />
					<circle cx='150' cy='50' r='30' fill='green' />
					<circle cx='50' cy='150' r='30' fill='blue' />
					<circle cx='150' cy='150' r='30' fill='yellow' />
					<rect x='75' y='75' width='50' height='50' fill='purple' />
				</svg>""");

		// Test 6: Bezier curves
		testProfileShape("bezier_path", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='200' width='200'>
					<path d='M10,80 C40,10 65,10 95,80 S150,150 180,80' stroke='black' stroke-width='2' fill='none' />
					<path d='M10,120 Q50,180 100,120 T180,120' stroke='red' stroke-width='2' fill='none' />
				</svg>""");

		// Test 7: Large image
		testProfileShapeWithSize("large_circle", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='500' width='500'>
					<circle cx='250' cy='250' r='200' fill='red' />
				</svg>""", 500, 500);

		// Test 8: Radial gradient
		testProfileShape("radial_gradient", """
				<?xml version='1.0' encoding='UTF-8' standalone='no'?>
				<svg height='200' width='200'>
					<defs>
						<radialGradient id='grad1' cx='50%' cy='50%' r='50%'>
							<stop offset='0%' style='stop-color:rgb(255,255,0);stop-opacity:1' />
							<stop offset='100%' style='stop-color:rgb(255,0,0);stop-opacity:1' />
						</radialGradient>
					</defs>
					<circle cx='100' cy='100' r='80' fill='url(#grad1)' />
				</svg>""");
	}

	private void testProfileShape(final String name, final String svgData) {
		testProfileShapeWithSize(name, svgData, -1, -1);
	}

	private void testProfileShapeWithSize(final String name, final String svgData, final int width, final int height) {
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(svgData);

		// Warmup
		for (int i = 0; i < 5; i++) {
			if (width > 0) {
				doc.renderSvgBuffer(new org.atriasoft.etk.math.Vector2i(width, height), false);
			} else {
				doc.renderSvgBuffer(null, false);
			}
		}

		// Mesure
		final int iterations = 20;
		final long startTime = System.nanoTime();

		for (int i = 0; i < iterations; i++) {
			if (width > 0) {
				doc.renderSvgBuffer(new org.atriasoft.etk.math.Vector2i(width, height), false);
			} else {
				doc.renderSvgBuffer(null, false);
			}
		}

		final long endTime = System.nanoTime();
		final double avgTimeMs = (endTime - startTime) / 1_000_000.0 / iterations;

		LOGGER.info(String.format("  %-20s: %7.2f ms", name, avgTimeMs));
	}
}
