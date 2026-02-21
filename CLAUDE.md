# esvg — Claude Code Configuration

## What is esvg?

SVG font library for Java. Loads SVG font files, extracts glyphs/metrics/kerning, and rasterizes text to grayscale bitmaps. Used by `ewol` for text rendering.

## Architecture

### Package structure

```
org.atriasoft.esvg/
    Esvg.java              Module init — registers "esvg" resource library + bundled fonts
    SvgFont.java           Main public class — font data, metrics, render facade (~340 lines)
    SvgFontCache.java      Font caching + variant resolution (bold/italic/oblique)
    SvgFontLoader.java     Package-private — loads SVG font XML via Jackson XmlMapper
    font/
        Glyph.java         Single glyph: SVG path, advance width, kerning list
        Kerning.java       Record: (float offset, int unicode)
    raster/
        GlyphRaster.java   2D float[][] raster, values 0.0–1.0 (grayscale)
        GlyphRenderer.java Renders glyphs/strings via Java2D Graphics2D → GlyphRaster
    internal/
        SvgPathParser.java SVG path `d` attribute → java.awt.Shape (uses Apache Batik)
        dto/               Jackson XML mapping DTOs for SVG font file structure
```

### Data flow

```
SVG font file (.svg)
    → Jackson XmlMapper (SvgFontLoader)
        → DTOs (SvgDto → DefsDto → FontDto → GlyphDto[], HKernDto[], FontFaceDto)
            → SvgFont (domain model with Glyph[] + metrics)

Text rendering:
    SvgFont.render("text", fontSize)
        → GlyphRenderer.renderString()
            → for each char: Glyph.getShape() [lazy: SvgPathParser.parsePath(d)]
                → Graphics2D.fill(shape) on BufferedImage
                    → extract pixels → GlyphRaster
```

### Key design decisions

- **SvgFontLoader is package-private** — only `SvgFont.load(Uri)` is public. Loader accesses SvgFont fields directly (package-private visibility).
- **Glyph shapes are lazily parsed** — `Glyph.getShape()` calls `SvgPathParser.parsePath(path)` on first access, not at load time.
- **GlyphRaster is a simple float[][]** — values 0.0 (transparent) to 1.0 (opaque). Used by ewol's `ResourceFontSvg` to build OpenGL textures.
- **Font variant resolution** — `SvgFontCache.getFont(name, bold, italic)` tries BoldOblique → Bold → Oblique → base → default font.
- **Jackson `@JsonMerge` + `useWrapping=false`** — required because `<glyph>` and `<hkern>` elements are interlaced siblings in SVG font XML (not wrapped in a container element).

## Dependencies

- `etk` — `Uri` (resource resolution), `Vector2i`/`Vector2f` (math), `Configs`/`ConfigFont` (font registry)
- `jackson-dataformat-xml` (2.18.3) — XML parsing
- `batik-parser` (1.18) — SVG path data parsing

## Consumers

- `ewol/ResourceFontSvg.java` — loads `SvgFont` via `SvgFontCache`, calls `render()` to get `GlyphRaster`, converts to OpenGL texture
- `ewol/font/GlyphProperty.java` — uses `SvgFont` for glyph metrics (`calculateScaleFactor`, `calculateWidth`, `getGlyph`)

## Common patterns

### Loading a font
```java
Esvg.init();  // once at startup
SvgFont font = SvgFontCache.getFont("FreeSans", false, false);
// bold: SvgFontCache.getFont("FreeSans", true, false);
```

### Calculating text size
```java
int pixelWidth = font.calculateWidth("Hello World", 24);
Vector2i bbox = font.calculateTextSize(24, "Hello World");
float scale = font.calculateScaleFactor(24);
```

### Rendering text
```java
GlyphRaster raster = font.render("Hello", 24);
// or with kerning control:
GlyphRaster raster = font.render("Hello", 24, true);
// access pixels:
float value = raster.get(x, y);  // 0.0 = transparent, 1.0 = opaque
```

## Font metrics reference

Font units are defined by `unitsPerEm` (typically 1000). Key metrics:
- `ascent` — max height above baseline (positive, e.g. 800)
- `descent` — max depth below baseline (negative, e.g. -200)
- `capHeight` — height of capital letters (e.g. 662)
- `horizAdvX` — default horizontal advance width

`calculateFontRealHeight(fontSize)` = `fontSize * unitsPerEm / capHeight`
`calculateScaleFactor(fontSize)` = `realHeight / unitsPerEm`

## Pitfalls

1. **`@JsonMerge` is required on DTO lists** — without it, Jackson only keeps the last `<glyph>` element instead of collecting all of them. This is because `<glyph>` and `<hkern>` are interlaced (not wrapped).
2. **Font names in `SvgFontCache` must match `ConfigFont` keys** — the name passed to `getFont()` must match what was registered via `Configs.getConfigFonts().add(name, uri)`.
3. **`calculateSclaleFactor()` is deprecated** — use `calculateScaleFactor()` (fixed spelling).
4. **SVG font paths use inverted Y-axis** — SVG coordinate system has Y increasing downward, but font glyphs are defined with Y increasing upward. The renderer handles this via the ascent/descent transform.

## Build

```bash
JAVA_HOME=/usr/lib/jvm/java-25-openjdk mvn install -pl esvg
```
