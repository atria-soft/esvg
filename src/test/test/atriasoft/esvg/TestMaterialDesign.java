package test.atriasoft.esvg;

import org.atriasoft.esvg.Esvg;
import org.atriasoft.esvg.EsvgDocument;
import org.atriasoft.etk.Uri;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class TestMaterialDesign {
	@Test
	public void testMDCancel() {
		Esvg.init();
		//@formatter:off
		final String data = """
				<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
					<title>cancel</title>
					<path d="M12 2C17.5 2 22 6.5 22 12S17.5 22 12 22 2 17.5 2 12 6.5 2 12 2M12 4C10.1 4 8.4 4.6 7.1 5.7L18.3 16.9C19.3 15.5 20 13.8 20 12C20 7.6 16.4 4 12 4M16.9 18.3L5.7 7.1C4.6 8.4 4 10.1 4 12C4 16.4 7.6 20 12 20C13.9 20 15.6 19.4 16.9 18.3Z" />
				</svg>
				""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "testMDCancel.png"));
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "testMDCancel.svg"), data.replace("'", "\"")));
	}
	
	@Test
	public void testMDAccountSupervisorCircle() {
		Esvg.init();
		//@formatter:off
		final String data = """
				<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
					<title>account-supervisor-circle</title>
					<path d="M12,2C6.47,2 2,6.5 2,12A10,10 0 0,0 12,22A10,10 0 0,0 22,12A10,10 0 0,0 12,2M15.6,8.34C16.67,8.34 17.53,9.2 17.53,10.27C17.53,11.34 16.67,12.2 15.6,12.2A1.93,1.93 0 0,1 13.67,10.27C13.66,9.2 14.53,8.34 15.6,8.34M9.6,6.76C10.9,6.76 11.96,7.82 11.96,9.12C11.96,10.42 10.9,11.5 9.6,11.5C8.3,11.5 7.24,10.42 7.24,9.12C7.24,7.81 8.29,6.76 9.6,6.76M9.6,15.89V19.64C7.2,18.89 5.3,17.04 4.46,14.68C5.5,13.56 8.13,13 9.6,13C10.13,13 10.8,13.07 11.5,13.21C9.86,14.08 9.6,15.23 9.6,15.89M12,20C11.72,20 11.46,20 11.2,19.96V15.89C11.2,14.47 14.14,13.76 15.6,13.76C16.67,13.76 18.5,14.15 19.44,14.91C18.27,17.88 15.38,20 12,20Z" />
				</svg>
				""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "testMDAccountSupervisorCircle.png"));
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "testMDAccountSupervisorCircle.svg"), data.replace("'", "\"")));
	}
	
	@Test
	public void testMDOpenInApp() {
		Esvg.init();
		//@formatter:off
		final String data = """
				<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
					<title>open-in-app</title>
					<path d="M12,10L8,14H11V20H13V14H16M19,4H5C3.89,4 3,4.9 3,6V18A2,2 0 0,0 5,20H9V18H5V8H19V18H15V20H19A2,2 0 0,0 21,18V6A2,2 0 0,0 19,4Z" />
				</svg>
				""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "testMDOpenInApp.png"));
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "testMDOpenInApp.svg"), data.replace("'", "\"")));
	}
	
	@Test
	public void testMDAccountSupervisorCircleDebug() {
		Esvg.init();
		// Décomposition du path AccountSupervisorCircle en sous-chemins colorés
		//@formatter:off
		final String data = """
				<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
					<title>account-supervisor-circle-debug</title>
					<!-- Path 1: Cercle extérieur (rouge) -->
					<path fill="#FF0000" d="M12,2C6.47,2 2,6.5 2,12A10,10 0 0,0 12,22A10,10 0 0,0 22,12A10,10 0 0,0 12,2Z" />
					<!-- Path 3: Grande tête gauche (bleu) -->
					<path fill="#0000FF" d="M9.6,6.76C10.9,6.76 11.96,7.82 11.96,9.12C11.96,10.42 10.9,11.5 9.6,11.5C8.3,11.5 7.24,10.42 7.24,9.12C7.24,7.81 8.29,6.76 9.6,6.76Z" />
					<!-- Path 2: Petite tête droite (vert) -->
					<path fill="#00FF00" d="M15.6,8.34C16.67,8.34 17.53,9.2 17.53,10.27C17.53,11.34 16.67,12.2 15.6,12.2A1.93,1.93 0 0,1 13.67,10.27C13.66,9.2 14.53,8.34 15.6,8.34Z" />
					<!-- Path 4: Corps gauche (jaune) -->
					<path fill="#FFFF00" d="M9.6,15.89V19.64C7.2,18.89 5.3,17.04 4.46,14.68C5.5,13.56 8.13,13 9.6,13C10.13,13 10.8,13.07 11.5,13.21C9.86,14.08 9.6,15.23 9.6,15.89Z" />
					<!-- Path 5: Corps droit (magenta) -->
					<path fill="#FF00FF" d="M12,20C11.72,20 11.46,20 11.2,19.96V15.89C11.2,14.47 14.14,13.76 15.6,13.76C16.67,13.76 18.5,14.15 19.44,14.91C18.27,17.88 15.38,20 12,20Z" />
				</svg>
				""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "testMDAccountSupervisorCircleDebug.png"));
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(
				new Uri(ConfigTest.BASE_PATH + "testMDAccountSupervisorCircleDebug.svg"), data.replace("'", "\"")));
	}
	
	@Test
	public void testParsingValidation() {
		Esvg.init();
		// Test simple avec un cercle fait d'arcs
		final String pathData = "M12,2C6.47,2 2,6.5 2,12A10,10 0 0,0 12,22A10,10 0 0,0 22,12A10,10 0 0,0 12,2Z";
		
		// Parse le path
		final org.atriasoft.esvg.render.PathModel pathModel = org.atriasoft.esvg.Path.createPathModel(pathData);
		
		// Afficher les éléments parsés
		System.out.println("=== Path parsing validation ===");
		System.out.println("Original: " + pathData);
		System.out.println("Parsed elements:");
		final StringBuilder regenerated = new StringBuilder();
		for (final org.atriasoft.esvg.render.Element elem : pathModel.listElement) {
			System.out.println("  " + elem.toString());
			// Régénérer le path SVG à partir des éléments parsés
			regenerated.append(elementToSvgPath(elem));
		}
		System.out.println("Regenerated: " + regenerated.toString());
		System.out.println("=== End validation ===");
	}
	
	@Test
	public void testArcPointGeneration() {
		Esvg.init();
		// Test avec un seul arc simple : quart de cercle de rayon 10
		// De (2,12) à (12,22) avec rayon (10,10)
		final String pathData = "M2,12 A10,10 0 0,0 12,22";
		
		System.out.println("=== Arc point generation test ===");
		System.out.println("Path: " + pathData);
		
		// Parse et génère les points
		final org.atriasoft.esvg.render.PathModel pathModel = org.atriasoft.esvg.Path.createPathModel(pathData);
		
		// Afficher les éléments parsés
		System.out.println("Parsed elements:");
		for (final org.atriasoft.esvg.render.Element elem : pathModel.listElement) {
			System.out.println("  " + elem.toString());
		}
		
		// Générer les points (level=0, recurtionMax=10, threshold=0.25)
		final org.atriasoft.esvg.render.PointList pointList = pathModel.generateListPoints(0, 10, 0.25f);
		
		// Collecter tous les points dans une liste plate
		final java.util.List<org.atriasoft.esvg.render.Point> allPoints = new java.util.ArrayList<>();
		for (final java.util.List<org.atriasoft.esvg.render.Point> subList : pointList.data) {
			allPoints.addAll(subList);
		}
		
		System.out.println(
				"\nGenerated points (" + allPoints.size() + " total, " + pointList.data.size() + " sublists):");
		int count = 0;
		for (final org.atriasoft.esvg.render.Point pt : allPoints) {
			System.out.println("  [" + count + "] " + pt.pos + " type=" + pt.type);
			count++;
			if (count > 30) {
				System.out.println("  ... (truncated)");
				break;
			}
		}
		
		// Vérifier que le premier point est proche de (2,12) et le dernier de (12,22)
		if (!allPoints.isEmpty()) {
			final org.atriasoft.etk.math.Vector2f first = allPoints.get(0).pos;
			final org.atriasoft.etk.math.Vector2f last = allPoints.get(allPoints.size() - 1).pos;
			System.out.println("\nFirst point: " + first + " (expected: ~(2,12))");
			System.out.println("Last point: " + last + " (expected: ~(12,22))");
			
			// Le centre du cercle devrait être à (12,12)
			// Vérifier que les points sont à distance ~10 du centre
			System.out.println("\nDistance from center (12,12):");
			final org.atriasoft.etk.math.Vector2f center = new org.atriasoft.etk.math.Vector2f(12, 12);
			for (int i = 0; i < Math.min(allPoints.size(), 10); i++) {
				final org.atriasoft.etk.math.Vector2f p = allPoints.get(i).pos;
				final float dist = (float) Math.sqrt(Math.pow(p.x() - center.x(), 2) + Math.pow(p.y() - center.y(), 2));
				System.out.println("  [" + i + "] pos=" + p + " dist=" + dist + " (expected: ~10)");
			}
		}
		
		System.out.println("=== End arc test ===");
	}
	
	private String elementToSvgPath(final org.atriasoft.esvg.render.Element elem) {
		final String cmd;
		return switch (elem.getType()) {
			case MOVE_TO -> {
				cmd = elem.getRelative() ? "m" : "M";
				yield cmd + elem.getPos().x() + "," + elem.getPos().y();
			}
			case LINE_TO -> {
				cmd = elem.getRelative() ? "l" : "L";
				yield cmd + elem.getPos().x() + "," + elem.getPos().y();
			}
			case LINE_TO_H -> {
				cmd = elem.getRelative() ? "h" : "H";
				yield cmd + elem.getPos().x();
			}
			case LINE_TO_V -> {
				cmd = elem.getRelative() ? "v" : "V";
				yield cmd + elem.getPos().y();
			}
			case CURVE_TO -> {
				cmd = elem.getRelative() ? "c" : "C";
				yield cmd + elem.getPos1().x() + "," + elem.getPos1().y() + " " + elem.getPos2().x() + ","
						+ elem.getPos2().y() + " " + elem.getPos().x() + "," + elem.getPos().y();
			}
			case SMOOTH_CURVE_TO -> {
				cmd = elem.getRelative() ? "s" : "S";
				yield cmd + elem.getPos2().x() + "," + elem.getPos2().y() + " " + elem.getPos().x() + ","
						+ elem.getPos().y();
			}
			case ELLIPTIC -> {
				final org.atriasoft.esvg.render.ElementElliptic arc = (org.atriasoft.esvg.render.ElementElliptic) elem;
				cmd = elem.getRelative() ? "a" : "A";
				yield cmd + arc.getPos1().x() + "," + arc.getPos1().y() + " " + arc.angle + " "
						+ (arc.largeArcFlag ? "1" : "0") + "," + (arc.sweepFlag ? "1" : "0") + " " + arc.getPos().x()
						+ "," + arc.getPos().y();
			}
			case STOP -> "Z";
			default -> "?" + elem.getType();
		};
	}
	
	@Test
	public void testFullCircleArcs() {
		Esvg.init();
		// Le cercle complet du debug: M12,2 C6.47,2 2,6.5 2,12 A10,10 0 0,0 12,22 A10,10 0 0,0 22,12 A10,10 0 0,0 12,2 Z
		// Centre du cercle: (12, 12), rayon: 10
		final String pathData = "M12,2C6.47,2 2,6.5 2,12A10,10 0 0,0 12,22A10,10 0 0,0 22,12A10,10 0 0,0 12,2Z";
		
		System.out.println("=== Full circle arc test ===");
		System.out.println("Path: " + pathData);
		
		final org.atriasoft.esvg.render.PathModel pathModel = org.atriasoft.esvg.Path.createPathModel(pathData);
		
		System.out.println("Parsed elements:");
		for (final org.atriasoft.esvg.render.Element elem : pathModel.listElement) {
			System.out.println("  " + elem.toString());
		}
		
		final org.atriasoft.esvg.render.PointList pointList = pathModel.generateListPoints(0, 10, 0.25f);
		
		final java.util.List<org.atriasoft.esvg.render.Point> allPoints = new java.util.ArrayList<>();
		for (final java.util.List<org.atriasoft.esvg.render.Point> subList : pointList.data) {
			allPoints.addAll(subList);
		}
		
		System.out.println("\nGenerated " + allPoints.size() + " points:");
		final org.atriasoft.etk.math.Vector2f center = new org.atriasoft.etk.math.Vector2f(12, 12);
		
		// Afficher tous les points avec leur distance au centre
		for (int i = 0; i < allPoints.size(); i++) {
			final org.atriasoft.etk.math.Vector2f p = allPoints.get(i).pos;
			final float dist = (float) Math.sqrt(Math.pow(p.x() - center.x(), 2) + Math.pow(p.y() - center.y(), 2));
			final String status = (dist < 9.0f || dist > 11.0f) ? " *** PROBLEM ***" : "";
			System.out.println("  [" + i + "] pos=" + p + " dist=" + String.format("%.2f", dist) + status);
		}
		
		// Identifier les points problématiques (distance != ~10)
		System.out.println("\nPoints with distance != ~10:");
		int problemCount = 0;
		for (int i = 0; i < allPoints.size(); i++) {
			final org.atriasoft.etk.math.Vector2f p = allPoints.get(i).pos;
			final float dist = (float) Math.sqrt(Math.pow(p.x() - center.x(), 2) + Math.pow(p.y() - center.y(), 2));
			if (dist < 9.0f || dist > 11.0f) {
				System.out.println("  [" + i + "] pos=" + p + " dist=" + String.format("%.2f", dist) + " type="
						+ allPoints.get(i).type);
				problemCount++;
			}
		}
		System.out.println("Total problems: " + problemCount + " / " + allPoints.size());
		System.out.println("=== End full circle test ===");
	}
	
	@Test
	public void testYellowBodyPath() {
		Esvg.init();
		// Corps gauche jaune du personnage
		final String pathData = "M9.6,15.89V19.64C7.2,18.89 5.3,17.04 4.46,14.68C5.5,13.56 8.13,13 9.6,13C10.13,13 10.8,13.07 11.5,13.21C9.86,14.08 9.6,15.23 9.6,15.89Z";

		System.out.println("=== Yellow body path test ===");
		System.out.println("Path: " + pathData);

		final org.atriasoft.esvg.render.PathModel pathModel = org.atriasoft.esvg.Path.createPathModel(pathData);

		System.out.println("Parsed elements:");
		for (final org.atriasoft.esvg.render.Element elem : pathModel.listElement) {
			System.out.println("  " + elem.toString());
		}

		final org.atriasoft.esvg.render.PointList pointList = pathModel.generateListPoints(0, 10, 0.25f);

		System.out.println("\nGenerated sublists: " + pointList.data.size());
		int totalPoints = 0;
		for (int s = 0; s < pointList.data.size(); s++) {
			final java.util.List<org.atriasoft.esvg.render.Point> subList = pointList.data.get(s);
			System.out.println("Sublist " + s + " (" + subList.size() + " points):");
			for (int i = 0; i < subList.size(); i++) {
				final org.atriasoft.esvg.render.Point pt = subList.get(i);
				System.out.println("  [" + i + "] pos=" + pt.pos + " type=" + pt.type);
			}
			totalPoints += subList.size();
		}
		System.out.println("Total points: " + totalPoints);
		System.out.println("=== End yellow body test ===");
	}

	@Test
	public void testCheckBox() {
		Esvg.init();
		//@formatter:off
		final String data = """
				<svg xmlns="http://www.w3.org/2000/svg"
			         width="64"
			         height="64">
					<path d="M 3.0075839,31.00325 8.9447454,26.55688 21.989166,46.327194 56.019873,4.9985448 60.997388,9.9916825 22.023835,59.71831 Z"/>
				</svg>
				""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "testCheckBox.png"));
		Assertions.assertDoesNotThrow(
				() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "testCheckBox.svg"), data.replace("'", "\"")));
	}

	@Test
	public void testPropertyScanLineFail() {
		Esvg.init();
		//@formatter:off
		final String data = """
				<svg
				   width="32"
				   height="32">
				  <rect
				     x="16.79899"
				     y="-3.5857863"
				     width="6"
				     height="10"
				     rx="1"
				     transform="rotate(45)"
				     style="fill:#FFFFFF;fill-opacity:1"
				     id="rect5" />
				</svg>
				""";
		//@formatter:on
		final EsvgDocument doc = new EsvgDocument();
		doc.parse(data);
		ConfigTest.generateAnImage(doc, new Uri(ConfigTest.BASE_PATH + "testPropertyScanLineFail.png"));
		Assertions.assertDoesNotThrow(() -> Uri.writeAll(new Uri(ConfigTest.BASE_PATH + "testPropertyScanLineFail.svg"),
				data.replace("'", "\"")));
	}

}
