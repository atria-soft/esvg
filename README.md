Atria-soft ESVG
==============

[MPL-2] Mozilla Public License (V 2.0)

## Overview

**esvg** is a pure Java library for loading and rendering SVG fonts. It parses SVG font files (as defined by [SVG Tiny 1.2](https://www.w3.org/TR/SVGTiny12/fonts.html)), extracts glyph outlines, font metrics, and kerning data, and rasterizes text to grayscale bitmaps.

## Features

- Load SVG font files (`.svg`) with full glyph, metric, and kerning support
- Calculate text dimensions (width, height) for a given font size
- Render individual glyphs or full text strings to grayscale rasters
- Font variant resolution (bold, italic/oblique) with automatic fallback
- Font caching to avoid redundant parsing
- Lazy glyph shape parsing (SVG path data is only parsed on first use)
- Bundled fonts: FreeSherif, FreeSans, FreeMono

## Dependencies

- `etk` (Atria-soft core toolkit) — URI resolution, math utilities
- `jackson-dataformat-xml` — SVG font file XML parsing
- `batik-parser` — SVG path `d` attribute parsing to `java.awt.Shape`

## Quick Start

```java
// 1. Initialize the module (registers bundled fonts)
Esvg.init();

// 2. Load a font (uses SvgFontCache for automatic caching)
SvgFont font = SvgFontCache.getFont("FreeSans", false, false);

// 3. Calculate text metrics
int width = font.calculateWidth("Hello", 24);
Vector2i size = font.calculateTextSize(24, "Hello");

// 4. Render text to a grayscale raster
GlyphRaster raster = font.render("Hello", 24);
float pixel = raster.get(10, 5);  // 0.0 = transparent, 1.0 = opaque
```

## Architecture

```
org.atriasoft.esvg/
    Esvg                    Module initializer (registers fonts)
    SvgFont                 Main public class: font data, metrics, render facade
    SvgFontCache            Cached font loading with variant resolution
    SvgFontLoader           (internal) XML parsing via Jackson XmlMapper
    font/
        Glyph               Single glyph: path data, advance width, kerning
        Kerning             Kerning pair (offset + unicode target)
    raster/
        GlyphRaster         2D grayscale raster output (float[][])
        GlyphRenderer       Glyph/text rendering via Java2D Graphics2D
    internal/
        SvgPathParser       SVG path `d` → java.awt.Shape (via Batik)
        dto/                Jackson XML mapping DTOs (SvgDto, FontDto, etc.)
```

## Font Metrics

```
                          *----------------------*   calculateFontRealHeight()
                          |                      |      getAscent()
                          |          /\          |          Font Height = fontSize
                          |         /  \         |
                          |        /    \        |
                          |       /------\       |
                          |      /        \      |
                          |     /          \     |   ← render baseline
                          |                      |      getDescent()
                          *----------------------*
```

Key methods on `SvgFont`:
- `calculateFontRealHeight(fontSize)` — total pixel height including ascent + descent
- `calculateScaleFactor(fontSize)` — scale from font units to pixels
- `calculateWidth(text, fontSize)` — pixel width of a text string (with kerning)
- `calculateTextSize(fontSize, text)` — bounding box as `Vector2i`
- `calculateRenderOffset(fontSize)` — baseline offset for proper positioning

## Building

```bash
JAVA_HOME=/usr/lib/jvm/java-25-openjdk mvn install -pl esvg
```
