#include <stdlib.h>
#include <regex.h>

#include "gui.h"
#include "denoms.h"

GtkWidget* entry;

// checks string is in the right format with a regular expression
int is_input_valid(char* s) {
  regex_t reg;
  int val = regcomp(&reg, "^[0-9]*\\.[0-9][0-9]$", 0);
  //g_print("%d\n", val);
  return !regexec(&reg, s, 0, NULL, 0);
}

// callback for when the button is pressed
void entry_callback(GtkWidget* widget, gpointer data) {
  GtkWidget** labels = (GtkWidget**) data; 
  
  char* text = (char*) gtk_entry_get_text(GTK_ENTRY(entry));
  if (!is_input_valid(text)) {
    gtk_label_set_text(GTK_LABEL(labels[11]), "Invalid input");
    return;
  }
  gtk_label_set_text(GTK_LABEL(labels[11]), "");

  int dollars = get_dollars(text);
  int coins = get_coins(text);

  int* dollars_change = get_change(dollars, DENOMS, 7);
  for (int i = 0; i < 7; i++) {
    // max of 10 digits for number + 7 characters for preceding part of string
    // so 18 should guarantee safety. (1 null character)
    char* s = malloc(sizeof(char) * 18);
    sprintf(s, "$%d : %d", DENOMS[i], dollars_change[i]);
    gtk_label_set_text(GTK_LABEL(labels[i]), s);
    free(s);
  }
  free(dollars_change);

  int* coins_change = get_change(coins, COIN_DENOMS, 4);
  for (int i = 0; i < 4; i++) {
    char* s = malloc(sizeof(char) * 18);
    sprintf(s, "¢%d : %d", COIN_DENOMS[i], coins_change[i]);
    gtk_label_set_text(GTK_LABEL(labels[i+7]), s);
    free(s);
  }
  free(coins_change);
}

// create the labels for change and error
GtkWidget** init_labels(GtkContainer* container) {
  GtkWidget **labels = malloc(sizeof(GtkWidget**) * 12);
  
  labels[0] = gtk_label_new("$1 : 0");
  labels[1] = gtk_label_new("$2 : 0");
  labels[2] = gtk_label_new("$5 : 0");
  labels[3] = gtk_label_new("$10 : 0");
  labels[4] = gtk_label_new("$20 : 0");
  labels[5] = gtk_label_new("$50 : 0");
  labels[6] = gtk_label_new("$100 : 0");
  labels[7] = gtk_label_new("¢1 : 0");
  labels[8] = gtk_label_new("¢5 : 0");
  labels[9] = gtk_label_new("¢10 : 0");
  labels[10] = gtk_label_new("¢25 : 0");
  // error label
  labels[11] = gtk_label_new("");

  gtk_container_add(container, labels[11]);
  for (int i = 0; i < 11; i++) {
    gtk_container_add(container, labels[i]);
  }
  
  return labels;
}

// initialize all of the widgets
void init_gui(GtkApplication *app) {
  GtkWidget *window;

  // initialize window
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Denominations");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

  // create box container for vertical flow
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  // create instructions label
  GtkWidget *label = gtk_label_new("Enter a value in the form XXXX.YY:");
  gtk_container_add(GTK_CONTAINER(box), label);
  
  // text input
  entry = gtk_entry_new();
  gtk_container_add(GTK_CONTAINER(box), entry);

  // button
  GtkWidget *button = gtk_button_new_with_label("Submit");
  gtk_container_add(GTK_CONTAINER(box), button);

  // make denominations labels
  GtkWidget **labels = init_labels(GTK_CONTAINER(box));
  g_signal_connect(button, "clicked", G_CALLBACK(entry_callback), labels);
  
  gtk_container_add(GTK_CONTAINER(window), box);

  // show gui
  gtk_widget_show_all(box);
  gtk_window_present(GTK_WINDOW (window));
}
