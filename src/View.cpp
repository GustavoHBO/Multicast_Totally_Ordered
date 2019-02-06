#include "View.hpp"
#include <gtk/gtk.h>

char const *title = "Chat";

static void print(GtkWidget *widget, gpointer data)
{
    g_print("Hello World\n");
}

static void teste(GtkWidget *widget, gpointer data)
{
    g_print("OK\n");
}

static void start_window_chat(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button, *button_start_chat;
    GtkWidget *button_box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 540);

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), button_box);

    button = gtk_button_new_with_label("Hello World");
    g_signal_connect(button, "clicked", G_CALLBACK(print), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), button);

    button_start_chat = gtk_button_new_with_label("Iniciar Chat");
    g_signal_connect(button_start_chat, "clicked", G_CALLBACK(teste), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), button_start_chat);

    gtk_widget_show_all(window);
}

static void start_chat(GtkWidget *widget, gpointer data)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(start_window_chat), NULL);
    int argc = 1;
    char *argv[1];
    argv[1] = "./multicast";
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button, *button_start_chat;
    GtkWidget *button_box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 540);

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), button_box);

    button = gtk_button_new_with_label("Hello World");
    g_signal_connect(button, "clicked", G_CALLBACK(print), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), button);

    button_start_chat = gtk_button_new_with_label("Iniciar Chat");
    g_signal_connect(button_start_chat, "clicked", G_CALLBACK(start_chat), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), button_start_chat);

    gtk_widget_show_all(window);
}

View::View(int argc, char *argv[])
{
    this->argc = argc;
    this->argv = &argv;
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
}

View::~View()
{
}

int View::startChat(GtkWidget *widget, gpointer data)
{

    return 0;
}