#include"board.h"

int map[WIDTH_MAX*HEIGHT_MAX]={0};
int WIDTH, HEIGHT;
frame my_frame;
frame opp_frame;
int opp_points=0;
int my_points=0;
int version;
_Bool my_turn=1;
_Bool small_window_opened=0;
_Bool main_window_opened=0;
GtkWidget *mypoints_info;
GtkWidget *opppoints_info;
GtkWidget *window;

gboolean button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if(my_turn==0 || small_window_opened==1)
    {
        return FALSE;
    }
	if (event->button == GDK_BUTTON_PRIMARY)
    {
		vec pom=dot_clicked(event->x, event->y);
		if(verify_click(map, pom, WIDTH, HEIGHT)==1)
		{
			move(map, &my_frame, pom.x+pom.y*WIDTH, &opp_points, &my_points, WIDTH, HEIGHT);
			send_info(pom.x+pom.y*WIDTH);
    		gtk_widget_queue_draw(widget);
    		if(the_end()==1)
    		{
                end_game_window();
    		}
    		my_turn=0;
		}
	}
	return 1;
}

gboolean create_map(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    points_update();
	for(int i=0; i<my_frame.num; i++)
	{
		cairo_set_source_rgb(cr, 0.9, 0.0, 0.0);
		cairo_set_line_width(cr, (double)(RADIOUS)/2.0);
		cairo_move_to(cr, my_frame.line[i].x1*GAP, my_frame.line[i].y1*GAP);
        cairo_line_to(cr, my_frame.line[i].x2*GAP, my_frame.line[i].y2*GAP);
		cairo_stroke(cr);
	}
	for(int i=0; i<opp_frame.num; i++)
	{
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.9);
		cairo_set_line_width(cr, (double)(RADIOUS)/2.0);
		cairo_move_to(cr, opp_frame.line[i].x1*GAP, opp_frame.line[i].y1*GAP);
        cairo_line_to(cr, opp_frame.line[i].x2*GAP, opp_frame.line[i].y2*GAP);
		cairo_stroke(cr);
	}
	cairo_translate(cr, 0, GAP);
	for(int i=1; i<HEIGHT-1; i++)
	{
		for(int j=1; j<WIDTH-1; j++)
		{
			if(map[i*WIDTH+j]<0 && map[i*WIDTH+j]>-7)
			{
				cairo_set_source_rgb(cr, 0, 0, 1.0);
			}
			else
			{
				if(map[i*WIDTH+j]>0 && map[i*WIDTH+j]<7)
				{
					cairo_set_source_rgb(cr, 1.0, 0, 0);
				}
				else
				{
					if(map[i*WIDTH+j]==7 || map[i*WIDTH+j]==-7)
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

void new_game(_Bool isA)
{
    for(int i=0; i<HEIGHT; i++)
    {
        for(int j=0; j<WIDTH; j++)
        {
            map[i*WIDTH+j]=0;
        }
    }
    if(isA==0)
    {
        my_turn=0;
    }
    else
    {
        my_turn=1;
    }
	my_frame.num=0;
	opp_frame.num=0;
	my_points=0;
	opp_points=0;
}

int opponents_move(gpointer data)
{
    if(my_turn==1)
    {
        return 1;
    }
    int opp;
    get_info(&opp);
    if(opp>=0)
    {
        for(int i=0; i<HEIGHT; i++)
        {
            for(int j=0; j<WIDTH; j++)
            {
                map[i*WIDTH+j]=-map[i*WIDTH+j];
            }
        }
        move(map, &opp_frame, opp, &my_points, &opp_points, WIDTH, HEIGHT);
        for(int i=0; i<HEIGHT; i++)
        {
            for(int j=0; j<WIDTH; j++)
            {
                map[i*WIDTH+j]=-map[i*WIDTH+j];
            }
        }
        gtk_widget_queue_draw(GTK_WIDGET(data));
        if(the_end()==1)
        {
            end_game_window();
        }
        my_turn=1;
    }
    return 1;
}

void points_update(void)
{
    char text[30];
    sprintf(text, "My score: %d", my_points);
    gtk_label_set_text(GTK_LABEL(mypoints_info), text);
    sprintf(text, "Opponent's score: %d", opp_points);
    gtk_label_set_text(GTK_LABEL(opppoints_info), text);
}

void new_game_window(GtkWidget *widget, gpointer data)
{
    if(small_window_opened==1)
    {
        return;
    }
    small_window_opened=1;
    GtkWidget *small_window;
    GtkWidget *no_button=gtk_button_new_with_label("No"), *yes_button=gtk_button_new_with_label("Yes");
    GtkWidget *question=gtk_label_new("In order to start a new game you have to surrender first.\nDo you want to surrender and start a new game?");
    GtkWidget *ver_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0), *hor_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(ver_box), question, TRUE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(ver_box), hor_box, TRUE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(hor_box), no_button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hor_box), yes_button, TRUE, TRUE, 0);
    small_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(small_window), ver_box);
    gtk_window_set_title(GTK_WINDOW(small_window), "Are you sure?");
    gtk_window_set_position(GTK_WINDOW(small_window),GTK_WIN_POS_CENTER);

    g_signal_connect(G_OBJECT(yes_button), "clicked", G_CALLBACK(close_main_window), small_window);
	g_signal_connect(G_OBJECT(no_button), "clicked", G_CALLBACK(close_small_window), small_window);
    gtk_widget_show_all(small_window);
}

gboolean close_main_window(GtkWidget *widget, gpointer data)
{
    main_window_opened=0;
    small_window_opened=0;
    gtk_window_close(data);
    gtk_window_close(GTK_WINDOW(window));
    return TRUE;
}

gboolean close_small_window(GtkWidget *widget, gpointer data)
{
    small_window_opened=0;
    gtk_window_close(GTK_WINDOW(data));
    return TRUE;
}

void main_window(int size)
{
    if(size==1 || size==4)
    {
        WIDTH=14;
        HEIGHT=11;
        version='S';
    }
    else
    {
        if(size==2 || size==5)
        {
            WIDTH=18;
            HEIGHT=14;
            version='M';
        }
        else
        {
            WIDTH=22;
            HEIGHT=17;
            version='B';
        }
    }
    GtkWidget *drawing_area;
	GtkWidget *layout;
	GtkWidget *newgame_button;
	GtkWidget *close_button;
	GtkWidget *buttons;
	GtkWidget *vert_line;
	GtkWidget *hor_line;
	new_game(size<4);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	drawing_area = gtk_drawing_area_new();
	layout=gtk_grid_new();
	buttons=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	vert_line=gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	hor_line=gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	newgame_button=gtk_button_new_with_label("New game");
	close_button=gtk_button_new_with_label("Close game");
	mypoints_info=gtk_label_new("My score: 0");
	opppoints_info=gtk_label_new("Opponent's score: 0");

	gtk_widget_set_size_request (drawing_area, GAP*(WIDTH-1), GAP*(HEIGHT-1));
	gtk_grid_attach(GTK_GRID(layout), drawing_area, 0, 0, WIDTH, HEIGHT);
	gtk_box_pack_start(GTK_BOX(buttons), newgame_button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(buttons), close_button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(buttons), hor_line, FALSE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(buttons), mypoints_info, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(buttons), opppoints_info, FALSE, TRUE, 0);
	gtk_grid_attach(GTK_GRID(layout), vert_line, WIDTH, 0, 1, HEIGHT);
	gtk_grid_attach(GTK_GRID(layout), buttons, WIDTH+1, 0, 1, HEIGHT);

  	gtk_container_add(GTK_CONTAINER(window), layout);

	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(create_map), NULL);
	g_signal_connect(G_OBJECT(newgame_button), "clicked", G_CALLBACK(new_game_window), NULL);
	g_signal_connect(G_OBJECT(close_button), "clicked", G_CALLBACK(close_main_window_alert), NULL);
	g_signal_connect (window, "button-press-event", G_CALLBACK (button_press_event), NULL);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
 	if(size<4)
 	{
        gtk_window_set_title(GTK_WINDOW(window), "Dots (player A)");
    }
    else
    {
        gtk_window_set_title(GTK_WINDOW(window), "Dots (player B)");
    }
 	g_timeout_add(100, opponents_move, window);

 	gtk_widget_show_all(window);
}

void close_main_window_alert()
{
    if(small_window_opened==1)
    {
        return;
    }
    small_window_opened=1;
    GtkWidget *small_window;
    GtkWidget *no_button=gtk_button_new_with_label("No"), *yes_button=gtk_button_new_with_label("Yes");
    GtkWidget *question=gtk_label_new("You will surrender and close the game.\nDo you want to continue?");
    GtkWidget *ver_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0), *hor_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(ver_box), question, TRUE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(ver_box), hor_box, TRUE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(hor_box), no_button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hor_box), yes_button, TRUE, TRUE, 0);
    small_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(small_window), ver_box);
    gtk_window_set_title(GTK_WINDOW(small_window), "Are you sure?");
    gtk_window_set_position(GTK_WINDOW(small_window),GTK_WIN_POS_CENTER);

    g_signal_connect(G_OBJECT(yes_button), "clicked", G_CALLBACK(gtk_main_quit), small_window);
	g_signal_connect(G_OBJECT(no_button), "clicked", G_CALLBACK(close_small_window), small_window);
    gtk_widget_show_all(small_window);
}

void check_version(int sign)
{
    if(sign!=version)
    {
        printf("Wrong versions of games. Error\n");
        exit(1);
    }
}

_Bool the_end(void)
{
    for(int i=1; i<HEIGHT-1; i++)
    {
        for(int j=1; j<WIDTH-1; j++)
        {
            if(map[i*WIDTH+j]==0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void end_game_window(void)
{
    small_window_opened=1;
    GtkWidget *small_window;
    GtkWidget *Ok=gtk_button_new_with_label("Ok");
    GtkWidget *ver_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0), *hor_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(ver_box), hor_box, TRUE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(ver_box), Ok, TRUE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(hor_box), opppoints_info, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(hor_box), mypoints_info, TRUE, TRUE, 5);
    small_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(small_window), 200, 200);
    gtk_container_add(GTK_CONTAINER(small_window), ver_box);
    if(opp_points>my_points)
    {
        gtk_window_set_title(GTK_WINDOW(small_window), "You lost!");
    }
    else
    {
        if(opp_points<my_points)
        {
            gtk_window_set_title(GTK_WINDOW(small_window), "You won!");
        }
        else
        {
            gtk_window_set_title(GTK_WINDOW(small_window), "Draw!");
        }
    }

    gtk_window_set_position(GTK_WINDOW(small_window),GTK_WIN_POS_CENTER);

    g_signal_connect(G_OBJECT(Ok), "clicked", G_CALLBACK(close_main_window), small_window);
    gtk_widget_show_all(small_window);
}
