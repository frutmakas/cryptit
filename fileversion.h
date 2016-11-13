//---------------------------------------------------------------------------
#ifndef fileversionH
#define fileversionH
//#include <dos.h>
#include <stdio.h>
//---------------------------------------------------------------------------

struct date {
        unsigned short da_year;
        unsigned short da_mon;
        unsigned short da_day;
};

struct CryptVersion {
       int MajorVersion;
       int MinorVersion;
       date VersionDate;
       date CryptDate;
};

struct fileInformation {
       char name[40];
       char ext[8];
       int length;
       unsigned char crc[5];
};

const unsigned char crc[5]={27, 19, 177, 241, 32};

//CryptVersion currentVersion = { 1, 0, {1999,7,11},{0,0,0}};
extern CryptVersion currentVersion; // = { 1, 1, {1999,7,27},{0,0,0}};

void initCryptVersion(CryptVersion &ver);
CryptVersion readVersion(FILE **f);
void printVersion(CryptVersion cv);
FILE* writeVersion(const char* filename);

bool writeFileInfo(FILE* f, const char* filename);
void readFileInfo(FILE *f, fileInformation *fi);
void fileInformationCopy(fileInformation *dest, fileInformation src);


void crcCopy(unsigned char *target);
bool crcCompare(const unsigned char* src);




#endif
