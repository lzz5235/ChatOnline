#include "FuncTools.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QDebug>

//////////////////////////////////////////////////////////////////////////
// 函数实现
//////////////////////////////////////////////////////////////////////////


// 工具函数 
unsigned long str2time(const char *str1)
{
	int time_int;
	unsigned long time_long;
	char time_char[20];
	struct tm tmptr;

	strcpy(time_char,str1);
	time_char[4]=0;

	time_int=atoi(time_char)-1900;

	tmptr.tm_year=time_int;

	strcpy(time_char,str1+4);
	time_char[2]=0;
	tmptr.tm_mon=atoi(time_char)-1;

	strcpy(time_char,str1+6);
	time_char[2]=0;
	tmptr.tm_mday=atoi(time_char);

	strcpy(time_char,str1+8);
	time_char[2]=0;
	tmptr.tm_hour=atoi(time_char);

	strcpy(time_char,str1+10);
	time_char[2]=0;
	tmptr.tm_min=atoi(time_char);

	strcpy(time_char,str1+12);
	time_char[2]=0;
	tmptr.tm_sec=atoi(time_char);

	tmptr.tm_isdst=0;
	time_long=mktime(&tmptr);

	return (time_long);
}
 
int time2str(time_t sec_num, char *date_ret)
{
	/*根据时间的秒数返回字符串格式的日期时间*/
	/*date_ret:日期  time_ret:时间 */
	struct tm *tmptr;

	tmptr=localtime(&sec_num);
	++tmptr->tm_mon;
	if (tmptr->tm_year < 40) {
		tmptr->tm_year+=2000;
	}
	else {
		tmptr->tm_year+=1900;
	}
	//strcpy(date_ret,"");

	sprintf(date_ret,"%4d%02d%02d%02d%02d%02d",tmptr->tm_year,
		tmptr->tm_mon,
		tmptr->tm_mday,
		tmptr->tm_hour,
		tmptr->tm_min,
		tmptr->tm_sec);
	return 0;
}

void formattime(char *pszTime)
{
	time_t sec_num;
	time(&sec_num);
	sec_num -= 8 * 60 * 60;

	struct tm *tmptr;
	tmptr=localtime(&sec_num);
	++tmptr->tm_mon;
	if (tmptr->tm_year < 40) {
		tmptr->tm_year+=2000;
	}
	else {
		tmptr->tm_year+=1900;
	}

	sprintf(pszTime,"%02d:%02d:%02d.479 ",
		tmptr->tm_hour,
		tmptr->tm_min,
		tmptr->tm_sec);
}

// // 获取当前时间
string GetCurrTime()
{
	char szTime[15];
	time_t curtime;
	time(&curtime);
	time2str(curtime, szTime);
	szTime[14] = '\0';

	return string(szTime);
}
// 
// // 本地时间转换为格林威治时间
string LT2GMT(C_STR strLocaleTime)
{
	unsigned long ltime = str2time(strLocaleTime.c_str());
	ltime -= 8 * 60 * 60;
	char szTime[15];
	time2str(ltime, szTime);
	return string(szTime);
}
// 
// // 转换时间格式
string ConvertTimeFormat(C_STR strTime)
{
	LPCSTR lpstr = strTime.c_str();
	char szTime[32];
	memset(szTime, 0, 32);
    sprintf(szTime, "%c%c%c%c-%c%c-%c%c %c%c:%c%c:%c%c", lpstr[0], lpstr[1], lpstr[2], lpstr[3],
		lpstr[4], lpstr[5], 
		lpstr[6], lpstr[7], 
		lpstr[8], lpstr[9], 
		lpstr[10], lpstr[11], 
		lpstr[12], lpstr[13]);
	return string(szTime);
}
// 
// LPCSTR PrintHex(LPCSTR lpstr, LPSTR lpstrDest)
// {
// 	while (*lpstr != '\0')
// 	{
// 		char szTmp[16];
// 		sprintf(szTmp, "%02x", *lpstr);
// 		strcat(lpstrDest, szTmp);
// 		lpstr++;			
// 	}
// 	return lpstrDest;
// }
// 
// // 将用分隔符分隔的字符串分开放入set中
void SeperateString(set<string> &setRet, C_STR strParse, LPCSTR lpszDeli)
{

	LPSTR lpstr = new char[strParse.length() + 1];
	strcpy(lpstr, strParse.c_str());
	LPSTR lpszOne = strtok(lpstr, lpszDeli);
	while (NULL != lpszOne)
	{
		setRet.insert(lpszOne);
		lpszOne = strtok(NULL, lpszDeli);
	}
	delete[] lpstr;

}
// 
// // 将用分隔符分隔的字符串分开放入list中
void SeperateString(list<string> &lstRet, C_STR strParse, LPCSTR lpszDeli)
{

	LPSTR lpstr = new char[strParse.length() + 1];
	strcpy(lpstr, strParse.c_str());
	LPSTR lpszOne = strtok(lpstr, lpszDeli);
	while (NULL != lpszOne)
	{
		lstRet.push_back(lpszOne);
		lpszOne = strtok(NULL, lpszDeli);
	}
	delete[] lpstr;

}
// 
// // 将用分隔符分隔的字符串分开放入list中
void SeperateString(list<string> &lstRet, LPSTR lpstr, LPCSTR lpszDeli)
{

	LPSTR lpszOne = strtok(lpstr, lpszDeli);
	while (NULL != lpszOne)
	{
		lstRet.push_back(lpszOne);
		lpszOne = strtok(NULL, lpszDeli);
	}

}
// 
// // 将用分隔符分隔的字符串分开放入vector中
void SeperateString(vector<string> &vecRet, C_STR strParse, LPCSTR lpszDeli)
{

	LPSTR lpstr = new char[strParse.length() + 1];
	strcpy(lpstr, strParse.c_str());
	LPSTR lpszOne = strtok(lpstr, lpszDeli);
	while (NULL != lpszOne)
	{
		vecRet.push_back(lpszOne);
		lpszOne = strtok(NULL, lpszDeli);
	}
	delete[] lpstr;

}
// 
// // 将用分隔符分隔的字符串分开放入deque中
// void SeperateString(deque<string> &deqRet, C_STR strParse, LPCSTR lpszDeli)
// {
// 
// 	LPSTR lpstr = new char[strParse.length() + 1];
// 	strcpy(lpstr, strParse.c_str());
// 	LPSTR lpszOne = strtok(lpstr, lpszDeli);
// 	while (NULL != lpszOne)
// 	{
// 		deqRet.push_back(lpszOne);
// 		lpszOne = strtok(NULL, lpszDeli);
// 	}
// 	delete[] lpstr;
// 
// }
// 
// // 返回加过后的时间
// string PlusTime(C_STR strTime, int nMin)
// {
// 	unsigned long ltime = str2time(strTime.c_str());
// 	ltime += nMin * 60;
// 	char szTime[15];
// 	time2str(ltime, szTime);
// 	return szTime;
// }
// 
// // 前向时间取整，如，1：29 = 1：00，1：31 = 1：30
// string FrontTime(C_STR strTime)
// {
// 	unsigned long ltime = str2time(strTime.c_str());
// 	int nElse = ltime % (30 * 60);
// 	ltime -= nElse;
// 	char szTime[15];
// 	time2str(ltime, szTime);
// 	return szTime;
// }
// 
// // 生成一个递增的MessageId
// string MakeMessageId()
// {
// 	static long lMsgId = 100;
// 
// 	//EnterCriticalSection(&g_csMsgId);
// 	char szDigit[16];
// 	lMsgId++;
// 	long lCurrMsgId = lMsgId % 65535;
// 	sprintf(szDigit, "%ld", lCurrMsgId);
// 	//LeaveCriticalSection(&g_csMsgId);
// 
// 	return string(szDigit);
// }
// 
// string Gen4Digit()
// {
// 
// 	static long l4digit = atoi(GetCurrTime().substr(8, 4).c_str());
// 	if (++l4digit > 9999)
// 	{
// 		l4digit = atoi(GetCurrTime().substr(8, 4).c_str());
// 	}
// 	
// 	char szDigit[16];
// 	_itoa(l4digit, szDigit, 10);
// 
// 	
// 	return szDigit;
// }
//
// //add by wxg preDefine
static int g_nID = 0;
string Gen4Digit1()
{
	if (g_nID == 0)
	{
		srand((unsigned)time(NULL));
                g_nID = rand() % 10000;
	}
	else
        {
            srand((unsigned)time(NULL));
            g_nID += rand() % 10000;
	}
	if (g_nID >= 9999)
	{
		srand((unsigned)time(NULL));
                g_nID = rand() % 10000;
	}
	char szDigit[16];
        sprintf(szDigit, "%4d", g_nID);
	
	return szDigit;
}
// 
// 
// // 查找在list<string>中
// list<string>::iterator FindList(list<string> &lst, C_STR str)
// {
// 	list<string>::iterator itlst = lst.begin();
// 	for (; itlst != lst.end(); ++itlst)
// 	{
// 		if (*itlst == str)
// 		{
// 			return itlst;
// 		}
// 	}
// 	return itlst;
// }
// 
void UnicodeToUTF_8(char* pOut, const wchar_t* pText)
{
    // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
    char* pchar = (char *)pText;
    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));
}

void UnicodeToGB2312(char* pOut, const wchar_t uData)
{
    //WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(wchar_t),NULL,NULL);
}

void Gb2312ToUnicode(wchar_t* pOut, const char *gbBuffer)
{
    //MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
}

 int Ansi2UTF8(char *pIn)
 {
//    DWORD dwBufLen = MultiByteToWideChar(CP_ACP, 0, pIn, -1, NULL, 0);
//    LPWSTR lpwBuf = new wchar_t[dwBufLen];
//    if( lpwBuf==NULL )
//            return 0;
//    dwBufLen = MultiByteToWideChar(CP_ACP,0,pIn,-1,lpwBuf,dwBufLen);
//
//    dwBufLen = WideCharToMultiByte(CP_UTF8, 0, lpwBuf, -1, NULL, 0, NULL, NULL);
//
//    LPSTR lpszUtf8= new char[dwBufLen];
//    if( lpszUtf8==NULL )
//    {
//        delete [] lpwBuf;
//        return 0;
//    }
//    dwBufLen = WideCharToMultiByte(CP_UTF8, 0, lpwBuf, -1, lpszUtf8, dwBufLen, NULL, NULL);
//    memcpy(pIn,lpszUtf8,dwBufLen);
//
//    delete [] lpwBuf;
//    delete [] lpszUtf8;
//
//    return dwBufLen;
    return 0;
}

void UTF82Ansi(char *pszBuf)
{
//    wchar_t wcsBuf[102400];
//    MultiByteToWideChar(CP_UTF8, 0, pszBuf, strlen(pszBuf)+1, wcsBuf, 102400);
//    UnicodeToAnsi(pszBuf, wcsBuf, 102400);
}

void GB2312ToUTF_8(string& pOut, const char *pText, int pLen)
{
    char buf[4];
    int nLength = pLen* 3;
    char* rst = new char[nLength];

    memset(buf,0,4);
    memset(rst,0,nLength);

    int i = 0;
    int j = 0;
    while(i < pLen)
    {
        //如果是英文直接复制就可以
        if( *(pText + i) >= 0)
        {
            rst[j++] = pText[i++];
        }
        else
        {
            wchar_t pbuffer;
            //Gb2312ToUnicode(&pbuffer,pText+i);

            //UnicodeToUTF_8(buf,&pbuffer);

            unsigned short int tmp = 0;
            tmp = rst[j] = buf[0];
            tmp = rst[j+1] = buf[1];
            tmp = rst[j+2] = buf[2];

            j += 3;
            i += 2;
        }
    }
    rst[j] = '\0';

    //返回结果
    pOut = rst;
    delete []rst;

    return;
}

// //启动进程
// int StartProcess(const char *pszExeName, char *pszUrl)
// {
// 	STARTUPINFOA si;
// 	PROCESS_INFORMATION pi;
// 	ZeroMemory( &pi, sizeof(pi) );
// 	ZeroMemory( &si, sizeof(si) );
// 	si.cb = sizeof(si);
// 	si.dwFlags = STARTF_USESHOWWINDOW;
// 	si.wShowWindow = SW_HIDE;
// 
// 	char szUrl[256];
// 	sprintf(szUrl, "%s %s", pszExeName, pszUrl);
// // 	if(CreateProcessA(NULL, szUrl, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
// // 	{
// // 		CloseHandle( pi.hProcess );
// // 		CloseHandle( pi.hThread );
// // 		return 0;
// // 	}
// // 	else
// // 	{
// // 		return -1;
// // 	}
// 	return 0;
// }
// 
// LPSTR strerror(LPSTR lpszBuf) 
// { 
// 	LPVOID lpMsgBuf;
// 	DWORD dw = GetLastError(); 
// 
// // 	FormatMessageA(
// // 		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
// // 		FORMAT_MESSAGE_FROM_SYSTEM,
// // 		NULL,
// // 		dw,
// // 		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
// // 		(LPSTR) &lpMsgBuf,
// // 		0, NULL );
// 
// 	sprintf(lpszBuf, 
// 		"failed with error %d: %s", 
// 		dw, lpMsgBuf); 
// 
// 	LocalFree(lpMsgBuf);
// 	return lpszBuf;
// }
// 
// wchar_t *AnsiToUnicode(wchar_t *pszwDest, const char *pszSource, int len)
// {
// 	MultiByteToWideChar( CP_ACP, 0, pszSource, strlen(pszSource)+1, pszwDest, len);
// 	return pszwDest;
// }
// 
// char *UnicodeToAnsi(char *pszDest, const wchar_t *pszwSource, int len)
// {
// 	WideCharToMultiByte( CP_ACP, 0, pszwSource, wcslen(pszwSource)+1, pszDest, len, NULL, NULL);
// 	return pszDest;
// }
// 
// string GetSelfName()
// {
// 	char szAppPath[MAX_PATH + 1];
// 	string strFile;
// // 	if(::GetModuleFileNameA(NULL, szAppPath, MAX_PATH) > 0)
// // 	{
// // 		char drive[10];
// // 		char dir[256];
// // 		char fname[128];
// // 		char ext[10];
// // 		_splitpath( szAppPath, drive, dir, fname, ext );
// // 		strFile = drive;
// // 		strFile += dir;
// // 		
// // 		return fname;
// //	}
// 	return "";
// }
// 
// string GenRelogin(int nMcuID, C_STR strIP, C_STR strUsername, C_STR strPasswd, int nPort, C_STR strUrl)
// {
// 	// 发重新登录命令
// 	char szBuf[512];
// 	sprintf(szBuf, "x7|%d|%s|%s|%s|%d|%s\n", nMcuID, strIP.c_str(), strUsername.c_str(), strPasswd.c_str(), nPort, strUrl.c_str());
// 
// 	char szCmd[768];
// 	sprintf(szCmd, "t00000000010000000001%.5d%s", strlen(szBuf), szBuf);
// 	return szCmd;
// }
// 
// //连接到...
// // int ConnectTo(const char *pszIP, int nPort)
// // {
// // 
// // 	SOCKET confd = socket(AF_INET, SOCK_STREAM, 0);
// // 
// // 	//服务器地址
// // 	sockaddr_in addrServ;
// // 	addrServ.sin_family = AF_INET;
// // 	addrServ.sin_port = htons(nPort); //保证字节顺序
// // 	addrServ.sin_addr.s_addr = inet_addr(pszIP);
// // 
// // 	char szDebug[1024];
// // 	sprintf(szDebug, "connect to ip is [%s], port is [%d]", pszIP, nPort);
// // 	int nRet = connect(confd, (sockaddr*)&addrServ, sizeof(sockaddr));
// // 	if (nRet == -1)
// // 	{
// // 		char szLog[LOG_LEN];
// // 		char szError[LOG_LEN];
// // 		sprintf(szLog, "connect error: [%s]. ip is [%s], port is [%d]", strerror(szError), pszIP, nPort);
// // 		closesocket(confd);
// // 		return -1;
// // 	}
// // 	return confd;
// // }
// 
// // int XSend(int sockfd, LPCSTR lpszData, size_t nLength)
// // {
// // 	int nRet = send(sockfd, lpszData, nLength, 0);
// // 	if (-1 == nRet)
// // 	{
// // 		char szLog[LOG_LEN];
// // 		//sprintf(szLog, "Failed to send data. Error code is %d.", WSAGetLastError());
// // 		return -1;
// // 	}
// // 	return nRet;
// // }
// 
// // int XTrySend(int &sockfd, LPCSTR lpszData, size_t nLength, LPCSTR lpszIP, int nPort)
// // {
// // 	if(sockfd < 0)
// // 	{
// // 		sockfd = ConnectTo(lpszIP, nPort);
// // 		if (sockfd < 0)
// // 		{
// // 			return -1;
// // 		}
// // 	}
// // 	int nRet = XSend(sockfd, lpszData, nLength);
// // 	if (nRet < 0)
// // 	{
// // 		sockfd = ConnectTo(lpszIP, nPort);
// // 		return XSend(sockfd, lpszData, nLength);
// // 	}
// // 	return nRet;
// // }
// 
// 整型转到字符串
// string i2a(int n)
// {
// 	char szBuf[32];
// 	_itoa(n, szBuf, 10);
// 	return szBuf;
// }


// a2u
// string A2U(C_STR strAnsi)
// {
// 	char szUft8Buf[1024]={0};
// 	//memset(szUft8Buf, 0, 1024);
// 	strcpy_s(szUft8Buf, 1024, strAnsi.c_str());
// 	Ansi2UTF8(szUft8Buf);
// 	return szUft8Buf;
// }

bool IsDigit2(string str) 
{ 
    for(unsigned int i=0;i<str.size();i++)
    {
        if ((str.at(i)>'9') || (str.at(i)<'0') )
        {
            return false;
        }
    }
    return true;
} 

// 生成完整的连接点ID，构成为[McuID + "_mcu_" + 所属McuID + "_" + ConfID]
string GenCompleteCPID(C_STR strCPID, int nOwnMcuID, C_STR strConfID)
{
	char szID[128];
	if (strCPID.empty())
	{
		//DEBUGONE("请检查MCU信令地址配置");
		return "";
	}
	sprintf(szID, "%s_mcu_%d_%s", strCPID.c_str(), nOwnMcuID, strConfID.c_str());
	return szID;
}

bool eraseStrUselessToken(string& strToBeErase, list<char> lstToken)
{
    list<char>::iterator itToken = lstToken.begin();
    if(itToken == lstToken.end())
    {
        return false;
    }
    for(; itToken != lstToken.end(); ++itToken)
    {
        int iPos = strToBeErase.find(*itToken);
        while(iPos)
        {
            strToBeErase.erase(iPos, 1);
            iPos = strToBeErase.find(*itToken);
            if(-1 == iPos)
            {
                break;
            }
        }
    }
    return true;
}

bool RplUnRecToken2TransfToken(string &token, const map<string, string> &rplMap)
{
    map<string, string>::const_iterator it = rplMap.begin();
    while(it != rplMap.end())
    {
        while(int iPos = token.find((*it).first))
        {
            if(-1 != iPos)
            {
                token.replace(iPos, strlen((*it).first.c_str()), (*it).second);
            }
            break;
        }
        ++it;
    }
}

//positive number
void itoa(int i, char a[])
{
    int sign = 0;
    int half;
    do
    {
        a[sign++] = i%10 + '0';
    }while(i/=10);
    a[sign] = '\0';

    printf("before reorder %s \n", a);

    int mod = sign % 2;
    half = sign/2;

    for(int i = 0; i < half; i++, sign--)
    {
        char swap;
        swap = a[i];
        a[i] = a[sign - 1];
        a[sign - 1] = swap;
    }
}

string getElement(map<string, string> &from, string key)
{
    map<string, string>::iterator it = from.begin();
    if(it == from.end())
        return "";

    it = from.find(key);
    if(it != from.end())
    {
        qDebug() << " element is " << it->second.c_str();
        return it->second;
    }
    else
        return "";
}

int getElement(map<string, int> &from, string key)
{
    map<string, int>::iterator it = from.begin();
    if(it == from.end())
        return -1;

    it = from.find(key);
    if(it != from.end())
    {
        qDebug() << "element is " << it->second << "type is " << it->first.c_str();
        return it->second;
    }
    else
        return -1;
}

string  getElement(map<int, string> &from, int key)
{
    map<int, string>::iterator it = from.begin();
    if(it == from.end())
        return "";

    it = from.find(key);
    if(it != from.end())
    {
        qDebug() << "element is " << it->second.c_str() << "type is " << it->first;
        return it->second;
    }
    else
        return "";
}

QImage convert2Gray(const QString img, QSize size)
{
    QImage  image;
    image = QImage(img).scaled(size.width(), size.height());

    int w,h;
    w = image.width();
    h = image.height();
    QImage iGray(w,h,QImage::Format_RGB32);

    for(int i=0; i < size.width(); i++)
    {
        for(int j=0; j < size.height(); j++)
        {
            QRgb pixel = image.pixel(i, j);
            int gray = qGray(pixel);
            QRgb grayPixel = qRgb(gray,gray,gray);
            iGray.setPixel(i,j,grayPixel);
        }
    }

    return iGray;
}






