// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GTKMM_ENTRYBUFFER_H
#define _GTKMM_ENTRYBUFFER_H

#include <gtkmmconfig.h>


#include <glibmm.h>

/* $Id: entrybuffer.hg,v 1.20 2006/11/20 09:19:49 murrayc Exp $ */

/* Copyright(C) 1998-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or(at your option) any later version.
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

// This is for including the config header before any code (such as
// the #ifndef GTKMM_DISABLE_DEPRECATED in deprecated classes) is generated:


#include <gtkmm/object.h>
#include <gtkmmconfig.h>
#include <utility>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkEntryBuffer GtkEntryBuffer;
typedef struct _GtkEntryBufferClass GtkEntryBufferClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class EntryBuffer_Class; } // namespace Gtk
namespace Gtk
{

/** A Text buffer for the Entry widget.
 *
 * The EntryBuffer class contains the actual text displayed in an Entry widget.
 *
 * A single EntryBuffer object can be shared by multiple Entry
 * widgets which will then share the same text content, but not the cursor
 * position, visibility attributes, icon etc.
 *
 * EntryBuffer may be derived from. Such a derived class might allow
 * text to be stored in an alternate location, such as non-pageable memory,
 * useful in the case of important passwords. Or a derived class could 
 * integrate with an application's concept of undo/redo.
 *
 * @@newin{2,20}
 */

class EntryBuffer : public Glib::Object
{
   
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  typedef EntryBuffer CppObjectType;
  typedef EntryBuffer_Class CppClassType;
  typedef GtkEntryBuffer BaseObjectType;
  typedef GtkEntryBufferClass BaseClassType;

private:  friend class EntryBuffer_Class;
  static CppClassType entrybuffer_class_;

private:
  // noncopyable
  EntryBuffer(const EntryBuffer&);
  EntryBuffer& operator=(const EntryBuffer&);

protected:
  explicit EntryBuffer(const Glib::ConstructParams& construct_params);
  explicit EntryBuffer(GtkEntryBuffer* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  virtual ~EntryBuffer();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GtkEntryBuffer*       gobj()       { return reinterpret_cast<GtkEntryBuffer*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GtkEntryBuffer* gobj() const { return reinterpret_cast<GtkEntryBuffer*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GtkEntryBuffer* gobj_copy();

private:

protected:

  /** Create a new EntryBuffer object with no text.
   */
  EntryBuffer();

  /** Create a new EntryBuffer object.
   *
   * @param text Initial buffer text.
   */
  explicit EntryBuffer(const Glib::ustring& text);

public:
  /** Create a new EntryBuffer object with no text.
   */
  
  static Glib::RefPtr<EntryBuffer> create();


  /** Create a new EntryBuffer object.
   *
   * @param text Initial buffer text.
   */
  
  static Glib::RefPtr<EntryBuffer> create(const Glib::ustring& text);


  /** Retrieves the length in bytes of the buffer.
   * See get_length().
   * 
   * @newin{2,18}
   * @return The byte length of the buffer.
   */
  gsize get_bytes() const;
  
  /** Retrieves the length in characters of the buffer.
   * 
   * @newin{2,18}
   * @return The number of characters in the buffer.
   */
  guint get_length() const;
  
  /** Retrieves the contents of the buffer.
   * 
   * The memory pointer returned by this call will not change
   * unless this object emits a signal, or is finalized.
   * 
   * @newin{2,18}
   * @return A pointer to the contents of the widget as a
   * string. This string points to internally allocated
   * storage in the buffer and must not be freed, modified or
   * stored.
   */
  Glib::ustring get_text() const;

  /** Sets the text in the buffer.
   * This is roughly equivalent to calling delete_text() and insert_text().
   *
   * @param text The text to set in the buffer.
   */
  void set_text(const Glib::ustring& text);
  

  /** Sets the maximum allowed length of the contents of the buffer. If
   * the current contents are longer than the given length, then they
   * will be truncated to fit.
   * 
   * @newin{2,18}
   * @param max_length The maximum length of the entry buffer, or 0 for no maximum.
   * (other than the maximum length of entries.) The value passed in will
   * be clamped to the range 0-65536.
   */
  void set_max_length(int max_length);
  
  /** Retrieves the maximum allowed length of the text in
   *  @a buffer. See set_max_length().
   * 
   * @newin{2,18}
   * @return The maximum allowed number of characters
   * in Gtk::EntryBuffer, or 0 if there is no maximum.
   */
  int get_max_length() const;

  /** Inserts @a text into the contents of the buffer, at position @a position.
   *
   * @param position The position at which to insert text.
   * @param text The text to insert into the buffer.
   * @result The number of characters actually inserted.
   */
  guint insert_text(guint position, const Glib::ustring& text);
  

  /** Deletes a sequence of characters from the buffer. @a n_chars characters are
   * deleted starting at @a position. If @a n_chars is negative, then all characters
   * until the end of the text are deleted.
   * 
   * If @a position or @a n_chars are out of bounds, then they are coerced to sane
   * values.
   * 
   * Note that the positions are specified in characters, not bytes.
   * 
   * @newin{2,18}
   * @param position Position at which to delete text.
   * @param n_chars Number of characters to delete.
   * @return The number of characters deleted.
   */
  guint delete_text(guint position, int n_chars);

  /** Used when deriving from EntryBuffer.
   * @param position Position at which text was inserted.
   * @param text Text that was inserted.
   */
  void emit_inserted_text(guint position, const Glib::ustring& text);
  

  /** Used when subclassing Gtk::EntryBuffer
   * 
   * @newin{2,18}
   * @param position Position at which text was deleted.
   * @param n_chars Number of characters deleted.
   */
  void emit_deleted_text(guint position, guint n_chars);

  
  /**
   * @par Prototype:
   * <tt>void on_my_%inserted_text(guint position, const gchar* chars, guint n_chars)</tt>
   */

  Glib::SignalProxy3< void,guint,const gchar*,guint > signal_inserted_text();

  
  /**
   * @par Prototype:
   * <tt>void on_my_%deleted_text(guint position, guint n_chars)</tt>
   */

  Glib::SignalProxy2< void,guint,guint > signal_deleted_text();


  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The contents of the buffer.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_text() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The contents of the buffer.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_text() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Length of the text currently in the buffer.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<guint> property_length() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Maximum number of characters for this entry. Zero if no maximum.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<int> property_max_length() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** Maximum number of characters for this entry. Zero if no maximum.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<int> property_max_length() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::
  virtual void on_inserted_text(guint position, const gchar* chars, guint n_chars);
  virtual void on_deleted_text(guint position, guint n_chars);


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
   * @relates Gtk::EntryBuffer
   */
  Glib::RefPtr<Gtk::EntryBuffer> wrap(GtkEntryBuffer* object, bool take_copy = false);
}


#endif /* _GTKMM_ENTRYBUFFER_H */

