#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

PIXEL *generate_random_image(int width, int height, int max_color) {

  PIXEL *returnArray =
      malloc(width * height *
             sizeof(PIXEL)); // initizalizing an array of width*height elements

  for (int i = 0; i < (width * height);
       i++) { // for loop to give each pixel random r b g values

    returnArray[i].r = rand() % (max_color + 1);
    returnArray[i].b = rand() % (max_color + 1);
    returnArray[i].g = rand() % (max_color + 1);
  }

  return returnArray; // returns a pointer to array of pixels
}

Individual *generate_population(int population_size, int width, int height,
                                int max_color) {

  Individual *returnArray =
      malloc(population_size * sizeof(Individual)); // initiazlizing array

  for (int i = 0; i < (population_size);
       i++) { // for loop to make each Individual

    returnArray[i].image.data = generate_random_image(
        width, height,
        max_color); // make the data part of the PPM_IMAGE part of individual
    returnArray[i].image.width =
        width; // make width of PPM_image part of individual
    returnArray[i].image.height = height;       // make height """"
    returnArray[i].image.max_color = max_color; // make max_color """""
  }

  return returnArray; // returns a poiner to array of individuals
}
