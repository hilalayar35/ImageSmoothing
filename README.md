# ImageSmoothing
 Sequential and Parallel Image Smoothing
 
 In this program, we used parallel computing. Our purpose is high performance computing and gaining 
time with using data parallelism. We write 2 different code firstly sequential and secondly parallel 
codes also we learn that how can we smooth image.

**Commands we used in the sequential program:** 

gcc smooth.c -o smooth -lm

./smooth photo.JPG photo1.JPG

**Commands we used in the parallel program:**

mpicc mpi_smooth.c -o mpi_smooth -lm

./mpi_smooth photo.JPG photo2.JPG
