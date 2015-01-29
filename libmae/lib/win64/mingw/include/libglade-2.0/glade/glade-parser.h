/* -*- Mode: C; c-basic-offset: 4 -*-
 * libglade - a library for building interfaces from XML files at runtime
 * Copyright (C) 1998-2002  James Henstridge <james@daa.com.au>
 *
 * glade-parser.h: functions for parsing glade-2.0 files
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
 * License along with this library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA  02111-1307, USA.
 */

#ifndef GLADE_PARSER_H
#define GLADE_PARSER_H

#include <glib.h>
#include <gdk/gdk.h>

G_BEGIN_DECLS

typedef struct _GladeProperty GladeProperty;
struct _GladeProperty {
    gchar *name;
    gchar *value;
};

typedef struct _GladeSignalInfo GladeSignalInfo;
struct _GladeSignalInfo {
    gchar *name;
    gchar *handler;
    gchar *object; /* NULL if this isn't a connect_object signal */
    guint after : 1;
};

typedef struct _GladeAtkActionInfo GladeAtkActionInfo;
struct _GladeAtkActionInfo {
    gchar *action_name;
    gchar *description;
};

typedef struct _GladeAtkRelationInfo GladeAtkRelationInfo;
struct _GladeAtkRelationInfo {
    gchar *target;
    gchar *type;
};

typedef struct _GladeAccelInfo GladeAccelInfo;
struct _GladeAccelInfo {
    guint key;
    GdkModifierType modifiers;
    gchar *signal;
};

typedef struct _GladeWidgetInfo GladeWidgetInfo;
typedef struct _GladeChildInfo GladeChildInfo;

struct _GladeWidgetInfo {
    GladeWidgetInfo *parent;

    gchar *classname;
    gchar *name;

    GladeProperty *properties;
    guint n_properties;

    GladeProperty *atk_props;
    guint n_atk_props;

    GladeSignalInfo *signals;
    guint n_signals;
	
    GladeAtkActionInfo *atk_actions;
    guint n_atk_actions;

    GladeAtkRelationInfo *relations;
    guint n_relations;

    GladeAccelInfo *accels;
    guint n_accels;

    GladeChildInfo *children;
    guint n_children;
};

struct _GladeChildInfo {
    GladeProperty *properties;
    guint n_properties;

    GladeWidgetInfo *child;
    gchar *internal_child;
};

typedef struct _GladeInterface GladeInterface;
struct _GladeInterface {
    gchar **requires;
    guint n_requires;

    GladeWidgetInfo **toplevels;
    guint n_toplevels;

    GHashTable *names;

    GHashTable *strings;
};

/* the actual functions ... */
GladeInterface *glade_parser_parse_file   (const gchar *file,
					   const gchar *domain);
GladeInterface *glade_parser_parse_buffer (const gchar *buffer, gint len,
					   const gchar *domain);
void            glade_interface_destroy   (GladeInterface *interface);

void            glade_interface_dump      (GladeInterface *interface,
					   const gchar *filename);

G_END_DECLS

#endif
