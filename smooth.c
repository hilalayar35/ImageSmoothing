#include <stdint.h>
#include <stdio.h>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#define CHANNEL_NUM 1


int main(int argc,char* argv[]) {

  int width, height, bpp;
  clock_t start,end;
  double time;


	// Reading the image
  uint8_t* rgb_image = stbi_load(argv[1], &width, &height, &bpp, CHANNEL_NUM);

  if(rgb_image == NULL) {
    printf("Error in loading the image\n");
    exit(1);
  }

  printf("Width: %d  Height: %d \n",width,height);

  printf("Timer started.\n");
  start=clock();

  for(int k=1;k<height-1;k++){
    for(int l=1;l<width-1;l++){
 	    int sum=0;
      for(int m=k-1;m<=k+1;m++){
        for(int n=l-1;n<=l+1;n++){

            sum=sum+rgb_image[m*width + n];

        }
      }
      rgb_image[k*width+l]=sum/9;
    }
  }

  end=clock();

  time=(double)(end-start)/CLOCKS_PER_SEC;
  printf("Calculation completed in %.2f miliseconds\n",(time*1000.0));

  // Storing the image
  stbi_write_jpg(argv[2], width, height, CHANNEL_NUM, rgb_image, 100);
  stbi_image_free(rgb_image);

  return 0;
}
