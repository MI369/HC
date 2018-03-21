/**
	Auto generated by xproto.exe
@author
	Dany
*/


#pragma  once 

#include <vector>
#include <ctype.h>
const char* strnstr(const char *dst,  int dlen, const char * src, int slen);
const char * strsnstr(const char *dest1, int dstlen1, 
			 const char *dest2, int dstlen2,
			 const char* src,int srclen);

void split_string(std::vector<char *>& stringList_result, 
				  char * input,
				  size_t len,
				  const char sep, 
				  int bSkipSpace,
				  int stopAt
				  );

#define SZ_BLANK "\r\n \t"
bool IsInCharset(char testc,const char *charset);
bool IsAllDigital(const char *sub,bool allowSpace);
void IcStringTrimEx(char *ss, const char *bem, const char *charset);

unsigned int HexStringnToIntegerA(char *lpHexString, int len);
unsigned int HexStringToIntegerA(char *lpHexString);
bool HexStringToBytesA(const char *lpszHexString, unsigned char * lpBytesOutput, int *pLenOfBytesOutput);
void BytesToStringA(char *&lpszHexStringOutPut, const unsigned char * lpBytes, int LenOfBytes, char seperator=' ');
void StringTrimSpaceA(char *ss, char *bem) ;

#ifdef WIN32
unsigned int HexStringToIntegerW(wchar_t *lpHexString);
bool HexStringToBytesW(const wchar_t *lpszHexString, unsigned char * lpBytesOutput, int *pLenOfBytesOutput);
void BytesToStringW(wchar_t *&lpszHexStringOutPut, const unsigned char * lpBytes, int LenOfBytes, wchar_t seperator=' ');
void StringTrimSpaceW(wchar_t *ss, wchar_t *bem) ;
#endif

