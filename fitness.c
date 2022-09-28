#include "a4.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double comp_distance(const PIXEL *A, const PIXEL *B,
                     int image_size) {   // WOrking
  double sum = 0;                        // Holds the sum of the distances
  for (int i = 0; i < image_size; i++) { // for loop goes through each pixel
    //Calculates the differences between red green and blue pixels, squares, and then adds them to overall sum 
    int r = A[i].r - B[i].r;
    int g = A[i].g - B[i].g;
    int b = A[i].b - B[i].b;
    r *= r;
    g *= g;
    b *= b;
    sum += r + b + g;
    // sum+= pow(A[i].r-B[i].r,2)+pow(A[i].g-B[i].g,2)+pow(A[i].b-B[i].b,2); // old less efficient code
    // adds the distance of each pixel to the sum
  }
  return (sqrt(sum)); // returns square root of the sum
}

void comp_fitness_population(const PIXEL *image, Individual *individual,
                             int population_size) {
  int image_size = individual[0].image.width *
                   individual[0].image.height; // finds the size of the image
  for (int i = 0; i < population_size;
       i++) { // for loop goes through each picture in population
    individual[i].fitness = comp_distance(
        image, individual[i].image.data,
        image_size); // sets the fitness to the difference between original
                     // image and individual in population
  }
}
