// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GTKMM_TABLE_H
#define _GTKMM_TABLE_H


#include <glibmm.h>

/* $Id: table.hg,v 1.3 2006/05/16 14:16:08 jjongsma Exp $ */

/* Copyright (C) 1998-2002 The gtkmm Development Team
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

#include <glibmm/helperlist.h>
#include <gtkmm/container.h>
#include <gtkmm/enums.h>

//TODO: Careful of including this before box.h,
//because we need to undef some things first.
//TODO: Maybe do all includes of gtk.h in a single file.
#include <gtk/gtk.h> /* for GtkTableChild */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkTable GtkTable;
typedef struct _GtkTableClass GtkTableClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class Table_Class; } // namespace Gtk
namespace Gtk
{

class Table;

/** @deprecated Use Container::get_children() instead.
 */
namespace Table_Helpers
{

/** @deprecated Use Container::get_children() instead.
 */
class Child : protected _GtkTableChild
{
private:
  Child& operator=(const Child&); //Not implemented.
  Child(const Child&); //Not implemented.

public:
  inline _GtkTableChild* gobj() {return (this);}
  inline const _GtkTableChild* gobj() const {return (this);}

#ifndef GTKMM_DISABLE_DEPRECATED

  Widget* get_widget() const;

  //TODO: Which of the GtkTableChild's fields are public API?
  //Maybe we should remove some of these get()s or add some set()s.
  //If get_widget() is the only accessor, then we should probably make
  //the STL-style Table list contain Widgets instead of Childs.

  guint16 get_left_attach() const;
  guint16 get_right_attach() const;
  guint16 get_top_attach() const;
  guint16 get_bottom_attach() const;
  guint16 get_xpadding() const;
  guint16 get_ypadding() const;
  bool get_xexpand() const;
  bool get_yexpand() const;
  bool get_xshrink() const;
  bool get_yshrink() const;
  bool get_xfill() const;
  bool get_yfill() const;
#endif // GTKMM_DISABLE_DEPRECATED


protected:
  inline GtkTable* parent()
    { return GTK_TABLE(gtk_widget_get_parent(gobj()->widget)); }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  friend class Dummy_; // silence the compiler (Child has only private ctors)
#endif
};


class TableList : public Glib::HelperList< Child, Widget, Glib::List_Iterator< Child > >
{
public:
  TableList();
  explicit TableList(GtkTable* gparent);
  TableList(const TableList& src);
  virtual ~TableList() {}

  TableList& operator=(const TableList& src);

  typedef Glib::HelperList< Child, Widget,  Glib::List_Iterator< Child > > type_base;

  GtkTable* gparent();
  const GtkTable* gparent() const;

  virtual GList*& glist() const;      // front of list

  virtual void erase(iterator start, iterator stop);
  virtual iterator erase(iterator);  //Implented as custom or by LIST_CONTAINER_REMOVE
  virtual void remove(const_reference); //Implented as custom or by LIST_CONTAINER_REMOVE

  /// This is order n. (use at own risk)
  reference operator[](size_type l) const;

protected:
  //Hide these because its read-only:
  iterator insert(iterator position, element_type& e);

  inline void pop_front();
  inline void pop_back();


  //The standard iterator, instead of List_Cpp_Iterator,
  //only works because Child is derived from _GtkTableChild.

  
virtual void remove(Widget& w); //Implented as custom or by LIST_CONTAINER_REMOVE

  };


} // namespace Table_Helpers


/** Pack widgets in regular patterns.
 * @ingroup Widgets
 * @ingroup Containers
 * Gtk::Table is one of the primary ways of grouping widgets together.  It
 * consists of a set of lattice points to to which widgets can be attached.
 * There are <em>rows</em>&nbsp;+&nbsp;1 lattice points vertically and
 * <em>columns</em>&nbsp;+&nbsp;1 lattice points horizontally.  Lattice points
 * start counting from 0.  Lattice points can either be specified to be
 * <em>homogeneous</em>, meaning equally spaced, or not <em>homogeneous</em>,
 * meaning each cell should be calculated based on the widgets contained in the
 * row and column. The <em>homogeneous</em> property defaults to false.
 *
 * Widgets can be attached to the table by specifying the top, bottom, left and
 * right points corresponding to upper, lefthand lattice point and the lower,
 * righthand lattice point which the widget should span.  Widgets can either be
 * contained in a cell or may span cells.  A number of options control the
 * resizing behavior of widgets contained in the table.
 *
 * @par Packing options:
 * There are a number of packing options that can be specified when adding a
 * widget.  With <tt>Gtk::EXPAND</tt>, the lattice is allowed to grow to fill
 * space.  With <tt>Gtk::SHRINK</tt>, the lattice is allowed to shrink when
 * resized.  It is also possible to specify the behaviour of the widgets
 * allocation within the table.  The flag <tt>Gtk::FILL</tt> declares the
 * widget should grow to fill lattice.  If this is not set any extra space is
 * used as padding.  The default is <tt>(Gtk::FILL&nbsp;|&nbsp;Gtk::EXPAND)</tt>.
 *
 * @par Table sizing:
 * The table size is calculated based on the size of the widgets contained
 * within and the restrictions imposed by specified options.  Padding and
 * spacing can be used in the table.  Padding is added on either side of a
 * widget, while spacing is placed between widgets.
 *
 * A Table widget looks like this:
 * @image html table1.png
 *
 * @see Gtk::HBox, Gtk::VBox
 */

class Table : public Container
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Table CppObjectType;
  typedef Table_Class CppClassType;
  typedef GtkTable BaseObjectType;
  typedef GtkTableClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~Table();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class Table_Class;
  static CppClassType table_class_;

  // noncopyable
  Table(const Table&);
  Table& operator=(const Table&);

protected:
  explicit Table(const Glib::ConstructParams& construct_params);
  explicit Table(GtkTable* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkTable*       gobj()       { return reinterpret_cast<GtkTable*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkTable* gobj() const { return reinterpret_cast<GtkTable*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

  
public:
  explicit Table(guint n_rows = 1, guint n_columns = 1, bool homogeneous = false);

  
        void attach(Widget& child,
                    guint left_attach, guint right_attach,
                    guint top_attach, guint bottom_attach,
                    AttachOptions xoptions = FILL | EXPAND, AttachOptions yoptions = FILL | EXPAND,
                    guint xpadding = 0, guint ypadding = 0);


  void resize(guint rows, guint columns);


  void set_row_spacing(guint row, guint spacing);
  
  /** Gets the amount of space between row @a row, and
   * row @a row + 1. See set_row_spacing().
   * @param row A row in the table, 0 indicates the first row.
   * @return The row spacing.
   */
  guint get_row_spacing(guint row) const;

  
  void set_col_spacing(guint column, guint spacing);
  
  /** Gets the amount of space between column @a col, and
   * column @a col + 1. See set_col_spacing().
   * @param column A column in the table, 0 indicates the first column.
   * @return The column spacing.
   */
  guint get_col_spacing(guint column) const;

  
  void set_row_spacings(guint spacing);

  
  void set_col_spacings(guint spacing);

  void set_spacings(guint spacing);

  
  /** Gets the default row spacing for the table. This is
   * the spacing that will be used for newly added rows.
   * (See set_row_spacings())
   * @return The default row spacing.
   */
  guint get_default_row_spacing();
  
  /** Gets the default column spacing for the table. This is
   * the spacing that will be used for newly added columns.
   * (See set_col_spacings())
   * @return The default column spacing.
   */
  guint get_default_col_spacing();

  
  void set_homogeneous(bool homogeneous = true);
  
  /** Returns whether the table cells are all constrained to the same
   * width and height. (See set_homogenous())
   * @return <tt>true</tt> if the cells are all constrained to the same size.
   */
  bool get_homogeneous() const;

  
  /** Returns the number of rows and columns in the table.
   * 
   * @newin{2,22}
   * @param rows Return location for the number of
   * rows, or <tt>0</tt>.
   * @param columns Return location for the number
   * of columns, or <tt>0</tt>.
   */
  void get_size(guint& rows,  guint& columns) const;

  /** @deprecated Use Container::get_children() instead.
   */
  typedef Table_Helpers::TableList TableList;

#ifndef GTKMM_DISABLE_DEPRECATED

  /** @deprecated Use Container::get_children() instead.
   */
  TableList& children();

  /** @deprecated Use Container::get_children() instead.
   */
  const TableList& children() const;
#endif // GTKMM_DISABLE_DEPRECATED


  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The number of rows in the table.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<guint> property_n_rows() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The number of rows in the table.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<guint> property_n_rows() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The number of columns in the table.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<guint> property_n_columns() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The number of columns in the table.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<guint> property_n_columns() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The amount of space between two consecutive columns.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<guint> property_column_spacing() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The amount of space between two consecutive columns.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<guint> property_column_spacing() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The amount of space between two consecutive rows.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<guint> property_row_spacing() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The amount of space between two consecutive rows.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<guint> property_row_spacing() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** If TRUE, the table cells are all the same width/height.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<bool> property_homogeneous() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** If TRUE, the table cells are all the same width/height.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_homogeneous() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


protected:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  mutable TableList children_proxy_;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


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
   * @relates Gtk::Table
   */
  Gtk::Table* wrap(GtkTable* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_TABLE_H */

