package org.atriasoft.esvg.font;

/**
 * @notindoc
 * Kerning properties of one specific Glyph with an other
 * 
 * Without Kerning :
 * [pre]
 *                                     
 *        \          /      /\         
 *         \        /      /  \        
 *          \      /      /    \       
 *           \    /      /------\      
 *            \  /      /        \     
 *             \/      /          \    
 *        v          v a          a    
 * [/pre]
 * 
 * With Kerning :
 * [pre]
 *                                     
 *        \          /  /\             
 *         \        /  /  \            
 *          \      /  /    \           
 *           \    /  /\          
 *            \  /  /        \         
 *             \/  /          \        
 *        v        a v        a        
 * [/pre]
 * 
 * @note The "Kerning" is the methode to provide a better display for some string like
 *       the "VA" has 2 letter that overlap themself. This name Kerning
 */
public record Kerning(
		float offset,
		int unicode) {}
