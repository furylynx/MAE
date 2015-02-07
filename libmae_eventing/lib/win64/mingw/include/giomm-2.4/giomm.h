#ifndef _GIOMM_H
#define _GIOMM_H

/* 
 * Copyright (C) 2007 The giomm Development Team
 * 
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

#include <giomm/appinfo.h>
#include <giomm/asyncresult.h>
#include <giomm/bufferedinputstream.h>
#include <giomm/bufferedoutputstream.h>
#include <giomm/cancellable.h>
#include <giomm/contenttype.h>
#include <giomm/datainputstream.h>
#include <giomm/dataoutputstream.h>
#ifndef G_OS_WIN32
# include <giomm/desktopappinfo.h>
#endif
#include <giomm/drive.h>
#include <giomm/emblemedicon.h>
#include <giomm/emblem.h>
#include <giomm/enums.h>
#include <giomm/error.h>
#include <giomm/fileattributeinfo.h>
#include <giomm/fileattributeinfolist.h>
#include <giomm/fileenumerator.h>
#include <giomm/file.h>
#include <giomm/fileicon.h>
#include <giomm/fileinfo.h>
#include <giomm/fileinputstream.h>
#include <giomm/fileiostream.h>
#include <giomm/filemonitor.h>
#include <giomm/filenamecompleter.h>
#include <giomm/fileoutputstream.h>
#include <giomm/filterinputstream.h>
#include <giomm/filteroutputstream.h>
#include <giomm/icon.h>
#include <giomm/inetaddress.h>
#include <giomm/inetsocketaddress.h>
#include <giomm/init.h>
#include <giomm/initable.h>
#include <giomm/inputstream.h>
#include <giomm/iostream.h>
#include <giomm/loadableicon.h>
#include <giomm/memoryinputstream.h>
#include <giomm/memoryoutputstream.h>
#include <giomm/mount.h>
#include <giomm/mountoperation.h>
#include <giomm/networkaddress.h>
#include <giomm/networkservice.h>
#include <giomm/outputstream.h>
#include <giomm/resolver.h>
#include <giomm/seekable.h>
#include <giomm/socket.h>
#include <giomm/socketaddress.h>
#include <giomm/socketaddressenumerator.h>
#include <giomm/socketclient.h>
#include <giomm/socketconnectable.h>
#include <giomm/socketconnection.h>
#include <giomm/srvtarget.h>
#include <giomm/tcpconnection.h>
#include <giomm/themedicon.h>
#ifndef G_OS_WIN32
# include <giomm/unixconnection.h>
# include <giomm/unixinputstream.h>
# include <giomm/unixoutputstream.h>
#endif
#include <giomm/volume.h>
#include <giomm/volumemonitor.h>

#endif /* #ifndef _GIOMM_H */

