#include <stdlib.h>

#include "gui.h"
#include "denoms.h"

GtkWidget* entry;

void entry_callback(GtkWidget* widget, gpointer data) {
  GtkWidget** labels = (GtkWidget**) data; 
  
  char* text = (char*) gtk_entry_get_text(GTK_ENTRY(entry));

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

GtkWidget** init_labels(GtkContainer* container) {
  GtkWidget **labels = malloc(sizeof(GtkWidget**) * 11);
  
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

  gtk_container_add(container, labels[0]);
  gtk_container_add(container, labels[1]);
  gtk_container_add(container, labels[2]);
  gtk_container_add(container, labels[3]);
  gtk_container_add(container, labels[4]);
  gtk_container_add(container, labels[5]);
  gtk_container_add(container, labels[6]);
  gtk_container_add(container, labels[7]);
  gtk_container_add(container, labels[8]);
  gtk_container_add(container, labels[9]);
  gtk_container_add(container, labels[10]);
  
  return labels;
}

void init_gui(GtkApplication *app) {
  GtkWidget *window;

  // initialize window
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Denominations");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  // create box container for vertical flow
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  // create instructions label
  GtkWidget *label = gtk_label_new("Enter a value:");
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
