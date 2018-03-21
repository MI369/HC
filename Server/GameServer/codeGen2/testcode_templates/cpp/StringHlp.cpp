
/**
	Auto generated by xproto.exe
@author
	Dany
*/

/*::STDAFX_H::*/
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#else
#include <string.h>
#endif

#include "StringHlp.h"




const char* strnstr(const char *dst,  int dlen, const char * src, int slen)
{
	const char *s = NULL;

	while (dlen >= slen) {
		if (memcmp(src, dst, slen) == 0) {
			s = dst;
			break;
		}
		dst++;
		dlen--;
	}
	return s;
}

const char * strsnstr(const char *dest1, int dstlen1, 
			 const char *dest2, int dstlen2,
			 const char* src,int srclen)
{
	int dlen = dstlen1+dstlen2;
	const char *p1 = NULL;
	const char *p2 = NULL;
	int i,j;
	for(j=0;j<=dlen-srclen;j++)
	{

		if(j < dstlen1)
			p1 =dest1+j;
		else
			p1 =dest2+j-dstlen1;

		int match=1;
		for(i=0;i<srclen;i++)
		{
			
			if(j+i < dstlen1)
				p2 = dest1+j+i;
			else
				p2 = dest2+j+i-dstlen1;

			if(*p2!=*(src+i))
			{
				match=0;
				break;
			}
		}

		if(match)
		{
			return p1;
		}
	}
	return 0;
}
/**
split string and trim begin and end. must be a zero terminated string.
*/
void split_string(std::vector<char *>& stringList_result, 
				  char * input,
				  size_t len,
				  const char sep, 
				  int bSkipSpace,
				  int stopAt
				  )
{
	char *p = input;
	char *e = input + len+1;

	//remove space at the front.
	if(bSkipSpace)
	{
		while(p<e && (*p=='\r'||*p=='\n'||*p==' '||*p=='\t')) p++;
	}
	
	char *pv = p; 
	while(p<e)
	{
		if(*p==sep || *p==0)
		{
			char *psavePos = p;
			
			
			if(bSkipSpace&&p>input)
			{
				char *pe=p-1;
				
				while(pe>=input && (*pe=='\r'||*pe=='\n'||*pe==' '||*pe=='\t')) 
					pe--;

				if(pe<p-1)
					*(pe+1)=0;
			}
			

			stringList_result.push_back(pv);

			if(stopAt==stringList_result.size())
			{
				break;
			}

			if(*psavePos!=0)
			{
				*psavePos=0;
			}

			p++;

			if(bSkipSpace)
			{
				while(p<e && (*p=='\r'||*p=='\n'||*p==' '||*p=='\t' ||*p==sep)) p++;
			}

			pv = p;			
		}
		else
		{
			p++;
		}
	}
	
}


unsigned int HexStringnToIntegerA(char *lpHexString, int len)
{
	char temp[20];
	if(len > 20 ) return 0;
	if(len%2!=0)
	{
		temp[0]='0';
		memcpy(temp+1,lpHexString,len);
		temp[len+1]=0;
	}
	else
	{
		memcpy(temp,lpHexString,len);
		temp[len]=0;
	}
	
	
	
	return HexStringToIntegerA(temp);

}

unsigned int HexStringToIntegerA(char *pHexStr)
{
	int iret =0;
	unsigned char *pb = (unsigned char *)&iret;
	static unsigned char hexTable[23] = {0,1,2,3,4,5,6,7,8,9,0,0,0,0, 0,0,0, 10,11,12,13,14,15};
	char *p = pHexStr;
	while(*p)
	{
		if(*p>='a' && *p<='z')
		{
			*p =*p-'a' +'A';
		}
		p++;
	}

	char *pstr = pHexStr;

	bool bNegtive=false;
	if(pstr[0]=='+')
	{
		pstr++;
	}
	else if(pstr[0]=='-')
	{
		bNegtive = true;
		pstr++;
	}

	size_t istrlen = strlen(pstr);
	if(istrlen > 8 || istrlen==0)
	{
		return 0;
	}
	bool bHi=false;
	int i,j;
	for(i=(int)istrlen-1,j=0 ;i>=0;i--)
	{
		if( !( (pstr[i]>='0' &&  pstr[i]<='9') || ( pstr[i]>='A' && pstr[i]<='Z') ))
			continue;

		if(!bHi)
		{
			pb[j] =hexTable[pstr[i]- '0'];
		}
		else
		{
			pb[j] +=hexTable[pstr[i]- '0']*16;
			j++;
		}
		bHi=!bHi;
	}

	if(bNegtive)
	{
		return (unsigned int)(-iret);
	}
	else
	{
		return (unsigned int)iret;
	}
}

bool HexStringToBytesA(const char *pBinStr, unsigned char * pBins, int *pLenOfBins)
{
	size_t istrlen = strlen(pBinStr);
	if(istrlen ==0)
	{
		return false;
	}

	const char *pbBeg = pBinStr;
	const char *pbEnd = pBinStr+istrlen;
	while(pbBeg < pbEnd && *pbBeg ==0x0020 ) pbBeg++;
	
	
	istrlen = pbEnd - pbBeg;
	if(istrlen <=0)
	{
		return false;
	}

	int binLen = (int)(istrlen+1)/2;
	
	
	if(pBins==NULL || *pLenOfBins < binLen ) 
	{
		*pLenOfBins = binLen;
		return false;
	}

	unsigned char * pret=pBins;
	
	unsigned char hexTable[23] = {0,1,2,3,4,5,6,7,8,9,0,0,0,0, 0,0,0, 10,11,12,13,14,15};
	int i =0;
	
	bool bHi=true;
	while(pbBeg <pbEnd)
	{
		char wc = *pbBeg;
		if(wc !=0x0020)
		{
			if(wc>'F')
			{
				wc-='a'-'A';
			}

			if(!bHi)
			{
				pret[i] +=hexTable[wc- '0'];
				i++;
			}
			else
			{
				pret[i] =hexTable[wc-'0']*16;
				
			}
			bHi=!bHi;
		}
		pbBeg++;
	}
	
	*pLenOfBins = i;
	return true;


}

void BytesToStringA(char *&pBinStr, const  unsigned char * pbin, int len,char seperator)
{
	pBinStr = new char[len*3+2];
	pBinStr[0]=0;
	if(len==0 || pbin == NULL)
	{
		return;
	}
	int ncLen = 0;
	for(int i=0;i<len;i++)
	{
		if(seperator!=0)
			ncLen += sprintf(pBinStr+ncLen,"%02X%c",pbin[i],seperator);
		else
			ncLen += sprintf(pBinStr+ncLen,"%02X",pbin[i]);
	}
}


bool IsInCharset(char testc,const char *charset)
{
	const char *p = charset;
	while(*p!=0)
	{
		if(testc==*p)
			return true;
		p++;
	}
	return false;
}

bool IsAllDigital(const char *sub,bool allowSpace)
{
	int len = strlen(sub);
	for(int j=0;j<len;j++)
	{
		if(sub[j] > 0 && !isdigit(sub[j]))
		{
			if(allowSpace && sub[j]==' ')
			{
				continue;
			}
			else
				return false;
		}
	}
	return true;
}


/**
Removes char from the beginning and/or end and/or middle of strings 
"b" for begin
"e" for end
"m" for middle
"bem" for remove spaces in begin,end and middle.
*/
void IcStringTrimEx(char *ss, const char *bem, const char *charset) 
{
	char fc1,*fcp1,*fcp2,*fcp3;
	const char *bemptr;

	for (fcp1=ss; IsInCharset(*fcp1,charset); fcp1++);

	if (!(*fcp1)) { *ss=0; return; }  /* Null or ALL blanks */

	/* Now there's at least one non-space */
	for (bemptr=bem; *bemptr; bemptr++) {

		if (IsInCharset(*ss,charset)&& (*bemptr=='b' || *bemptr=='B')) {
			for (fcp2=ss; IsInCharset(*fcp2,charset); fcp2++);

			for (fcp1=ss; *fcp2; fcp1++,fcp2++) *fcp1=*fcp2;
			*fcp1=0;
		} else if (*bemptr=='e' || *bemptr=='E') {
			for (fcp1=ss; *fcp1; fcp1++);

			while (IsInCharset(*(--fcp1),charset)/**(--fcp1)==trchr*/); 

			*(fcp1+1)=0;

		} else if (*bemptr=='m' || *bemptr=='M') {
			/* Just compact between 1st & last non-space: */
			for (fcp1=ss; IsInCharset(*fcp1,charset); fcp1++); /* 1st non-space */

			for (fcp3=fcp1; *fcp3; fcp3++);

			while (IsInCharset(*(--fcp3),charset)); /* fcp3 now at last non-space */

			fc1=*(fcp3+1); *(fcp3+1)=0; /* terminate string temporarily */
			for (fcp2=fcp3=fcp1; *fcp3; fcp3++) { /* compact */
				if (!IsInCharset(*(--fcp3),charset) /**fcp3!=trchr*/) 
				{ *fcp2=*fcp3; fcp2++; }
			}
			*fcp3=fc1; /* put the blasted char back */
			for (; *fcp3; fcp2++,fcp3++)  *fcp2=*fcp3; /* Just copy the rest */
			*fcp2=0;
		}
	}
}

void StringTrimSpaceA(char *ss, char *bem) 
{
/* Removes spaces from the beginning and/or end and/or middle of strings */
    char fc1,*fcp1,*fcp2,*fcp3,*bemptr;

    for (fcp1=ss; *fcp1==' '; fcp1++);
    if (!(*fcp1)) { *ss=0; return; }  /* Null or ALL blanks */

    /* Now there's at least one non-space */
    for (bemptr=bem; *bemptr; bemptr++) {
        if (*ss==' ' && (*bemptr=='b' || *bemptr=='B')) {
            for (fcp2=ss; *fcp2==' '; fcp2++);
            for (fcp1=ss; *fcp2; fcp1++,fcp2++) *fcp1=*fcp2;
            *fcp1=0;
        } else if (*bemptr=='e' || *bemptr=='E') {
            for (fcp1=ss; *fcp1; fcp1++);
            while (*(--fcp1)==' '); *(fcp1+1)=0;
        } else if (*bemptr=='m' || *bemptr=='M') {
            /* Just compact between 1st & last non-space: */
            for (fcp1=ss; *fcp1==' '; fcp1++); /* 1st non-space */
            for (fcp3=fcp1; *fcp3; fcp3++);
            while (*(--fcp3)==' '); /* fcp3 now at last non-space */
            fc1=*(fcp3+1); *(fcp3+1)=0; /* terminate string temporarily */
            for (fcp2=fcp3=fcp1; *fcp3; fcp3++) { /* compact */
                if (*fcp3!=' ') { *fcp2=*fcp3; fcp2++; }
            }
            *fcp3=fc1; /* put the blasted char back */
            for (; *fcp3; fcp2++,fcp3++)  *fcp2=*fcp3; /* Just copy the rest */
            *fcp2=0;
        }
    }
}


#ifdef WIN32
unsigned int HexStringToIntegerW(wchar_t *pHexStr)
{
	int iret =0;
	UCHAR *pb = (unsigned char *)&iret;
	static unsigned char hexTable[23] = {0,1,2,3,4,5,6,7,8,9,0,0,0,0, 0,0,0, 10,11,12,13,14,15};
	_wcsupr(pHexStr);
	wchar_t *pstr = pHexStr;
	bool bNegtive=false;
	if(pstr[0]=='+')
	{
		pstr++;
	}
	else if(pstr[0]=='-')
	{
		bNegtive = true;
		pstr++;
	}

	size_t istrlen = wcslen(pstr);
	if(istrlen > 8 || istrlen==0)
	{
		return 0;
	}
	bool bHi=false;
	int i,j;
	for(i=(int)istrlen-1,j=0 ;i>=0;i--)
	{
		if(!bHi)
		{
			pb[j] =hexTable[pstr[i]- '0'];
		}
		else
		{
			pb[j] +=hexTable[pstr[i]- '0']*16;
			j++;
		}
		bHi=!bHi;
	}

	if(bNegtive)
	{
		return (unsigned int)(-iret);
	}
	else
	{
		return (unsigned int)iret;
	}
}

bool HexStringToBytesW(const wchar_t *pBinStr, unsigned char * pBins, int *pLenOfBins)
{
	size_t istrlen = wcslen(pBinStr);
	if(istrlen ==0)
	{
		return false;
	}

	const wchar_t *pbBeg = pBinStr;
	const wchar_t *pbEnd = pBinStr+istrlen;
	while(pbBeg < pbEnd && *pbBeg ==0x0020 ) pbBeg++;
	
	
	istrlen = pbEnd - pbBeg;
	if(istrlen <=0)
	{
		return false;
	}

	int binLen = (int)(istrlen+1)/2;
	
	
	if(pBins==NULL || *pLenOfBins < binLen ) 
	{
		*pLenOfBins = binLen;
		return false;
	}

	unsigned char * pret=pBins;
	
	UCHAR hexTable[23] = {0,1,2,3,4,5,6,7,8,9,0,0,0,0, 0,0,0, 10,11,12,13,14,15};
	int i =0;
	
	bool bHi=true;
	while(pbBeg <pbEnd)
	{
		wchar_t wc = *pbBeg;
		if(wc !=0x0020)
		{
			if(wc>'F')
			{
				wc-='a'-'A';
			}

			if(!bHi)
			{
				pret[i] +=hexTable[wc- '0'];
				i++;
			}
			else
			{
				pret[i] =hexTable[wc-'0']*16;
				
			}
			bHi=!bHi;
		}
		pbBeg++;
	}
	
	*pLenOfBins = i;
	return true;
}


void BytesToStringW(wchar_t *&pBinStr, const unsigned char * pbin, int len,wchar_t seperator)
{
	pBinStr = new wchar_t[len*3+2];
	pBinStr[0]=0;
	if(len==0 || pbin == NULL)
	{
		return;
	}
	int ncLen = 0;
	for(int i=0;i<len;i++)
	{
		if(seperator!=0)
			ncLen += wsprintfW(pBinStr+ncLen,L"%02X%c",pbin[i],seperator);
		else
			ncLen += wsprintfW(pBinStr+ncLen,L"%02X",pbin[i]);
	}
}

void StringTrimSpaceW(wchar_t *ss, wchar_t *bem) 
{
/* Removes spaces from the beginning and/or end and/or middle of strings */
    wchar_t fc1,*fcp1,*fcp2,*fcp3,*bemptr;

    for (fcp1=ss; *fcp1==' '; fcp1++);
    if (!(*fcp1)) { *ss=0; return; }  /* Null or ALL blanks */

    /* Now there's at least one non-space */
    for (bemptr=bem; *bemptr; bemptr++) {
        if (*ss==' ' && (*bemptr=='b' || *bemptr=='B')) {
            for (fcp2=ss; *fcp2==' '; fcp2++);
            for (fcp1=ss; *fcp2; fcp1++,fcp2++) *fcp1=*fcp2;
            *fcp1=0;
        } else if (*bemptr=='e' || *bemptr=='E') {
            for (fcp1=ss; *fcp1; fcp1++);
            while (*(--fcp1)==' '); *(fcp1+1)=0;
        } else if (*bemptr=='m' || *bemptr=='M') {
            /* Just compact between 1st & last non-space: */
            for (fcp1=ss; *fcp1==' '; fcp1++); /* 1st non-space */
            for (fcp3=fcp1; *fcp3; fcp3++);
            while (*(--fcp3)==' '); /* fcp3 now at last non-space */
            fc1=*(fcp3+1); *(fcp3+1)=0; /* terminate string temporarily */
            for (fcp2=fcp3=fcp1; *fcp3; fcp3++) { /* compact */
                if (*fcp3!=' ') { *fcp2=*fcp3; fcp2++; }
            }
            *fcp3=fc1; /* put the blasted char back */
            for (; *fcp3; fcp2++,fcp3++)  *fcp2=*fcp3; /* Just copy the rest */
            *fcp2=0;
        }
    }
}
 
#endif