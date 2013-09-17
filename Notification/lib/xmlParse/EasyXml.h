//////////////////////////////////////////////////////////////////////////
// EasyXml.h
//////////////////////////////////////////////////////////////////////////
#ifndef __EASYXML_H_
#define __EASYXML_H_

#include <string>
#include <map>
#include <vector>
#include <list>
#include "tinyxml.h"

using namespace std;

typedef enum
{
	XML_FILE,
	XML_STR,
}XMLLOAD;

typedef struct  
{
	string strKey;
	string strValue;
	map<string, string> mapAttri;
}XMLNODE;

typedef struct  
{
	string strName;
	map<string, string> mapAttri;
}SUBNODE;
typedef struct
{
	map<string, string> mapAttri;
	vector<SUBNODE> vecSubNode;
}NODERECORD;
typedef map<string, map<string, NODERECORD> > XMLRECORD;

class CEasyXml
{
public:
	CEasyXml(void);
	~CEasyXml(void);

	CEasyXml(const string &strXml, XMLLOAD xmlload = XML_STR);
	bool Open(const string &strXml, XMLLOAD xmlload = XML_STR);

public:
	string GetXml(const string& strIndent = "", const string &strLineBreak = "");
	bool GenXmlRecord(XMLRECORD &xmlrec);
	
	bool Query(const string& strPath, string &strValue);
	bool QueryAttri(const string& strPath, const string &strAttri, string &strValue);

	bool Modify(const string& strPath, const string &strValue);
	bool Modify(list<XMLNODE> &lstXmlNode);

	bool ModifyAttri(const string& strPath, const string &strAttri, const string &strValue);

	bool FirstSpecifyNode(const string &strPath, map<string, string> &mapNode);	// 找到指定路径的第一个，并返回map
	bool NextSpecifyNode(const string &strPath, map<string, string> &mapNode);	// 找到下一个

	bool GetNodesFromCurr(const string &strPath, const string &strSubPath, list<string> &lstNode);

	bool InsertXml(const string &strPath, CEasyXml &xml);

	TiXmlElement *GetRootElement();

	inline TiXmlDocument *GetDoc(){return m_pDoc;}
	
	bool ModifyNodeBySequence(const string& strPath, const string& strChildElement, int nSequence, const string& strElementName, const string& strValue);

private:
	TiXmlElement *FindPath(const string &strPath, TiXmlElement *pnode);

	bool Modify(XMLNODE &xmlNode);

	void GetAttri(TiXmlElement *pnode, map<string, string> &mapAttri);

	void GetSpecifyNode(TiXmlElement *pnode, map<string, string> &mapNode);



private:
	TiXmlDocument *m_pDoc;
	TiXmlElement *m_pCurrEle;

};

#endif	//__EASYXML_H_
