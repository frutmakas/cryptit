//---------------------------------------------------------------------------
#pragma hdrstop

#include <math.h>
#include <stdio.h>
#include <string.h>
//#include <conio.h>

#include "cryptkey.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

int strength=8;

char *mystrcpy(char *dest, const char*src, int len){
        for (int i =0;i<len;i++)
                dest[i]=src[i];
        return dest;
}

char *generateConfuseKey(char **confkey, const char* basekey, int keylen){
        *confkey=new char [keylen];
        int j =0;
        for (int i = 0; i <keylen;i+=2)
                (*confkey)[j++]=basekey[i];
        for (int i = 1; i<keylen;i+=2)
                (*confkey)[j++]=basekey[i];
        return *confkey;
}
char* generateKey(char **longkey, const char* basekey, int &keylen){

        char *subkey;
        int subkeylen=keylen;
        subkey=new char[subkeylen];
        mystrcpy(subkey, basekey,keylen);

        for (int j=0;j<strength && subkeylen<8192;j++){
                int stmplen=subkeylen*2;
                char *stmp = new char[stmplen+1];
                mystrcpy(stmp,subkey,subkeylen);
                for (int i=subkeylen;i<stmplen;i++) {
                        stmp[i]=((stmp[i-subkeylen]^stmp[i-subkeylen+1])+basekey[i%keylen]+i)%255;
                        stmp[i-subkeylen]=(stmp[i-subkeylen]*259-79*stmp[i]-i%173)%255;
                }
                stmp[stmplen]=0;
                // stmp dah isi, now kena update subkey ngan subkeylen
                delete subkey;
                subkey = new char[subkeylen=stmplen+1];
                mystrcpy(subkey,stmp, subkeylen);
                // subkey dah delete, now kena delete stmp
                delete stmp;
        }
        // now longkey dah generate, kena oddkan number
        *longkey = new char[subkeylen+1];
        mystrcpy(++(*longkey), subkey,subkeylen);
        --(*longkey);
        (*longkey)[0]= '\\';
        delete subkey;
        keylen=subkeylen+1;
        return *longkey;
}
