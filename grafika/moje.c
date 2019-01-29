#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>


static gboolean button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer data);
static gboolean create_map(GtkWidget *widget, cairo_t *cr, gpointer user_data);

int main (int argc, char *argv[])
{
  	GtkWidget *window;
  	GtkWidget *drawing_area;
  
  	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request (drawing_area, 200, 200);
  	gtk_container_add(GTK_CONTAINER(window), drawing_area);

	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(create_map), NULL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect (window, "button-press-event", G_CALLBACK (button_press_event), NULL);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
 	gtk_window_set_title(GTK_WINDOW(window), "Clicking");

 	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

static gboolean button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	if (event->button == GDK_BUTTON_PRIMARY)
    {
      printf("%lf %lf \n", event->x, event->y);
    }
	gtk_widget_queue_draw(widget);
	return 1;
}

static gboolean create_map(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	cairo_set_source_rgb(cr, 0.9, 0.0, 0.0);
	cairo_set_line_width(cr, 5);
	cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, 30, 30);
	cairo_stroke(cr);
	return TRUE;    
}
