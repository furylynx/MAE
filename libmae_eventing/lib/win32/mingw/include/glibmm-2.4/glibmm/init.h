// -*- c++ -*-
#ifndef _GLIBMM_INIT_H
#define _GLIBMM_INIT_H

/* $Id$ */

/* Copyright (C) 2002 The gtkmm Development Team
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

namespace Glib
{

/** Initialize glibmm.
 * You may call this more than once.
 * You do not need to call this if you are using Glib::MainLoop or Gtk::Main,
 * because they call it for you.
 */
void init();

} // namespace Glib



#endif /* _GLIBMM_INIT_H */

