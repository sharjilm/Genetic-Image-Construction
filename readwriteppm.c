#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
PPM_IMAGE *read_ppm(const char *file_name) { // WORKING

  int throwaway;
  FILE *fp = fopen(file_name, "rb");
  char throwaway2;
  PPM_IMAGE *pic = malloc(sizeof(PPM_IMAGE));
  if (fp != NULL) {
    fscanf(fp, "%c %d", &throwaway2,
           &throwaway); // reads and disregards the p3 component
    fscanf(
        fp, "%d %d %d ", &pic->width, &pic->height,
        &pic->max_color); // gets the next 3 values which are width, height and
                          // max color and stores them in the PPM_IMAGE pic
    pic->data =
        malloc(pic->width * pic->height *
               sizeof(PIXEL)); // Allocates enough data for all the pixels the
                               // image has based on its width and height
    for (int i = 0; i < (pic->width * pic->height); i++) {

      fscanf(fp, "%hhu %hhu %hhu", &pic->data[i].r, &pic->data[i].g,
             &pic->data[i].b); // Gets the next 3 values which should
                               // be the red green blue values of the next pixel
    }
    fclose(fp);
  }

  return pic;
}

void write_ppm(const char *file_name, const PPM_IMAGE *image) { // working

  FILE *myFileInfo =
      fopen(file_name, "wb"); // open for writing code in binary mode
  fprintf(myFileInfo, "P3\n%d %d\n%d\n", image->width, image->height,
          image->max_color); // make first 3 lines
  for (int i = 0; i < (image->height * image->width);
       i++) { // for loop for writing out pixels

    fprintf(myFileInfo, "%d %d %d ", image->data[i].r, image->data[i].g,
            image->data[i].b);
  }
  fclose(myFileInfo); // close file
}
