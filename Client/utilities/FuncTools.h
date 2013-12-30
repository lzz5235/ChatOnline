//////////////////////////////////////////////////////////////////////////
// FuncTools.h
//////////////////////////////////////////////////////////////////////////
#ifndef __FUNCTOOLS_H_
#define __FUNCTOOLS_H_
#include <string>
#include <set>
#include <deque>
#include <list>
#include <vector>
#include <map>
#include <QImage>
#include "global.h"
#include <QTextCodec>
using namespace std;

inline QString GBK2UTF8(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB2312");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

    QString g2u = gbk->toUnicode(gbk->fromUnicode(inStr));			  // gbk  convert utf8
	return g2u;
}

inline QString UTF82GBK(const QString &inStr)
{
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

	QString utf2gbk = gbk->toUnicode(inStr.toLocal8Bit());
	return utf2gbk;
}

string  getElement(map<string, string> &from, string key);
int     getElement(map<string, int>&from, string key);
string  getElement(map<int, string> &from, int key);

inline std::string gbk2utf8(const QString &inStr)
{
	return GBK2UTF8(inStr).toStdString();
}

inline QString utf82gbk(const std::string &inStr)
{
	QString str = QString::fromStdString(inStr);
	
	return UTF82GBK(str);
}

// �ַ���תΪʱ��
 unsigned long str2time(const char *str1);
// 
 void formattime(char *pszTime);
// 
// ʱ��תΪ�ַ���
 int time2str(time_t sec_num, char *date_ret);
// 
// ��ȡ��ǰʱ��
 string GetCurrTime();
// 
// ����ʱ��ת��Ϊ��������ʱ��
 string LT2GMT(C_STR strLocaleTime);
// 
// ת��ʱ���ʽ
 string ConvertTimeFormat(C_STR strTime);

// ���÷ָ����ָ����ַ����ֿ�����set��
 void SeperateString(set<string> &setRet, C_STR strParse, LPCSTR lpszDeli);

// ���÷ָ����ָ����ַ����ֿ�����list��
 void SeperateString(list<string> &lstRet, C_STR strParse, LPCSTR lpszDeli);

// ���÷ָ����ָ����ַ����ֿ�����list��
 void SeperateString(list<string> &lstRet, LPSTR lpstr, LPCSTR lpszDeli);

// ���÷ָ����ָ����ַ����ֿ�����vector��
 void SeperateString(vector<string> &vecRet, C_STR strParse, LPCSTR lpszDeli);

// ���÷ָ����ָ����ַ����ֿ�����deque��
 void SeperateString(deque<string> &deqRet, C_STR strParse, LPCSTR lpszDeli);
// 
 string Gen4Digit1();
//ɾ���ַ������޹��ַ�
 bool eraseStrUselessToken(string& strToBeErase, list<char>lstToken);

bool IsDigit2(string str);

string GenCompleteCPID(C_STR strCPID, int nOwnMcuID, C_STR strConfID);

//ת��xml�е�&,<,>,��,���ַ�
bool RplUnRecToken2TransfToken(string &token, const map<string, string> &rplMap);

void itoa(int, char a[]);

QImage convert2Gray(const QString img, QSize size);

#endif //__FUNCTOOLS_H_

