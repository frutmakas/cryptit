//---------------------------------------------------------------------------
#ifndef cryptkeyH
#define cryptkeyH
//---------------------------------------------------------------------------
extern int strength; //=8;
char *mystrcpy(char *dest, const char*src, int len);
char *generateConfuseKey(char **confkey, const char* basekey, int keylen);
char* generateKey(char **longkey, const char* basekey, int &keylen);

#endif
 