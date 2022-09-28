#include "a4.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void static merge(Individual *arr, int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  /* create temp arrays */
  Individual L[n1], R[n2];

  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  /* Merge the temp arrays back into arr[l..r]*/
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged subarray
  while (i < n1 && j < n2) {
    if (L[i].fitness <= R[j].fitness) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  /* Copy the remaining elements of L[], if there
     are any */
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  /* Copy the remaining elements of R[], if there
     are any */
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void static mergeSort(Individual *arr, int l, int r) {
  if (l < r) {
    // Same as (l+r)/2, but avoids overflow for
    // large l and h
    int m = l + (r - l) / 2;

    // Sort first and second halves
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations,
                        int population_size, double rate) {
  srand(time(NULL));
  Individual *Population = generate_population(population_size, image->width,
                                               image->height, image->max_color);
  comp_fitness_population(image->data, Population, population_size);
  mergeSort(Population, 0, population_size - 1);
  for (int i = 1; i <= num_generations; i++) {
    crossover(Population, population_size);
    mutate_population(Population, population_size, rate);
    comp_fitness_population(image->data, Population, population_size);
    mergeSort(Population, 0, population_size - 1);
    printf("Generation: %d Fitness: %lf\n", i, Population->fitness);
    /*if(i%1000 == 0){// prints the best image every 1000 generations
    char filename[40];
    sprintf(filename, "temp/results%d.ppm", i);
    write_ppm(filename,&Population->image);
    }*/
  }
  PPM_IMAGE *returnPic = malloc(image->height * image->width * sizeof(PPM_IMAGE)); // makes and allocates space for a new pic
  *returnPic = Population->image; //copies data from the best ranked image into new image
   returnPic->data = malloc(image->height * image->width* sizeof(PIXEL));
//allocates space for the pixels and then copies the pixel array
  for (int i = 0; i < image->height * image->width; i++)
	returnPic->data[i] = Population->image.data[i];
  for (int i = 0; i<population_size; i++){
	free(Population[i].image.data); //frees the pixel array in the population
  }
  free(Population);// frees the population

  return returnPic;
}

void free_image(PPM_IMAGE *p) {

  free(p->data); // free the array of pixels

  free(p); // free image
}
