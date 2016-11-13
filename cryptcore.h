//---------------------------------------------------------------------------
#ifndef cryptcoreH
#define cryptcoreH
//---------------------------------------------------------------------------
//const bufferSize = 16384;
//const bufferSize = 65536; //1.10c
//const bufferSize = 1048576; //1.10d
const bufferSize = 8388608; //1.10e

typedef enum {SRC_NOT_OPENED, TARGET_NOT_CREATED, FILE_NULL, INVALID_CHKSUM, INVALID_FORMAT, INVALID_KEY, FILE_NOT_WRITTEN, OUT_OF_MEMORY} errID;
typedef enum {CRYPT, DECRYPT} process;
typedef enum {CREATE_TARGET, OPEN_SOURCE, GENERATE_KEY, VERSION_CHECK, INFO_WRITE, INFO_READ, BUFFER_MALLOC } subprocess;

// until version 1.0.0.43
bool cryptFileV1(const char* src, const char* target, const char* subkey, int keylen);
//bool decryptFileV1(const char* src, const char* target, const char* subkey, int keylen);

// Current Version  starts 1.1.0.0
bool cryptFile(const char* src, const char* target, const char* subkey, int keylen);
bool decryptFile(const char* src, const char* target, const char* subkey, int keylen);

errID getErrorCode();
const char *getErrorMesg();

struct CryptError{
       errID errorID;
       char errMsg[100];
       process procID;
       subprocess subprocID;
};
#endif
