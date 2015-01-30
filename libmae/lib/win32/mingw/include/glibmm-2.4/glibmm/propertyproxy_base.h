// -*- c++ -*-
#ifndef _GLIBMM_PROPERTYPROXY_BASE_H
#define _GLIBMM_PROPERTYPROXY_BASE_H

/* propertyproxy_base.h
 *
 * Copyright 2002 The gtkmm Development Team
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

#include <glibmmconfig.h>
#include <glibmm/value.h>
#include <glibmm/signalproxy.h>

namespace Glib
{

#ifdef GLIBMM_PROPERTIES_ENABLED

class ObjectBase;

/// Use the connect() method, with sigc::ptr_fun() or sig::mem_fun() to connect signals to signal handlers.
class SignalProxyProperty : public SignalProxyBase
{
public:
  friend class PropertyProxy_Base;

  SignalProxyProperty(Glib::ObjectBase* obj, const gchar* property_name);
  ~SignalProxyProperty();

  typedef sigc::slot<void> SlotType;
  sigc::connection connect(const SlotType& sl);

protected:

  const char* property_name_; //Should be a static string literal.

private:
  SignalProxyProperty& operator=(const SignalProxyProperty&); // not implemented
};


class PropertyProxy_Base
{
public:
  PropertyProxy_Base(ObjectBase* obj, const char* property_name);
  PropertyProxy_Base(const PropertyProxy_Base& other);

  ///This signal will be emitted when the property changes.
  SignalProxyProperty signal_changed();

  ObjectBase* get_object()   const { return obj_; }
  const char* get_name() const { return property_name_; }

protected:
  void set_property_(const Glib::ValueBase& value);
  void get_property_(Glib::ValueBase& value) const;
  void reset_property_();

  ObjectBase* obj_; //The C++ wrapper instance of which this PropertyProxy is a member.

  const char* property_name_; //Should be a static string literal.

private:
  //Declared as private, but not implemented to prevent any automatically generated implementation.
  PropertyProxy_Base& operator=(const PropertyProxy_Base&);
};

#endif //GLIBMM_PROPERTIES_ENABLED

#ifndef DOXYGEN_SHOULD_SKIP_THIS

class SignalProxyProperty;

/** PropertyProxyConnectionNode is a connection node for use with SignalProxyProperty.
  * It's like ProxyConnectionNode, but it contains the property name too.
  * This is not public API.
  */
class PropertyProxyConnectionNode : public SignalProxyConnectionNode
{
public:
  friend class SignalProxyProperty;

  PropertyProxyConnectionNode(const sigc::slot_base& slot, GObject* gobject);

  static void callback(GObject* object, GParamSpec* pspec, gpointer data);
};

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} // namespace Glib



#endif /* _GLIBMM_PROPERTYPROXY_BASE_H */

