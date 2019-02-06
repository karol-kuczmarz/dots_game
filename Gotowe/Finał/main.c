#include"board.h"

_Bool isa=0;

GtkWidget *small_board;
GtkWidget *medium_board;
GtkWidget *big_board;

void i_main_window(GtkWidget *widget);

int main(int argc, char *argv[])
{
    fifo_init(argc, argv);

    if(argv[1][0]=='A')
    {
        isa=1;
    }

  	gtk_init(&argc, &argv);

  	GtkWidget *start_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *welcome=gtk_label_new("Choose board size:");
    small_board=gtk_button_new_with_label("Small board");
    medium_board=gtk_button_new_with_label("Medium board");
    big_board=gtk_button_new_with_label("Big board");

    gtk_window_set_position(GTK_WINDOW(start_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(start_window), 300, 150);
    if(argv[1][0]=='A')
    {
        gtk_window_set_title(GTK_WINDOW(start_window), "Welcome! (player A)");
    }
    else
    {
        gtk_window_set_title(GTK_WINDOW(start_window), "Welcome! (player B)");
    }
    gtk_box_pack_start(GTK_BOX(box), welcome, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(box), small_board, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(box), medium_board, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(box), big_board, TRUE, TRUE, 3);
    gtk_container_add(GTK_CONTAINER(start_window), box);
    g_signal_connect(G_OBJECT(small_board), "clicked", G_CALLBACK(i_main_window), NULL);
    g_signal_connect(G_OBJECT(medium_board), "clicked", G_CALLBACK(i_main_window), NULL);
    g_signal_connect(G_OBJECT(big_board), "clicked", G_CALLBACK(i_main_window), NULL);
    g_signal_connect(G_OBJECT(start_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);


    gtk_widget_show_all(start_window);

	gtk_main();

    return 0;
}

void i_main_window(GtkWidget *widget)
{
    if(isa==1)
    {
        if(widget==small_board)
        {
            main_window(1);
        }
        else
        {
            if(widget==medium_board)
            {
                main_window(2);
            }
            else
            {
                main_window(3);
            }
        }
    }
    else
    {
        if(widget==small_board)
        {
            main_window(4);
        }
        else
        {
            if(widget==medium_board)
            {
                main_window(5);
            }
            else
            {
                main_window(6);
            }
        }
    }
}
