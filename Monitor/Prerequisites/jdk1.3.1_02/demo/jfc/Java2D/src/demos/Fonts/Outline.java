/*
 * @(#)Outline.java	1.20 99/09/07
 *
 * Copyright (c) 1998, 1999 by Sun Microsystems, Inc. All Rights Reserved.
 * 
 * Sun grants you ("Licensee") a non-exclusive, royalty free, license to use,
 * modify and redistribute this software in source and binary code form,
 * provided that i) this copyright notice and license appear on all copies of
 * the software; and ii) Licensee does not utilize the software in a manner
 * which is disparaging to Sun.
 * 
 * This software is provided "AS IS," without a warranty of any kind. ALL
 * EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY
 * IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN AND ITS LICENSORS SHALL NOT BE
 * LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING
 * OR DISTRIBUTING THE SOFTWARE OR ITS DERIVATIVES. IN NO EVENT WILL SUN OR ITS
 * LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, OR FOR DIRECT,
 * INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE DAMAGES, HOWEVER
 * CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, ARISING OUT OF THE USE OF
 * OR INABILITY TO USE SOFTWARE, EVEN IF SUN HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 * This software is not designed or intended for use in on-line control of
 * aircraft, air traffic, aircraft navigation or aircraft communications; or in
 * the design, construction, operation or maintenance of any nuclear
 * facility. Licensee represents and warrants that it will not use or
 * redistribute the Software for such purposes.
 */

package demos.Fonts;

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;
import java.awt.font.TextAttribute;
import java.awt.font.TextLayout;
import java.awt.font.FontRenderContext;
import java.text.AttributedString;
import java.text.AttributedCharacterIterator;
import Surface;


/**
 * Rendering text as an outline shape.
 */
public class Outline extends Surface {

    public Outline() {
        setBackground(Color.white);
    }


    public void render(int w, int h, Graphics2D g2) {

        FontRenderContext frc = g2.getFontRenderContext();
        Font f = new Font("sansserif",Font.PLAIN,w/8);
        Font f1 = new Font("sansserif",Font.ITALIC,w/8);
        String s = "AttributedString";
        AttributedString as = new AttributedString(s);
        as.addAttribute(TextAttribute.FONT, f, 0, 10 );
        as.addAttribute(TextAttribute.FONT, f1, 10, s.length() );
        AttributedCharacterIterator aci = as.getIterator();
        TextLayout tl = new TextLayout (aci, frc);
        float sw = (float) tl.getBounds().getWidth();
        float sh = (float) tl.getBounds().getHeight();
        Shape sha = tl.getOutline(AffineTransform.getTranslateInstance(w/2-sw/2, h*0.2+sh/2));
        g2.setColor(Color.blue);
        g2.setStroke(new BasicStroke(1.5f));
        g2.draw(sha);
        g2.setColor(Color.magenta);
        g2.fill(sha);

        f = new Font("serif", Font.BOLD,w/6);
        tl = new TextLayout("Outline", f, frc);
        sw = (float) tl.getBounds().getWidth();
        sh = (float) tl.getBounds().getHeight();
        sha = tl.getOutline(AffineTransform.getTranslateInstance(w/2-sw/2,h*0.5+sh/2));
        g2.setColor(Color.black);
        g2.draw(sha);
        g2.setColor(Color.red);
        g2.fill(sha);

        f = new Font("sansserif",Font.ITALIC,w/8);
        AffineTransform fontAT = new AffineTransform();
        fontAT.shear(-0.2, 0.0);
        Font derivedFont = f.deriveFont(fontAT);
        tl = new TextLayout("Italic-Shear", derivedFont, frc);
        sw = (float) tl.getBounds().getWidth();
        sh = (float) tl.getBounds().getHeight();
        sha = tl.getOutline(AffineTransform.getTranslateInstance(w/2-sw/2,h*0.80f+sh/2));
        g2.setColor(Color.green);
        g2.draw(sha);
        g2.setColor(Color.black);
        g2.fill(sha);
    }


    public static void main(String s[]) {
        createDemoFrame(new Outline());
    }
}
