#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mutate(Individual *individual, double rate) { // Working
  int n = individual->image.width * individual->image.height;
  int mutateAmount = (int)(rate / 100 * n);
  for (int i = 0; i < mutateAmount; i++) {
    int z = rand() % (n + 1); // Finds a random pixel to edit
    individual->image.data[z].r = rand() % 256;
    individual->image.data[z].g = rand() % 256;
    individual->image.data[z].b = rand() % 256;
    // printf("%u %u
    // %u\n",individual->image.data[z].r,individual->image.data[z].g,individual->image.data[z].b);
  }
}

void mutate_population(Individual *individual, int population_size,
                       double rate) {
  for (int i = population_size / 4; i < population_size; i++) {
    mutate(&individual[i], rate);
  }
}
