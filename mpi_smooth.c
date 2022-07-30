#include <stdint.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#define CHANNEL_NUM 1


  int main(int argc,char* argv[]) {

  int width, height, bpp;

  int size; //number of processes
  int rank; //process rank

  clock_t start,end;
  double time;

	// Reading the image
  uint8_t* rgb_image = stbi_load(argv[1], &width, &height, &bpp, CHANNEL_NUM);

  if(rgb_image == NULL) {
    printf("Error in loading the image\n");
    exit(1);
  }

  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  if(rank==0){
    printf("Width: %d  Height: %d \n",width,height);
  }

  int count1 = height / size;
  int remainder1 = height % size;
  int start1, stop1;

  if (rank < remainder1) {
    // The first 'remainder' ranks get 'count + 1' tasks each
    start1 = rank * (count1 + 1);
    stop1 = start1 + count1;
  } else {
    // The remaining 'size - remainder' ranks get 'count' task each
    start1 = rank * count1 + remainder1;
    stop1 = start1 + (count1 - 1);
  }

  int count2 = width / size;
  int remainder2 = width % size;
  int start2, stop2;

  if (rank < remainder2) {
    // The first 'remainder' ranks get 'count + 1' tasks each
    start2 = rank * (count2 + 1);
    stop2 = start2 + count2;
  } else {
    // The remaining 'size - remainder' ranks get 'count' task each
    start2 = rank * count2 + remainder2;
    stop2 = start2 + (count2 - 1);
  }

  if(rank==0){
    printf("Timer started.\n");
  }

  start=clock();

  for(int k=start1;k<stop1-1;k++){
    for(int l=start2;l<stop2-1;l++){
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


  if(rank==0){
    // Storing the image
    stbi_write_jpg(argv[2], width, height, CHANNEL_NUM, rgb_image, 100);
    stbi_image_free(rgb_image);

    printf("Calculation completed in %.2f miliseconds\n",(time*1000.0));
  }

  MPI_Finalize();

  return 0;

}
