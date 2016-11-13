//---------------------------------------------------------------------------
#pragma hdrstop


#include <System.hpp>
#include "fileversion.h"
#include <stdio.h>
#include <SysUtils.hpp>
#include <string.h>
//#include <vcl/dstring.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//CryptVersion currentVersion = { 1, 1, {1999,7,27},{0,0,0}};
CryptVersion currentVersion = { 1, 1, {2003,1,30},{0,0,0}};

void getdate(date *CryptDate){
        TDateTime date_x = TDateTime::CurrentDate();
        date_x.DecodeDate(&CryptDate->da_year, &CryptDate->da_mon, &CryptDate->da_day);
}

void initCryptVersion(CryptVersion &ver){
        ver.MajorVersion=ver.MinorVersion=0;
        ver.VersionDate.da_year=ver.VersionDate.da_day=ver.VersionDate.da_mon=0;
}

CryptVersion readVersion(FILE **f){
        CryptVersion ver;
        initCryptVersion(ver);
        if (*f==NULL) return ver;
        rewind(*f);
        if (fread(&ver,sizeof(CryptVersion),1,*f)!=1)
           initCryptVersion(ver);
        return ver;
}

FILE* writeVersion(const char* filename){
        FILE* f = fopen(filename,"wb");
        getdate(&currentVersion.CryptDate);
        if (f==NULL) return NULL;
        fwrite(&currentVersion, sizeof(CryptVersion),1,f);
        return f;
}

void crcCopy(unsigned char *target){
     for(int i = 0; i<5;i++) target[i]=crc[i];
}

bool crcCompare(const unsigned char* src){
    bool ok = false;
    int max=strlen((char*)src)<5?strlen((char*)src):5;
    try {
        ok=max==5;
        for (int i =0; i<max;i++) ok=src[i]==crc[i]&&ok;
    } catch (...) {return false;}
    return ok;
}

void fileInformationCopy(fileInformation *dest, fileInformation src){
     for (int i=0;i<5;i++) dest->crc[i]=src.crc[i];
     for (int i=0;i<8;i++) dest->ext[i]=src.ext[i];
     for (int i=0;i<40;i++) dest->name[i]=src.name[i];
     dest->length=src.length;
}

void infoScramble(fileInformation **fi){
     int l = strlen((*fi)->name);
     int st=200;
     for (int i =0;i<l;i++) (*fi)->name[i]^=st++;
     l = strlen((*fi)->ext);
     for (int i =0;i<l;i++) (*fi)->ext[i]^=st++;
}

bool writeFileInfo(FILE* f, const char* filename){
     if (f==NULL) return false;
     AnsiString as = AnsiString(filename);
     fileInformation *fi=new fileInformation;
     strcpy(fi->name,ExtractFileName(filename).c_str());
     strcpy(fi->ext,ExtractFileExt(filename).c_str());
     fi->length=strlen(fi->name);
     infoScramble(&fi);
     crcCopy(fi->crc);
     if (fi->length>40) return false;
     return fwrite(fi,sizeof(fileInformation), 1, f)==1;
}

void readFileInfo(FILE *f, fileInformation *fi){
     if (f==NULL) return;
     if (fread(fi, sizeof(fileInformation),1,f)==1) infoScramble(&fi);
}

void printVersion(CryptVersion cv){
        printf("\nRelease %d.%d %d-%d-%d", cv.MajorVersion, cv.MinorVersion,
                                cv.VersionDate.da_day,cv.VersionDate.da_mon,cv.VersionDate.da_year);
}

