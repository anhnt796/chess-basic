#include <gtk/gtk.h>
#include <stdio.h>
#include "int2utf8.h"
#include "pieceConst.h"
#include "string.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#include "controller.h"

static gboolean button_pressed(GtkWidget *, GdkEventButton *, GtkLabel *[][8]);
static void play(GtkWidget *, GtkWidget *);
static void backToMain(GtkWidget *, GtkWidget *);
static void create_sv(GtkWindow *, gchar *);
static void connect_sv(GtkWindow *, gchar *);
static void updateGUI();

/*Css*/
GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
/*------*/
static const GdkRGBA green = {0.5899, 0.8867, 0.3906, 1};
static const GdkRGBA dbrown = {0.8242, 0.5508, 0.2773, 1};
static const GdkRGBA lbrown = {0.9805, 0.8047, 0.6094, 1};
GdkColor prevColor;
GtkWidget *table, *prevEventbox, *hpane, *infogrid, *textview, *scroll_win;
GtkTextBuffer *buffer;
GtkTextIter txtiter;
GtkLabel *currentPlayer, *row_label, *col_label;
/*container for the labels of the gui board*/
GtkLabel *labelBoard[8][8];

extern int makemove(int player, int *move, int board[][8]);

/*initBoard method is in chess.c*/
extern void initBoard(int tmpBoard[][8]);
extern void resetPassantArrays(void);
extern int kingUnderAttack(int player, int board[][8]);
extern int hasMovement(int player, int board[][8]);
extern decoded getresults(char *input);

int main(int argc, char *argv[]) {
    /*fill the board array with pieces*/
    initBoard(board);
    resetPassantArrays();
    GtkWidget *window, *eventbox;
    GtkLabel *label;
    /* Secure glib */
    if( ! g_thread_supported() )
        g_thread_init( NULL );

    /* Secure gtk */
    gdk_threads_init();

    /* Obtain gtk's global lock */
    gdk_threads_enter();

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Chess board");
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);
    gtk_widget_set_size_request(window, 680, 350);
    //table = gtk_grid_new (8,8,TRUE);
    table = gtk_grid_new();
    
    
    /*one is larger to make the squares wider*/
    char *pieces[64] = {"♜", "♞", "♝", "♛", "♚", "♝", "♞", "♜",
                        "♟", "♟", "♟", "♟", "♟", "♟", "♟", "♟",
                        "", "", "", "", "", "", "", "",
                        "", "", "", "", "", "", "", "",
                        "", "", "", "", "", "", "", "",
                        "", "", "", "", "", "", "", "",
                        "♙", "♙", "♙", "♙", "♙", "♙", "♙", "♙",
                        "♖", "♘", "♗", "♕", "♔", "♗", "♘", "♖"};
    int i, j;
    int p = 0;
    int oddCol = 1;
    int oddRow = 1;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            label = (GtkLabel *) gtk_label_new(pieces[p]);
            /* set the size of the label to avoid that they are resized when there is no piece in the row */
            gtk_widget_set_size_request((GtkWidget *) label, 56, 56);
            /*put the label into the container for easy access when mocing pieces*/
            labelBoard[i][j] = label;
            eventbox = gtk_event_box_new();
            if (oddRow) {
                if (oddCol) {
                    gtk_widget_override_background_color(eventbox, GTK_STATE_NORMAL, &lbrown);
                    oddCol = 0;
                } else {
                    gtk_widget_override_background_color(eventbox, GTK_STATE_NORMAL, &dbrown);
                    oddCol = 1;
                }
            } else {
                if (oddCol) {
                    gtk_widget_override_background_color(eventbox, GTK_STATE_NORMAL, &dbrown);
                    oddCol = 0;
                } else {
                    gtk_widget_override_background_color(eventbox, GTK_STATE_NORMAL, &lbrown);
                    oddCol = 1;
                }
            }

            gtk_event_box_set_above_child(GTK_EVENT_BOX(eventbox), FALSE);

            gtk_widget_override_font((GtkWidget *) label, pango_font_description_from_string(
                    "Serif 36"));
            /*put label into eventbox*/
            gtk_container_add(GTK_CONTAINER(eventbox), (GtkWidget *) label);
            /*put eventbox into table*/
            gtk_grid_attach((GtkGrid *) table, eventbox, j + 1, i, 1, 1);


            g_signal_connect(G_OBJECT(eventbox), "button_press_event",
                             G_CALLBACK(button_pressed), (gpointer) labelBoard);

            gtk_widget_set_events(eventbox, GDK_BUTTON_PRESS_MASK);
            /** Dont need widget_realize
             * connect to a signal that will be called 
             * after the widget is realized automatically
             * in g_signal_connect(window)
             * gtk_widget_realize(eventbox);
             */
            p++;
        }
        oddRow = !oddRow;
    }

    /* add square row names */
    sprintf(mnum, "%s", "`");
    for (i = 1; i < 9; i++) {
        mnum[0]++; // mnums first char becomes 'a', then 'b', then 'c' etc.
        label = (GtkLabel *) gtk_label_new(mnum);
        gtk_widget_set_size_request((GtkWidget *) label, 0, 30);
        gtk_grid_attach((GtkGrid *) table, (GtkWidget *) label, i, 9, 1, 1);
    }
    i = 8;
    for (j = 0; j < 8; j++) {
        sprintf(mnum, "%d", i--);
        label = (GtkLabel *) gtk_label_new(mnum);
        gtk_widget_set_size_request((GtkWidget *) label, 30, 0);
        gtk_grid_attach((GtkGrid *) table, (GtkWidget *) label, 0, j, 1, 1);
    }

    /*make a horizontal pane*/
    //hpane = gtk_grid_new(1,2,TRUE);
    hpane = gtk_grid_new();
    /*add the table to the horizontal pane*/
    gtk_grid_attach((GtkGrid *) hpane, table, 0, 0, 1, 1);

    /** create a vertical grid containing game info.
     * the first  widget is shows the current player
     * and the second widget is a textview showing last moves
     */
    infogrid = gtk_grid_new();
    textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(textview), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(textview), 10);

    /** add game info textview to the scroll window
     * and the scroll window and current player label to infogrid.
     * Finally add the info grid to the hpane, right of the chess board.
     */
    scroll_win = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scroll_win, 250, 415);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_win),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(scroll_win), textview);
    gtk_grid_attach((GtkGrid *) infogrid, (GtkWidget *) scroll_win, 0, 1, 1, 1);
    currentPlayer = (GtkLabel *) gtk_label_new("Current player: White");
    gtk_grid_attach((GtkGrid *) infogrid, (GtkWidget *) currentPlayer, 0, 0, 1, 1);
    gtk_grid_attach((GtkGrid *) hpane, (GtkWidget *) infogrid, 1, 0, 1, 1);

    /* create main window */
    GtkWidget *window_main;
    GtkBuilder * builder;
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"builder.xml",NULL);
    window_main = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
    g_signal_connect(window_main,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    GtkWidget *button;

    //play
    button = gtk_builder_get_object(builder,"btn_play");
    g_signal_connect(button,"clicked",G_CALLBACK(play),window);
    
    // create server
    button = gtk_builder_get_object(builder,"btn_create_sv");
    g_signal_connect(button,"clicked",G_CALLBACK(create_sv),"da tao server");

    // connect server
    button = gtk_builder_get_object(builder,"btn_connect_sv");
    g_signal_connect(button,"clicked",G_CALLBACK(connect_sv),"Nhap IP");

    //quit
    button = gtk_builder_get_object(builder,"btn_quit");
    g_signal_connect(button,"clicked",G_CALLBACK(gtk_main_quit),NULL);

    /*add table to window*/
    gtk_container_add(GTK_CONTAINER(window), hpane);
    gtk_widget_show(window_main);
    g_signal_connect(G_OBJECT(window), "destroy",
                             G_CALLBACK(backToMain),window_main);
    //css
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar* home ="style.css";
    
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref (provider);
   
    printf("day la socket %d\n",(int)sockfd );

    gtk_main();
    close(sockfd);
    /* Release gtk's global lock */
    gdk_threads_leave();

    return 0;
}

static void backToMain(GtkWidget *widget, GtkWidget *window_main) {
    g_print("Main menu!\n");
    gtk_widget_show_all(window_main);
}

static void create_sv(GtkWindow *parent, gchar *message) {
    GtkWidget *dialog, *label, *content_area;
    GtkDialogFlags flags;

    flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Message",parent, flags,"OK",
        GTK_RESPONSE_NONE,NULL);

    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new(message);
    g_signal_connect_swapped(dialog,"response", G_CALLBACK(gtk_widget_destroy),dialog);
	gtk_container_add(GTK_CONTAINER(content_area),label);
	make_server();
	isServer = 1;
	player_color = 0;
	gtk_widget_show_all(dialog);
}


static void connect_sv(GtkWindow *parent, gchar *message) {
    GtkWidget *dialog, *label, *content_area, *text_entry, *button;
    GtkDialogFlags flags;
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;    

    dialog = gtk_dialog_new();
    //player_color = 1;
    gtk_window_set_title(GTK_WINDOW(dialog),"Connect to a server... ");
    printf("abc/n");
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new(message);
    text_entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY (text_entry),"127.0.0.1");
    g_signal_connect_swapped(dialog,"response", G_CALLBACK(gtk_widget_destroy),dialog);

    button = gtk_button_new_with_label("OK");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(make_client),gtk_entry_get_text(GTK_ENTRY (text_entry)));
	gtk_container_add(GTK_CONTAINER(content_area),label);
	gtk_container_add(GTK_CONTAINER(content_area),text_entry);
	gtk_container_add(GTK_CONTAINER(content_area),button);
	isServer = 0;
	//player_color = 1;
    //player_color = 0;    
	gtk_widget_show_all(dialog);
}

int drawGuiBoard(GtkLabel *labels[][8], int cliBoard[][8]) {
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            gtk_label_set_text(labels[i][j], convertClipieceToGuiPiece(cliBoard[i][j]));
        }
    }
    printf("draw\n");
    return 0;
}

void long_algebraic_notation(char *note, int *move, int board[][8]) {
    int piece = board[move[1]][move[0]];
    note[0] = ' ';
    if (piece == wKnight || piece == bKnight) {
        note[1] = 'N';
    } else if (piece == wBishop || piece == bBishop) {
        note[1] = 'B';
    } else if (piece == wRook || piece == bRook) {
        note[1] = 'R';
    } else if (piece == wQueen || piece == bQueen) {
        note[1] = 'Q';
    } else if (piece == wKing || piece == bKing) {
        note[1] = 'K';
    }
    note[2] = move[0] + 97;
    note[3] = 8 - move[1] + 48;
    note[4] = 45;
    note[5] = move[2] + 97;
    note[6] = 8 - move[3] + 48;
    note[7] = 0;

    if (piece == wPawn || piece == bPawn) {
        note[1] = move[0] + 97;
        note[2] = 8 - move[1] + 48;
        note[3] = 45;
        note[4] = move[2] + 97;
        note[5] = 8 - move[3] + 48;
        note[6] = 0;
    }
}

static void updateGUI() {
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
                gtk_text_buffer_get_end_iter(buffer, &txtiter);
                if (!player) {
                    sprintf(mnum, "%d", ++movecnt);
                    gtk_text_buffer_insert(buffer, &txtiter, " ", -1);
                    gtk_text_buffer_insert(buffer, &txtiter, mnum, -1);
                    gtk_text_buffer_insert(buffer, &txtiter, ".", -1);
                }
                /* Update the GUI board */
                drawGuiBoard(labelBoard, board);
                /* Update the game info */
                gtk_text_buffer_insert(buffer, &txtiter, note, -1);
                player = !player;
                if (player) {
                    gtk_label_set_text(currentPlayer, "Current player: Black");
                } else {
                    gtk_label_set_text(currentPlayer, "Current player: White");
                }

                if (kingUnderAttack(player, board)) {
                    if (player) printf("Black King is now checked!\n");
                    if (!player) printf("White King is now checked!\n");
                }
                /* TODO */
                
                if (!hasMovement(player, board)) {
                    if (kingUnderAttack(player, board)) {
                        if (player) printf("Black checkmated, white wins!\n");
                        if (!player) printf("White checkmated, black wins!\n");
                    } else {
                        printf("Stalemate!\n");
                    }
                }
}

static gboolean button_pressed(GtkWidget *ebox, GdkEventButton *event,
                               GtkLabel *labelBoard[][8]) {
    unsigned left, top, width, height;

    if (event->type == GDK_BUTTON_PRESS) {
        if (!clicks) {
            gtk_widget_override_background_color(ebox, GTK_STATE_NORMAL, &green);
            /*get coordinates of eventbox*/
            gtk_container_child_get(GTK_CONTAINER(table), ebox,
                                    "left-attach", &left,
                                    "top-attach", &top,
                                    "width", &width,
                                    "height", &height,
                                    NULL);
            //store the position you move from. It will be used to move the pieces in the board array
            // subtract 1 from left because the row numbers are part of the label table
            move[0] = left - 1;
            move[1] = top;
            /*save label*/
            prevEventbox = ebox;
            /*save the current coordinates*/
            clicks = 1;
        } else {
            /*make move*/
            gtk_container_child_get(GTK_CONTAINER(table), ebox,
                                    "left-attach", &left,
                                    "top-attach", &top,
                                    "width", &width,
                                    "height", &height,
                                    NULL);
            //store the position you move to. It will be used to move the pieces in the board array
            // subtract 1 from left because the row numbers are part of the label table
            move[2] = left - 1;
            move[3] = top;
            /*color back to normal*/
            if ((move[0] + move[1]) & 1) {
                /*odd square, lightbrown color*/
                gtk_widget_override_background_color(prevEventbox, GTK_STATE_NORMAL, &dbrown);
            } else {
                /*even square, darkbrown color*/
                gtk_widget_override_background_color(prevEventbox, GTK_STATE_NORMAL, &lbrown);
            }
            long_algebraic_notation(note, move, board);
            int u;
            u = 1; 
            if(player == player_color) {
                u = makemove(player, move, board);    
                if (!u) {
                //gui len server
                code[0]=move[0]+'0';
                code[1]=move[1]+'0';
                code[2]=move[2]+'0';
                code[3]=move[3]+'0';
                code[4]='\0';
                printf("%s\n",code);
                char temp[30];
                strcpy(temp,"MOVE	");
                strcpy(temp+strlen(temp),code);
                printf("%s\n",temp);
                if(!isServer)                	{
                		ret = sendto(sockfd, temp, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
                		if(ret < 0) {
                    	printf("Error sending data\n");
                	}
                }

                else {
                	 	ret = sendto(newsockfd,temp, BUF_SIZE, 0, (struct sockaddr *) &cl_addr,len);
                		if(ret < 0) {
                    	printf("Error send to client\n");
                		}
                }
                updateGUI();

            }
            }
           
            clicks = 0;
        }
    }
    return FALSE;
}
    