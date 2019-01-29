#include"move.h"
#include"coordinates.h"


/*
MAP LEGEND:
-2 - opponent's in base
-1 - opponent's
0 - empty or opponent's
1 - my dot
2 - borders necessary
3 - part of a border
4 - dot in base
5 - mine inside
6 - noone's illegal

*/

int t[WIDTH*HEIGHT]={0};
frame my_frame;
frame opp_frame;
int opp_points=0;
int my_points=0;

static gboolean button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer data);
static gboolean create_map(GtkWidget *widget, cairo_t *cr, gpointer user_data);


int main(int argc, char *argv[])
{
	my_frame.num=0;
	opp_frame.num=0;
	GtkWidget *window;
  	GtkWidget *drawing_area;
  
  	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request (drawing_area, GAP*(WIDTH-1), GAP*(HEIGHT-1));

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
		vec pom=dot_clicked(event->x, event->y);
		if(verify_click(t, pom)==1)
		{
			move(t, &my_frame, pom.x+pom.y*WIDTH, &opp_points, &my_points);
    		gtk_widget_queue_draw(widget);
		}
	}
	return 1;
}

static gboolean create_map(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	for(int i=0; i<my_frame.num; i++)
	{
		cairo_set_source_rgb(cr, 0.9, 0.0, 0.0);
		cairo_set_line_width(cr, 5);
		cairo_move_to(cr, my_frame.line[i].x1*GAP, my_frame.line[i].y1*GAP);
        cairo_line_to(cr, my_frame.line[i].x2*GAP, my_frame.line[i].y2*GAP);
		cairo_stroke(cr);
	}
	for(int i=0; i<opp_frame.num; i++)
	{
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.9);
		cairo_set_line_width(cr, 5);
		cairo_move_to(cr, opp_frame.line[i].x1*GAP, opp_frame.line[i].y1*GAP);
        cairo_line_to(cr, opp_frame.line[i].x2*GAP, opp_frame.line[i].y2*GAP);
		cairo_stroke(cr);
	} 
	cairo_translate(cr, 0, GAP);
	for(int i=1; i<HEIGHT-1; i++)
	{
		for(int j=1; j<WIDTH-1; j++)
		{
			if(t[i*WIDTH+j]<0)
			{
				cairo_set_source_rgb(cr, 0, 0, 1.0);
			}
			else
			{
				if(t[i*WIDTH+j]>0 && t[i*WIDTH+j]<6)
				{
					cairo_set_source_rgb(cr, 1.0, 0, 0);
				}
				else
				{
					if(t[i*WIDTH+j]==6)
					{
						cairo_set_source_rgb(cr, 0.512, 0.512, 0.512);
					}
					else
					{
					cairo_set_source_rgb(cr, 0, 0, 0);
					}				
				}
			}
			cairo_translate(cr, GAP, 0);
			cairo_arc(cr, 0, 0, RADIOUS, 0, 2 * G_PI);
		 	cairo_stroke_preserve(cr);
		 	cairo_fill(cr);
		}
		cairo_translate(cr, -GAP*(WIDTH-2), GAP);
	}
	return TRUE;    
}
