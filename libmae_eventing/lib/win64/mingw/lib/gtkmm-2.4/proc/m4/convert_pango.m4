## gtkmm - a C++ wrapper for the Gtk toolkit
##
## Copyright 2003-2010 The gtkmm Development Team
##
## This library is free software; you can redistribute it and/or
## modify it under the terms of the GNU Lesser General Public
## License as published by the Free Software Foundation; either
## version 2.1 of the License, or (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public
## License along with this library; if not, write to the Free
## Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

# Enums:
_CONV_ENUM(Pango,AttrType)
_CONV_ENUM(Pango,Underline)
_CONV_ENUM(Pango,Direction)
_CONV_ENUM(Pango,CoverageLevel)
_CONV_ENUM(Pango,Style)
_CONV_ENUM(Pango,Variant)
_CONV_ENUM(Pango,Stretch)
_CONV_ENUM(Pango,Weight)
_CONV_ENUM(Pango,FontMask)
_CONV_ENUM(Pango,Alignment)
_CONV_ENUM(Pango,WrapMode)
_CONV_ENUM(Pango,TabAlign)
_CONV_ENUM(Pango,Script)
_CONV_ENUM(Pango,EllipsizeMode)
_CONV_ENUM(Pango,RenderPart)
_CONV_ENUM(Pango,Gravity)
_CONV_ENUM(Pango,GravityHint)

# General conversions:
_CONVERSION(`gchar*',`const char*',`($3)')
_CONVERSION(`guchar*&',`guchar**',`&($3)')
_CONVERSION(`int*&',`int**',`&($3)')


# Wrapper type conversions:
_CONVERSION(`PangoLanguage*',`Language',`Language($3)')
_CONVERSION(`PangoLanguage*',`Pango::Language',`Pango::Language($3)')
_CONVERSION(`const Language&',`const PangoLanguage*',`($3).gobj()')
_CONVERSION(`const Language&',`PangoLanguage*',`const_cast<PangoLanguage*>(`($3).gobj()')')

_CONVERSION(`Rectangle&',`PangoRectangle*',`($3).gobj()')
_CONVERSION(`Rectangle',`PangoRectangle',`*($3).gobj()')
_CONVERSION(`PangoRectangle',`Rectangle',`Rectangle(&($3))')

_CONVERSION(`Color&',`PangoColor*',`($3).gobj()')
_CONVERSION(`const Color&',`const PangoColor*',`($3).gobj()')
_CONVERSION(`Color',`PangoColor',`*($3).gobj()')
_CONVERSION(`PangoColor',`Color',`Color(&($3))')

_CONVERSION(`PangoFontDescription*',`FontDescription',`FontDescription(($3))')
_CONVERSION(`const PangoFontDescription*',`FontDescription',`FontDescription(const_cast<PangoFontDescription*>($3))')
_CONVERSION(`Pango::FontDescription&',`PangoFontDescription*',`($3).gobj()')
_CONVERSION(`FontDescription&',`PangoFontDescription*',`($3).gobj()')
_CONVERSION(`const FontDescription&',`const PangoFontDescription*',`($3).gobj()')
_CONVERSION(`const Pango::FontDescription&',`PangoFontDescription*',`const_cast<PangoFontDescription*>(`($3).gobj()')')
_CONVERSION(`const FontDescription&',`PangoFontDescription*',`const_cast<PangoFontDescription*>(`($3).gobj()')')

_CONVERSION(`PangoFontMetrics*',`FontMetrics',`FontMetrics(($3))')

_CONVERSION(`PangoAttribute*',`Attribute',`Attribute(($3))')
_CONVERSION(`Attribute&',`PangoAttribute*',`($3).gobj()')
_CONVERSION(`const Attribute&',`const PangoAttribute*',`($3).gobj()')

_CONVERSION(`PangoAttrList*',`AttrList',`AttrList(($3))')
_CONVERSION(`PangoAttrList*',`Pango::AttrList',`Pango::AttrList(($3))')
_CONVERSION(`AttrList&',`PangoAttrList*',`($3).gobj()')
_CONVERSION(`Pango::AttrList&',`PangoAttrList*',`($3).gobj()')

_CONVERSION(`PangoAttrIterator*',`AttrIter',`Glib::wrap(($3))')

_CONVERSION(`PangoAnalysis',`Analysis',`Analysis(&($3))')
_CONVERSION(`PangoAnalysis',`const Analysis',`Analysis(&($3))')
_CONVERSION(`Analysis&',`PangoAnalysis*',`($3).gobj()')
_CONVERSION(`const Analysis&',`const PangoAnalysis*',`($3).gobj()')
_CONVERSION(`const Analysis&',`PangoAnalysis*',`const_cast<PangoAnalysis*>(($3).gobj())')

_CONVERSION(`PangoItem*',`Item',`Item(($3))')
_CONVERSION(`PangoItem*',`const Item',`Item(($3))')
_CONVERSION(`Item&',`PangoItem*',`($3).gobj()')
_CONVERSION(`const Item&',`const PangoItem*',`($3).gobj()')

_EQUAL(`PangoGlyph',`Glyph')
_EQUAL(`PangoGlyphUnit',`GlyphUnit')
_EQUAL(`PangoGlyphVisAttr',`GlyphVisAttr')
#_CONVERSION(`PangoGlyphVisAttr',`GlyphVisAttr',`GlyphVisAttr(&($3))')
#_CONVERSION(`GlyphVisAttr',`PangoGlyphVisAttr',`*($3).gobj()')
_CONVERSION(`PangoGlyphGeometry',`GlyphGeometry',`GlyphGeometry(&($3))')
_CONVERSION(`GlyphGeometry',`PangoGlyphGeometry',`*($3).gobj()')

_CONVERSION(`PangoGlyphString*',`GlyphString',`GlyphString(($3))')
_CONVERSION(`PangoGlyphString*',`const GlyphString',`GlyphString(($3))')
_CONVERSION(`const Pango::GlyphString&',`PangoGlyphString*',const_cast<PangoGlyphString*>($3.gobj()))
_CONVERSION(`const GlyphString&',`PangoGlyphString*',const_cast<PangoGlyphString*>($3.gobj()))

_CONVERSION(`PangoFont*',`Glib::RefPtr<Font>',Glib::wrap($3))
_CONVERSION(`PangoFont*',`Glib::RefPtr<Pango::Font>',Glib::wrap($3))
_CONVERSION(`PangoFont*',`Glib::RefPtr<const Font>',Glib::wrap($3))
_CONVERSION(`PangoFont*',`Glib::RefPtr<const Pango::Font>',Glib::wrap($3))
_CONVERSION(`const Glib::RefPtr<Font>&',`PangoFont*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Pango::Font>&',`PangoFont*',__CONVERT_REFPTR_TO_P)
# Special treatment for the Sun Forte compiler
#_CONVERSION(const Glib::RefPtr<const Font>&,`PangoFont*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Font>&',`PangoFont*',__CONVERT_CONST_REFPTR_TO_P_SUN(Font))
#_CONVERSION(`const Glib::RefPtr<const Font>&',`PangoFont*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Pango::Font>&',`PangoFont*',__CONVERT_CONST_REFPTR_TO_P_SUN(Pango::Font))

_CONVERSION(`PangoFontFace*',`Glib::RefPtr<Pango::FontFace>',Glib::wrap($3))
_CONVERSION(`PangoFontFace*',`Glib::RefPtr<const Pango::FontFace>',Glib::wrap($3))
_CONVERSION(`PangoFontFamily*',`Glib::RefPtr<Pango::FontFamily>',Glib::wrap($3))
_CONVERSION(`PangoFontFamily*',`Glib::RefPtr<const Pango::FontFamily>',Glib::wrap($3))

_CONVERSION(`PangoFontMap*',`Glib::RefPtr<FontMap>',Glib::wrap($3))
_CONVERSION(`PangoFontMap*',`Glib::RefPtr<const FontMap>',Glib::wrap($3))
_CONVERSION(`const Glib::RefPtr<FontMap>&',`PangoFontMap*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`PangoCairoFontMap*',`Glib::RefPtr<CairoFontMap>',Glib::wrap($3))

_CONVERSION(`PangoFontSet*',`Glib::RefPtr<FontSet>',Glib::wrap($3))
_CONVERSION(`const Glib::RefPtr<FontSet>&',`PangoFontSet*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`PangoContext*',`Glib::RefPtr<Pango::Context>',Glib::wrap($3))
_CONVERSION(`PangoContext*',`Glib::RefPtr<Context>',Glib::wrap($3))
_CONVERSION(`const Glib::RefPtr<Context>&',`PangoContext*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`PangoLayout*',`Glib::RefPtr<Pango::Layout>',Glib::wrap($3))
_CONVERSION(`PangoLayout*',`Glib::RefPtr<const Pango::Layout>',Glib::wrap($3))
_CONVERSION(`PangoLayout*',`Glib::RefPtr<Layout>',Glib::wrap($3))
_CONVERSION(`PangoLayout*',`const Glib::RefPtr<Pango::Layout>&',Glib::wrap($3))
_CONVERSION(`const Glib::RefPtr<Layout>&',`PangoLayout*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Pango::Layout>&',`PangoLayout*',__CONVERT_REFPTR_TO_P)
# Special treatment for the Sun Forte compiler
_CONVERSION(`const Glib::RefPtr<const Pango::Layout>&',`PangoLayout*',__CONVERT_CONST_REFPTR_TO_P_SUN(Pango::Layout))
_CONVERSION(`const Glib::RefPtr<const Layout>&',`PangoLayout*',__CONVERT_CONST_REFPTR_TO_P_SUN(Layout))

_CONVERSION(`PangoLayoutLine*',`Glib::RefPtr<Pango::LayoutLine>',`Glib::wrap($3)')
_CONVERSION(`PangoLayoutLine*',`Glib::RefPtr<LayoutLine>',`Glib::wrap($3)')
_CONVERSION(`PangoLayoutLine*',`Glib::RefPtr<const LayoutLine>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Pango::LayoutLine>&',`PangoLayoutLine*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<LayoutLine>&',`PangoLayoutLine*',__CONVERT_REFPTR_TO_P)
# Special treatment for the Sun Forte compiler
_CONVERSION(`const Glib::RefPtr<const Pango::LayoutLine>&',`PangoLayoutLine*',__CONVERT_CONST_REFPTR_TO_P_SUN(Pango::LayoutLine))
_CONVERSION(`const Glib::RefPtr<const LayoutLine>&',`PangoLayoutLine*',__CONVERT_CONST_REFPTR_TO_P_SUN(LayoutLine))

_CONVERSION(`PangoLayoutRun*',`LayoutRun',Glib::wrap($3))

_CONVERSION(`PangoLayoutIter*',`LayoutIter',`LayoutIter($3)')

_CONVERSION(`PangoCoverage*',`Glib::RefPtr<Coverage>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Coverage>&',`PangoCoverage*',`Glib::unwrap($3)')

_CONVERSION(`PangoTabArray*',`Pango::TabArray',`Pango::TabArray(($3))')
_CONVERSION(`PangoTabArray*',`TabArray',`TabArray(($3))')
_CONVERSION(`Pango::TabArray&',`PangoTabArray*',($3).gobj())
_CONVERSION(`TabArray&',`PangoTabArray*',($3).gobj())

_CONVERSION(`PangoTabAlign&',`PangoTabAlign*',`&$3',`*$3')
_CONVERSION(`Pango::TabAlign&',`PangoTabAlign*',`((PangoTabAlign*) &($3))')
_CONVERSION(`TabAlign&',`PangoTabAlign*',`((PangoTabAlign*) &($3))')

_CONVERSION(`const Matrix&',`const PangoMatrix*',`&($3)')

#The documentation for pango_context_get_matrix() suggests that it's generally OK 
#to consider PANGO_MATRIX_INIT and a NULL PangoMatrix* as being equivalent:
#But this would cause 2 function calls.
#_CONVERSION(`const PangoMatrix*',`Matrix',`($3) ? *($3) : PANGO_MATRIX_INIT')
#_CONVERSION(`const Matrix&',`PangoMatrix*',`const_cast<PangoMatrix*>(&($3))')

define(`__FL2H_SHALLOW',`$`'2($`'3, Glib::OWNERSHIP_SHALLOW)')
_CONVERSION(`GSList*',`SListHandle_LayoutLine',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`SListHandle_ConstLayoutLine',__FL2H_SHALLOW)

_CONVERSION(`PangoFontMap*',`Glib::RefPtr<Pango::FontMap>',`Glib::wrap($3)')

_CONVERSION(`const Cairo::FontOptions&',`const cairo_font_options_t*',`($3).cobj()')

