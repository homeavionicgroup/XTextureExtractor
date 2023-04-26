// ---------------------------------------------------------------------
//
// XTextureExtractor
//
// Copyright (C) 2018-2022 Wayne Piekarski
// wayne@tinmith.net http://tinmith.net/wayne
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// ---------------------------------------------------------------------

#pragma once

// XPLM version #defines are in the vcproj file
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPLMPlanes.h"
#include "XPLMDataAccess.h"
#include "XPLMPlugin.h"
#include <string.h>
#include <stdio.h>
#if IBM
#include <windows.h>
#endif
#if LIN
#include <GL/gl.h>
#elif APL
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#ifndef XPLM301
#error This is made to be compiled against the XPLM301 SDK, this macro is also not set in the vcxproj Debug mode flags
#endif

static char __log_printf_buffer[4096];
#define log_printf(fmt, ...) if(true) snprintf(__log_printf_buffer, 4096, "XTextureExtractor-%s: " fmt, PLUGIN_VERSION, ##__VA_ARGS__), XPLMDebugString(__log_printf_buffer)

#define COCKPIT_MAX_WINDOWS 20
#define TCP_PLUGIN_PORT    "52500"
#define MAX_TEXTURE_WIDTH  4096
#define MAX_TEXTURE_HEIGHT 4096
#define TCP_INTRO_HEADER   4096
#define TCP_PROTOCOL_VERSION "XTEv3"
#define PLUGIN_VERSION     "v3.3"
#if APL
// OSX does not support 10mb buffers
#define TCP_SEND_BUFFER    5*1024*1024
#else
#define TCP_SEND_BUFFER    10*1024*1024
#endif
// Windows defines MAX_PATH as 260 and https://developer.x-plane.com/sdk/XPLMGetNthAircraftModel/ defines filename as 256 and path as 512
// Define a safe path length which we can be sure exceeds all possible cases
#define SAFE_PATH_LENGTH   4096
// TODO: The code is a mess of unchecked char strings, which should be replaced with std::string or checked snprintf

extern void start_networking_thread(void);
extern unsigned char *texture_pointer;
extern GLint cockpit_texture_id;
extern GLint cockpit_texture_width;
extern GLint cockpit_texture_height;
extern int   cockpit_texture_seq;

extern char cockpit_aircraft_name[];
extern char cockpit_aircraft_filename[];
extern int cockpit_window_limit;
extern char _g_window_name[COCKPIT_MAX_WINDOWS][256]; // titles of each window
extern int _g_texture_lbrt[COCKPIT_MAX_WINDOWS][4]; // left, bottom, right, top
