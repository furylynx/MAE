// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GTKMM_FRAME_H
#define _GTKMM_FRAME_H


#include <glibmm.h>

/* $Id: frame.hg,v 1.6 2006/04/12 11:11:25 murrayc Exp $ */

/* frame.h
 * 
 * Copyright (C) 1998-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include <gtkmm/bin.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkFrame GtkFrame;
typedef struct _GtkFrameClass GtkFrameClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class Frame_Class; } // namespace Gtk
namespace Gtk
{

/** A Gtk::Bin with a decorative frame and optional label.
 *
 * The Frame widget surrounds its single child with a decorative frame and
 * an optional label.  If present, the label is drawn in a gap in the top
 * side of the frame. The position of the label can be controlled with
 * set_label_align().
 *
 * A Frame widget looks like this:
 * @image html frame1.png
 *
 * @ingroup Widgets
 * @ingroup Containers
 */

class Frame : public Bin
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Frame CppObjectType;
  typedef Frame_Class CppClassType;
  typedef GtkFrame BaseObjectType;
  typedef GtkFrameClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~Frame();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class Frame_Class;
  static CppClassType frame_class_;

  // noncopyable
  Frame(const Frame&);
  Frame& operator=(const Frame&);

protected:
  explicit Frame(const Glib::ConstructParams& construct_params);
  explicit Frame(GtkFrame* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkFrame*       gobj()       { return reinterpret_cast<GtkFrame*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkFrame* gobj() const { return reinterpret_cast<GtkFrame*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

public:

  Frame();
  explicit Frame(const Glib::ustring& label);

  //TODO: Add a bool use_markup arg to set_label() as a convenience - it would have to use set_label_widget().
    
  
  /** Set the label to appear in the top edge of the frame.
   * Label alignment defaults to the upper left corner of the frame.
   */
  void set_label(const Glib::ustring& label);
  void unset_label();
  
  /** If the frame's label widget is a Gtk::Label, returns the
   * text in the label widget. (The frame will have a Gtk::Label
   * for the label widget if a non-<tt>0</tt> argument was passed
   * to new().)
   * @return The text in the label, or <tt>0</tt> if there
   * was no label widget or the lable widget was not
   * a Gtk::Label. This string is owned by GTK+ and
   * must not be modified or freed.
   */
  Glib::ustring get_label() const;

  
  /** Sets the label widget for the frame. This is the widget that
   * will appear embedded in the top edge of the frame as a
   * title.
   * @param label_widget The new label widget.
   */
  void set_label_widget(Widget& label_widget);
  
  /** Retrieves the label widget for the frame. See
   * set_label_widget().
   * @return The label widget, or <tt>0</tt> if there is none.
   */
  Widget* get_label_widget();
  
  /** Retrieves the label widget for the frame. See
   * set_label_widget().
   * @return The label widget, or <tt>0</tt> if there is none.
   */
  const Widget* get_label_widget() const;

  
  /** Set the alignment of the Frame's label.
   * @param xalign The position of the label along the top edge of the widget.
   * A value of 0.0 represents left alignment; 1.0 represents right alignment.
   * The default value for a newly created Frame is 0.0.
   * @param yalign The y alignment of the label. Currently ignored.
   */
  void set_label_align(float xalign = 0.0, float yalign = 0.5);
  
  /** Sets the alignment of the frame widget's label. The
   * default values for a newly created frame are 0.0 and 0.5.
   * @param xalign The position of the label along the top edge
   * of the widget. A value of 0.0 represents left alignment;
   * 1.0 represents right alignment.
   * @param yalign The y alignment of the label. A value of 0.0 aligns under 
   * the frame; 1.0 aligns above the frame. If the values are exactly
   * 0.0 or 1.0 the gap in the frame won't be painted because the label
   * will be completely above or below the frame.
   */
  void set_label_align(AlignmentEnum xalign, AlignmentEnum yalign = Gtk::ALIGN_CENTER);

  
  /** Retrieves the X and Y alignment of the frame's label. See
   * set_label_align().
   * @param xalign Location to store X alignment of frame's label, or <tt>0</tt>.
   * @param yalign Location to store X alignment of frame's label, or <tt>0</tt>.
   */
  void get_label_align(float& xalign, float& yalign) const;

  
  /** Sets shadow type of the frame.
   */
  void set_shadow_type(ShadowType type);
  
  /** Retrieves the shadow type of the frame. See
   * set_shadow_type().
   * @return The current shadow type of the frame.
   */
  ShadowType get_shadow_type() const;

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Text of the frame's label.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_label() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Text of the frame's label.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_label() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The horizontal alignment of the label.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<double> property_label_xalign() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The horizontal alignment of the label.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<double> property_label_xalign() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The vertical alignment of the label.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<double> property_label_yalign() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The vertical alignment of the label.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<double> property_label_yalign() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  //deprecated: _WRAP_PROPERTY("shadow", ShadowType)
  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Appearance of the frame border.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<ShadowType> property_shadow_type() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Appearance of the frame border.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<ShadowType> property_shadow_type() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** A widget to display in place of the usual frame label.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Widget*> property_label_widget() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** A widget to display in place of the usual frame label.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Widget*> property_label_widget() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


protected:
    virtual void compute_child_allocation_vfunc(Allocation& allocation);


};

} // namespace Gtk


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::Frame
   */
  Gtk::Frame* wrap(GtkFrame* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_FRAME_H */

