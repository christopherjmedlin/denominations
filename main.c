#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

#include "gui.h"
#include "denoms.h"

void activate(GtkApplication *app, gpointer user_data) {
  init_gui(app);
}

int main(int argc, char** argv) {
  /*
  int dollars = 0, coins = 0;

  printf("Please enter a currency value in the form X.YY\n");
  scanf("%d.%d", &dollars, &coins);
  
  if (coins > 99) {
    printf("Error: precision for cents cannot be greater than 2");
  }
  
  for (int i = 0; i < 7; i++) {
    printf("$%d : %d\n", DENOMS[i], dollars / DENOMS[i]);
    dollars %= DENOMS[i];
  }

  for (int i = 0; i < 4; i++) {
    printf("¢%d : %d\n", COIN_DENOMS[i], coins / COIN_DENOMS[i]);
    coins %= COIN_DENOMS[i];
  }
  */

  GtkApplication *app;
  int status;

  app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE); 
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL); 
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
