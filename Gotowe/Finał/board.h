#include"move.h"
#include"coordinates.h"
#include"communication.h"

/*
MAP LEGEND
0 - empty dot
1 - occupied dot
2 - dot that needs borders
3 - dat that is a part of a border
4 - opponent's dot in my base
5 - my dot inside my base
6 - my dot inside opponents base
7 - noone's dot inside base
*/

gboolean button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer data);
gboolean create_map(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void new_game(_Bool isA);
int opponents_move(gpointer data);
void points_update(void);
void new_game_window(GtkWidget *widget, gpointer data);
gboolean close_main_window(GtkWidget *widget, gpointer data);
gboolean close_small_window(GtkWidget *widget, gpointer data);
void main_window(int size);
void close_main_window_alert();
void check_version(int sign);
void end_game_window(void);
_Bool the_end(void);
