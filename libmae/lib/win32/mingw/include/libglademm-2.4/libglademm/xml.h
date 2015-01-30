// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _LIBGLADEMM_XML_H
#define _LIBGLADEMM_XML_H


#include <glibmm.h>

/* $Id: xml.hg,v 1.21 2004/09/19 12:55:53 murrayc Exp $ */

/* Copyright (C) 2002 The libglademm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gtkmm/container.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GladeXML GladeXML;
typedef struct _GladeXMLClass GladeXMLClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gnome
{

namespace Glade
{ class Xml_Class; } // namespace Glade

} // namespace Gnome
namespace Gnome
{

namespace Glade
{

class XmlError : public Glib::Exception
{
public:
  explicit XmlError(const Glib::ustring& message);
  virtual ~XmlError() throw();

  XmlError(const XmlError& other);
  XmlError& operator=(const XmlError& other);

  virtual Glib::ustring what() const;

private:
  Glib::ustring message_;
};


class Xml : public Glib::Object
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  typedef Xml CppObjectType;
  typedef Xml_Class CppClassType;
  typedef GladeXML BaseObjectType;
  typedef GladeXMLClass BaseClassType;

private:  friend class Xml_Class;
  static CppClassType xml_class_;

private:
  // noncopyable
  Xml(const Xml&);
  Xml& operator=(const Xml&);

protected:
  explicit Xml(const Glib::ConstructParams& construct_params);
  explicit Xml(GladeXML* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  virtual ~Xml();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GladeXML*       gobj()       { return reinterpret_cast<GladeXML*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GladeXML* gobj() const { return reinterpret_cast<GladeXML*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GladeXML* gobj_copy();

private:

  
   //Ignore private glade_xml functions.

protected:
  /** Loads a glade XML file.
   * @throw XmlError
   */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  Xml(const std::string& filename, const Glib::ustring& root, const Glib::ustring& domain);
#else
  Xml(const std::string& filename, const Glib::ustring& root, const Glib::ustring& domain, std::auto_ptr<XmlError>& error);
#endif

  /** Reads glade XML data from memory.
   * @throw XmlError
   */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  Xml(const char* buffer, int size, const Glib::ustring& root, const Glib::ustring& domain);
#else
  Xml(const char* buffer, int size, const Glib::ustring& root, const Glib::ustring& domain, std::auto_ptr<XmlError>& error);
#endif

  Gtk::Widget* get_widget_checked(const Glib::ustring& name, GType type);
  GtkWidget* get_cwidget(const Glib::ustring& name);

public:
  typedef Gnome::Glade::XmlError Error;

  /** Loads a Glade XML file.
   *
   * This will instantiate the widgets in the XML file. You can use the root
   * parameter to only instantiate a certain widget and its children. The
   * returned Xml object keeps pointers to the instantiated widgets which you
   * can retrieve with get_widget().
   *
   * Note that the Xml object does not delete the widgets it instantiates, but
   * instead leaves the responsibility to you. See get_widget(). This
   * means that you can safely let the Xml object go out of scope after you
   * have retrieved the pointers you need from it.
   * @throw XmlError
   */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  static Glib::RefPtr<Xml> create(const std::string& filename,
                                  const Glib::ustring& root   = Glib::ustring(),
                                  const Glib::ustring& domain = Glib::ustring());
#else
  static Glib::RefPtr<Xml> create(const std::string& filename,
                                  const Glib::ustring& root,
                                  const Glib::ustring& domain,
                                  std::auto_ptr<XmlError>& error);
#endif

  /** Reads glade XML data from memory.
   * @throw XmlError
   * @see create()
   */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  static Glib::RefPtr<Xml> create_from_buffer(const char* buffer, int size,
                                              const Glib::ustring& root   = Glib::ustring(),
                                              const Glib::ustring& domain = Glib::ustring());
#else
  static Glib::RefPtr<Xml> create_from_buffer(const char* buffer, int size,
                                              const Glib::ustring& root,
                                              const Glib::ustring& domain,
                                              std::auto_ptr<XmlError>& error);
#endif

   std::string get_filename() const;
 
//void       glade_xml_signal_connect      (GladeXML *self,
//					  const char *handlername,
//					  GCallback func);
//void       glade_xml_signal_connect_data (GladeXML *self,
//					  const char *handlername,
//					  GCallback func,
//					  gpointer user_data);
//
//void       glade_xml_signal_autoconnect  (GladeXML *self);
//
//
//typedef void (*GladeXMLConnectFunc) (const gchar *handler_name,
//				     GObject *object,
//				     const gchar *signal_name,
//				     const gchar *signal_data,
//				     GObject *connect_object,
//				     gboolean after,
//				     gpointer user_data);
//
//
//void       glade_xml_signal_connect_full     (GladeXML *self,
//					      const gchar *handler_name,
//					      GladeXMLConnectFunc func,
//					      gpointer user_data);
//
//void       glade_xml_signal_autoconnect_full (GladeXML *self,
//					      GladeXMLConnectFunc func,
//					      gpointer user_data);
//
//
  /** Get a widget from the Glade file.
   * For instance:
   * @code
   * Gtk::Table* pTable = dynamic_cast<Gtk::Table*>(refXml->get_widget("mytable"));
   * @endcode
   * Note that you are responsible for deleting top-level widgets (windows and
   * dialogs). Other widgets are instantiated as managed so they will be
   * deleted automatically if you add them to a container.
   * @param name The name of the widget.
   * @return A pointer to the widget, or <tt>0</tt> on failure.
   */
  
  Gtk::Widget* get_widget(const Glib::ustring& name);

  /** More convenient way of getting a widget from the Glade file.
   * It allows for a shorter syntax with less repetition. For instance:
   * @code
   * Gtk::Table* pTable = 0;
   * refXml->get_widget("mytable", pTable);
   * @endcode
   * This method prints a warning message to the console if the widget
   * doesn't exist or has the wrong type, so you don't need to check that
   * manually.
   *
   * Note that you are responsible for deleting top-level widgets (windows and
   * dialogs) instantiated by the Xml object. Other widgets are instantiated as
   * managed so they will be deleted automatically if you add them to a
   * container widget.
   *
   * @param name The name of the widget.
   * @retval widget A pointer to the widget, or <tt>0</tt> on failure.
   * @return The value of @a widget.
   */
  template <class T_Widget> inline
  T_Widget* get_widget(const Glib::ustring& name, T_Widget*& widget)
  {
    // The dynamic_cast<> should never fail if get_widget_checked() succeeded.
    widget = dynamic_cast<T_Widget*>(this->get_widget_checked(name, T_Widget::get_base_type()));

    if(!widget)
      g_critical("Gnome::Glade::Xml::get_widget(): dynamic_cast<> failed.");
      
    return widget;
  }

  /** This provides a pointer to a widget whose details are specified in the Glade file, but which is implemented
   * by your own derived class. Your class must have a constructor like so:
   * @code
   * DerivedDialog::DerivedDialog(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade)
   * : Gtk::Dialog(cobject) //Calls the base class constructor
   * @endcode
   *
   * For instance:
   * @code
   * Gtk::DerivedBox* pBox = 0;
   * refXml->get_widget_derived("mybox", pBox);
   * @endcode
   *
   * @param name The name of the widget.
   * @retval widget A pointer to the widget, or <tt>0</tt> on failure.
   * @return The value of @a widget.
   */
  template <class T_Widget> inline
  T_Widget* get_widget_derived(const Glib::ustring& name, T_Widget*& widget)
  {
     // initialize input parameter
     widget = 0;
     
     // Get the widget from the glade file.
     typedef  typename T_Widget::BaseObjectType cwidget_type;
     cwidget_type* pCWidget = (cwidget_type*)get_cwidget(name);

     //The error was already reported by get_cwidget().
     if(!pCWidget)
       return 0;

     //Check whether there is already a C++ wrapper instance associated with this C instance:
     Glib::ObjectBase* pObjectBase = ObjectBase::_get_current_wrapper((GObject*)pCWidget);

     //If there is already a C++ instance, then return it again:
     if(pObjectBase)
     {
       widget = dynamic_cast<T_Widget*>( Glib::wrap((GtkWidget*)pCWidget) );
       //Newer, more spec-complaint, versions of g++ not resolve a specific wrap() function in a template.

       //The dynamic cast checks that it is of the correct type.
       //Somebody might be trying to call get_widget_derived() after already calling get_widget(),
       //or after already calling get_widget_derived() with a different derived C++ type.
       if(!widget)
        g_critical("Gnome::Glade::Xml::get_widget_derived(): dynamic_cast<> failed. An existing C++ instance, of a different type, seems to exist.");      
     }
     else
     {
       //Create a new C++ instance to wrap the existing C instance:
       
       //Set the output variable. We needed to do this because we can not template the return type.
       Glib::RefPtr<Gnome::Glade::Xml> refThis(this);
       refThis->reference(); //take a copy.
       widget = new T_Widget(pCWidget, refThis);
     }

     //We return it as well (we need the parameter as well, because C++ can not just template the return type.)
     return widget;
  }

  
  Glib::ListHandle<Gtk::Widget*> get_widget_prefix(const Glib::ustring& name);

  ///Take the widget from the glade-generated container and put it in another container.
  void reparent_widget(const Glib::ustring& name, Gtk::Container& container);

  
  std::string relative_file(const std::string& filename) const;

  
  static Glib::ustring get_widget_name(Gtk::Widget& widget);
  
  static Glib::RefPtr<Xml> get_widget_tree(Gtk::Widget& widget);

              
  /** Connect a Gtk::Button's clicked signal or a Gtk::MenuItem's activated signal to a slot.
   *
   * For instance:
   * @code
   * refXml->connect_button("button", sigc::mem_fun(*this, &ExampleWindow::on_button_clicked) );
   * @endcode
   *
   * @param name The name of the widget.
   * @param pslot The slot to connect to.
   */
  void connect_clicked(const Glib::ustring& name, const sigc::slot<void>& slot_);


///* interface for changing the custom widget handling */
//typedef GtkWidget *(* GladeXMLCustomWidgetHandler) (GladeXML *xml,
//						    gchar *func_name,
//						    gchar *name,
//						    gchar *string1,
//						    gchar *string2,
//						    gint int1,
//						    gint int2,
//						    gpointer user_data);

//void glade_set_custom_handler(GladeXMLCustomWidgetHandler handler,
//			      gpointer user_data);


protected:

  
  // TODO: Make sure this is actually invoked even with disabled vfuncs so
  // that glade creates gtkmm's GObjects.
  virtual GType lookup_type_vfunc(const Glib::ustring& classname);


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

protected:
  //GTK+ Virtual Functions (override these to change behaviour):
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

  //Default Signal Handlers::
#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


};

} // namespace Glade
} // namespace Gnome


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gnome::Glade::Xml
   */
  Glib::RefPtr<Gnome::Glade::Xml> wrap(GladeXML* object, bool take_copy = false);
}


#endif /* _LIBGLADEMM_XML_H */

