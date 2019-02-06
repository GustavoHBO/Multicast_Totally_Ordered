#ifndef VIEW_H
#define VIEW_H
#include <gtk/gtk.h>


class View
{
  private:
    int argc;
    char ***argv;
  public:
    View(int argc, char *argv[]);
    ~View();
    int startChat(GtkWidget *widget, gpointer data);
};



#endif