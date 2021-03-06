/*
 *  User interface top include file
 *  Copyright (C) 2007 Andreas Öman
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UI_H__
#define UI_H__

LIST_HEAD(ui_list,  ui);
LIST_HEAD(uii_list, uii);

struct prop;

/**
 * User interface instance
 */
typedef struct uii {

  LIST_ENTRY(uii) uii_link;
  
  struct ui *uii_ui;

  struct prop *uii_prop;

} uii_t;


/**
 * User interface class
 */
typedef struct ui {

  int ui_flags;
#define UI_SINGLETON  0x1 // Only one instance may run
#define UI_MAINTHREAD 0x2 // Must execute in main thread, implies UI_SINGLETON

  const char *ui_title;

  LIST_ENTRY(ui) ui_link;

  int ui_num_instances;

  int (*ui_start)(struct ui *ui, struct prop *root, 
		  int argc, char **argv, int primary);

  void (*ui_dispatch_event)(uii_t *uii, struct event *e);

  void (*ui_stop)(uii_t *uii);

} ui_t;


/**
 *
 */
int ui_start(int argc, const char *argv[], const char *argv0);

void uii_register(uii_t *uii, int primary);

int ui_shutdown(void);

void ui_primary_event(struct event *e);


/**
 * Video modes
 */
#define UI_VIDEO_MODE_NATIVEp50  0x1
#define UI_VIDEO_MODE_NATIVEp60  0x2
#define UI_VIDEO_MODE_720p50     0x4
#define UI_VIDEO_MODE_720p60     0x8
#define UI_VIDEO_MODE_1080p50    0x10
#define UI_VIDEO_MODE_1080p60    0x20


#endif /* UI_H__ */
