//---------------------------------------------------------------------------
#pragma hdrstop

#include "cryptcore.h"
#include "cryptkey.h"
#include "fileversion.h"
//#include <conio.h>
#include <stdio.h>
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

CryptError errMesg;

errID getErrorCode(){
      return errMesg.errorID;
}

const char *getErrorMesg(){
      return errMesg.errMsg;
}

// old version, untl 1.0.0.43
bool cryptFileV1(const char* src, const char* target, const char* subkey, int keylen){
     char *buffer=NULL, *key;
     FILE *fori=fopen(src,"rb");
     if (fori==NULL){
        strcpy(errMesg.errMsg,"Unable to open source file");
        errMesg.errorID=SRC_NOT_OPENED;
        errMesg.procID=CRYPT;
        errMesg.subprocID=OPEN_SOURCE;
        return false;
     }

     int vBufferSize = bufferSize;
     while (buffer==NULL) {
          buffer = new char[vBufferSize];
          if(buffer==NULL) vBufferSize >>=1; // divide by 2 the required memory
          if(vBufferSize==0) {
                strcpy(errMesg.errMsg,"Out of Memory");
                errMesg.errorID=OUT_OF_MEMORY;
                errMesg.procID=CRYPT;
                errMesg.subprocID=BUFFER_MALLOC;
                return false;
          }
     }

     if (generateKey(&key,subkey,keylen)==NULL) {
        strcpy(errMesg.errMsg,"Error while processing key");
        errMesg.errorID=INVALID_KEY;
        errMesg.procID=CRYPT;
        errMesg.subprocID=GENERATE_KEY;
        delete[] buffer;
        return false;
     }


     FILE *fnew=writeVersion(target);
     if (fnew==NULL){
        strcpy(errMesg.errMsg,"Unable to create new file");
        errMesg.errorID=TARGET_NOT_CREATED;
        errMesg.procID=CRYPT;
        errMesg.subprocID=CREATE_TARGET;
        delete[] buffer;
        return false;
     }

     int k = 0;
     int read = 0;
     while (!feof(fori)){
           read = fread(buffer,1,vBufferSize,fori);
           k%=keylen;
           for (int i=0; i < read; i++){
               buffer[i]^=key[k<keylen?k:k%keylen];
               k++;
           }
           fwrite(buffer, 1, read, fnew);
     }
     fclose(fnew);
     fclose(fori);
     delete[] buffer;
     return true;
}

//current version, 1.1.0.0 -->

bool cryptFile(const char* src, const char* target, const char* subkey, int keylen){
     char *buffer=NULL, *key;
     FILE *fori=fopen(src,"rb");
     if (fori==NULL){
        strcpy(errMesg.errMsg,"Unable to open source file");
        errMesg.errorID=SRC_NOT_OPENED;
        errMesg.procID=CRYPT;
        errMesg.subprocID=OPEN_SOURCE;
        return false;
     }

     int vBufferSize = bufferSize;
     while (buffer==NULL) {
          buffer = new char[vBufferSize];
          if(buffer==NULL) vBufferSize >>=1; // divide by 2 the required memory
          if(vBufferSize==0) {
                strcpy(errMesg.errMsg,"Out of Memory");
                errMesg.errorID=OUT_OF_MEMORY;
                errMesg.procID=CRYPT;
                errMesg.subprocID=BUFFER_MALLOC;
                return false;
          }
     }

     if (generateKey(&key,subkey,keylen)==NULL) {
        strcpy(errMesg.errMsg,"Error while processing key");
        errMesg.errorID=INVALID_KEY;
        errMesg.procID=CRYPT;
        errMesg.subprocID=GENERATE_KEY;
        delete[] buffer;
        return false;
     }

     FILE *fnew=writeVersion(target);
     if (fnew==NULL ){
        strcpy(errMesg.errMsg,"Unable to create new file");
        errMesg.errorID=TARGET_NOT_CREATED;
        errMesg.procID=CRYPT;
        errMesg.subprocID=CREATE_TARGET;
        delete[] buffer;
        return false;
     }
     bool verOK=writeFileInfo(fnew, src);
     if (!verOK){
        strcpy(errMesg.errMsg,"Unable to create new file");
        errMesg.errorID=TARGET_NOT_CREATED;
        errMesg.procID=CRYPT;
        errMesg.subprocID=CREATE_TARGET;
        delete[] buffer;
        return false;
     }

     int k = 0;
     int read = 0;
     while (!feof(fori)){
           read = fread(buffer,1,vBufferSize ,fori);
           k%=keylen;
           for (int i=0; i < read; i++){
               buffer[i]^=key[k<keylen?k:k%keylen];
               k++;
           }
           fwrite(buffer, 1, read, fnew);
     }
     delete[] buffer;
     fclose(fnew);
     fclose(fori);
     return true;
}

bool decryptFile(const char* src, const char* target, const char* subkey, int keylen){
     char *buffer=NULL, *key;
     FILE *fcry=fopen(src,"rb");
     if (fcry==NULL){
        strcpy(errMesg.errMsg,"Unable to open source file");
        errMesg.errorID=SRC_NOT_OPENED;
        errMesg.procID=DECRYPT;
        errMesg.subprocID=OPEN_SOURCE;
        return false;
     }

     FILE *fori=fopen(target,"wb");

     if (fori==NULL){
        strcpy(errMesg.errMsg,"Unable to create new file");
        errMesg.errorID=TARGET_NOT_CREATED;
        errMesg.procID=DECRYPT;
        errMesg.subprocID=CREATE_TARGET;
        return false;
     }

     int vBufferSize = bufferSize;
     while (buffer==NULL) {
          buffer = new char[vBufferSize];
          if(buffer==NULL) vBufferSize >>=1; // divide by 2 the required memory
          if(vBufferSize==0) {
                strcpy(errMesg.errMsg,"Out of Memory");
                errMesg.errorID=OUT_OF_MEMORY;
                errMesg.procID=DECRYPT;
                errMesg.subprocID=BUFFER_MALLOC;
                return false;
          }
     }

     int k = 0,read=0;

     CryptVersion ver = readVersion(&fcry);

     switch (ver.MajorVersion){
            case 1: { if (generateKey(&key,subkey,keylen)==NULL) {
                         strcpy(errMesg.errMsg,"Error while processing key");
                         errMesg.errorID=INVALID_KEY;
                         errMesg.procID=DECRYPT;
                         errMesg.subprocID=GENERATE_KEY;
                         fclose(fcry); fclose(fori);
                         delete[] buffer;
                         return false;
                       }
                       switch (ver.MinorVersion){
                              case 0: { while (!feof(fcry)){
                                            read = fread(buffer,1,vBufferSize,fcry);
                                            k%=keylen;
                                            for (int i=0; i < read; i++){
                                                buffer[i]^=key[k<keylen?k:k%keylen];
                                                k++;
                                            }
                                            fwrite(buffer, 1, read, fori);
                                        } break;
                                      }
                              case 1: { fileInformation fi = {"","",0,""};
                                        readFileInfo(fcry,&fi);
                                        if (!crcCompare(fi.crc)) {
                                           strcpy(errMesg.errMsg,"Invalid file format");
                                           errMesg.errorID=INVALID_FORMAT;
                                           errMesg.procID=DECRYPT;
                                           errMesg.subprocID=INFO_READ;
                                           fclose(fcry); fclose(fori);
                                           delete[] buffer;
                                           return false;
                                        }
                                        while (!feof(fcry)){
                                              read = fread(buffer,1,vBufferSize,fcry);
                                              k%=keylen;
                                              for (int i=0; i < read; i++){
                                                  buffer[i]^=key[k<keylen?k:k%keylen];
                                                  k++;
                                              }
                                              fwrite(buffer, 1, read, fori);
                                        }
                                        break;
                                      }
                       }
                       break;
                    }
            default : {  strcpy(errMesg.errMsg,"Invalid file format");
                         errMesg.errorID=INVALID_FORMAT;
                         errMesg.procID=DECRYPT;
                         errMesg.subprocID=VERSION_CHECK;
                         fclose(fcry); fclose(fori);
                         delete[] buffer;
                         return false;
                       }
     }
     delete[] buffer;
     fclose(fcry);
     fclose(fori);
     return true;
}


