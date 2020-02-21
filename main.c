#include "PPMTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

void main()
{
  unsigned char *image1, *image2;
  int cols, rows, i, j, z, histSize;
  char filename1[50],filename2[50];

  printf("Histogram Difference between two images!\n\n");
  printf("Enter first image file name: ");
  scanf("%s",filename1);
  printf("Enter second image file name: ");
  scanf("%s",filename2);
  printf("Enter Histogram size (2(2x2x2), 4(4x4x4), 8(8x8x8), or 16(16x16x16)): ");
  scanf("%d",&histSize);

  //Reading PPM data
  image1 = ReadPPM(filename1,&cols, &rows);
  image2 = ReadPPM(filename2,&cols, &rows);

  //Calculating Bin size
  int binSize=256/histSize;

  struct pixel rgb ;
  int bin1[16][16][16],bin2[16][16][16];
  memset(bin1,0,sizeof(bin1));
  memset(bin2,0,sizeof(bin2));
  
  for(i=0;i<rows;i++)
          {
            for(j=0;j<cols;j++)
            {

                rgb.red=GetRPixel(image1,cols,j,i);
                rgb.green=GetGPixel(image1, cols,j,i);
                rgb.blue=GetBPixel(image1, cols,j,i);

                //Increments pixel count of bin1
                bin1[rgb.red/binSize][rgb.green/binSize][rgb.blue/binSize]++;

                rgb.red=GetRPixel(image2,cols,j,i);
                rgb.green=GetGPixel(image2, cols,j,i);
                rgb.blue=GetBPixel(image2, cols,j,i);

                //Increments pixel count of bin2
                bin2[rgb.red/binSize][rgb.green/binSize][rgb.blue/binSize]++;
                
            }
          }
  
  double histDiff=0,histDiffRatio=0;
  
  for (i=0;i<histSize;i++){
    for(j=0;j<histSize;j++){
      for(z=0;z<histSize;z++){
        //Comparing two histograms
        histDiff+=abs(bin1[i][j][z] - bin2[i][j][z]);
      }
    }    

  }

  //Calculating Histogram ratio
  histDiffRatio=histDiff/(cols*rows*2);
  
  printf("\n\n\nHistogram difference: %0.3lf\n",histDiff);
  printf("Histogram difference ratio: %0.3lf\n",histDiffRatio);
}

