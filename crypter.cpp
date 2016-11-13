
#pragma hdrstop
//#include <condefs.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
//#include <conio.h>
#include "cryptcore.h"
#include <io.h>
#include "fileversion.h"
#include "cryptcore.h"
#include "cryptkey.cpp"


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma argsused

int main(int argc, char* argv[])
{
/*        char key[60] = "";
        printf("\nEnter crypt code :");
        gets(key);
        int i = strlen(key);
        printf("\nEnter source filename : ");
        char src[50]=""; gets(src);
        printf("\nEnter target filename : ");
        char target[50]=""; gets(target);
        cryptFile(src,target,key,i);
        printf("\nEnter compare filename : ");
        char comp[50]=""; gets(comp);
        decryptFile(target,comp, key,i);
        printf("\nFile encryption/decryption done... ");
        printf("\nproceding with file compare ");
        FILE *f1 = fopen(src,"rb");
        FILE *f2 = fopen(comp,"rb");
        int fh1 = _fileno(f1), fh2=_fileno(f2);
        bool idem = false;
        if (filelength(fh1)==filelength(fh2)) {
           idem = true;
           while (!feof(f1) && idem){
                 idem = fgetc(f1)==fgetc(f2);
           }

        }
        if (idem) printf("\nfile identique!!! ");
        else printf("\nfile not identique!!! ");
        getch();
        fclose(f1);fclose(f2);





        return 0;*/
}
