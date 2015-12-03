#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){

  FILE *fp;
  unsigned int hex_num=0x4fe3c560;

  fp=fopen("sample_file.txt","w");

  if(fp != NULL)
    fprintf(fp,"0x%.16x",hex_num);
  else
    printf("\nError creating file\n");

  return 0;
}
