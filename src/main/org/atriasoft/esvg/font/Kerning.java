package org.atriasoft.esvg.font;

/**
 * Kerning pair between two glyphs.
 * <p>
 * Kerning adjusts the horizontal spacing between specific pairs of characters
 * to improve visual appearance. For example, "VA" typically has the letters
 * overlapping slightly:
 * <pre>
 * Without Kerning:
 *
 *        \          /      /\
 *         \        /      /  \
 *          \      /      /    \
 *           \    /      /------\
 *            \  /      /        \
 *             \/      /          \
 *        v          v a          a
 *
 * With Kerning:
 *
 *        \          /  /\
 *         \        /  /  \
 *          \      /  /    \
 *           \    /  /------\
 *            \  /  /        \
 *             \/  /          \
 *        v        a v        a
 * </pre>
 *
 * @param offset the kerning offset in font units (negative values move glyphs closer)
 * @param unicode the Unicode code point of the paired glyph
 */
public record Kerning(
		float offset,
		int unicode) {}
