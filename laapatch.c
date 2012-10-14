#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MZHEADER MZ
#define LAA_BIT  0x0020

int main(int argc, char** argv){
  if(argc < 2) return 1;
  
  FILE* f = fopen(argv[1], "rb");
  if(f){
      printf(" > Opening <%s>\n",argv[1]);
      
      char mzmagic[3];
      fread(&mzmagic, 2, 1, f);
      
      if(strcmp(mzmagic,"MZ")==0){
          //we're in front of a microsoft image
          printf(" >> This is a MS image, '%s' magic found...\n",mzmagic);
          
          //pick the PE header pointer
          fseek(f, 0x3C, SEEK_SET);
          
          unsigned short peheader;
          fread(&peheader, 2, 1, f);
          
          printf(" >>> PE header at offset 0x%x\n",peheader);
          fseek(f, peheader, SEEK_SET);
          
          char pemagic[5];
          fread(&pemagic, 4, 1, f);
          
          printf(" >>>> This is a PE executable, '%s' magic found...\n",&pemagic);
          
          if(strcmp(pemagic,"PE\0\0")==0){
              fseek(f, peheader+0x4+0x12, SEEK_SET);
              
              unsigned short characteristics;
              fread(&characteristics, 2, 1, f);
              
              printf(" ------------\n Characteristics bit field found,  /0x%x/, at offset 0x%x.",characteristics,ftell(f)-2);
              characteristics=characteristics|LAA_BIT;
              printf(             "\n Enabling Large Address Aware bit, /0x%x/.",characteristics);

          }else{
              puts(" >>>> This PE image seems corrupted or just pretty broken...");
          }

      }else{
          puts(" >> This thingie doesn't looks like a MS image at all...");
      }
  fclose(f);
  }
}