//---------------------------------------------------------------------------
#include <clx.h>
#include <stdio.h>
#include <math.h>
#pragma hdrstop

#include "compress.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
const buffer_size = 16384;


char getMod(FILE *f){
     if (f==NULL) return 0;
     rewind(f);
     char charmap[256];
     for(int i = 0; i<256;i++){
             charmap[i]=0;
     }

     char buff[buffer_size]="";
     int read=0;
     int max =0;
     char max_idx=0;
     int c=0;

     while (!feof(f)){
          read = fread(buff, sizeof(char), buffer_size, f);
          for (int i = 0; i<read;i++){
              c=charmap[(unsigned char)buff[i]]++;
              if (c>max) {
                max = c; max_idx=buff[i];
              }
          }
     }
     return max_idx;
}

char getMod(const char *filename){
     FILE *f=fopen(filename, "rb");
     char mod = getMod(f);
     fclose(f);
     return mod;
}

bool compress(const char* src,const char* target){
     char mod = getMod(src);
     char buff[buffer_size]="";
     int read =0;
     FILE *f1=fopen(src, "rb");
     FILE *f2=fopen(target, "wb");
     while (!feof(f1)){
           read=fread(buff, sizeof(char), buffer_size, f1);
           char *new_buff=new char[read+int(read/8)];
           for (int a=0; a<read;a++){
               char stmp[8]="";
               int k=0,j=0;
               char map=0;
               for (int i=0; i<8&&a<read;i++,k++,a++){
                   if (read[k]!=mod) stmp[j++]=read[k];
                   else map |= pow(2,i);
               }
               new_buff[nb++]=map;
               for(int b=0;b<j;b++) new_buff[nb++]=stmp[b];
           }
     }



     fclose(f1);fclose(f2);

}
