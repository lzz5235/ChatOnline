#ifndef _SIMPLE_XML_H
#define _SIMPLE_XML_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "tinyxml.h"

using namespace std;

const int XMLFILE = 1;
const int XMLSTR  = 2;
const int MODIFY  = 3;
const int QUERY  = 4;

typedef struct  
{
    string strNodeName;//"root"
    string strData;
    string strAttri;
}XMLNODEINFO;

class CSimpleXml
{
public:
    CSimpleXml();
    ~CSimpleXml(void);
    bool OpenXml(const string &strXml, int nXMLType = XMLSTR);
    bool ModifyXml(list<XMLNODEINFO> &lstXmlNodes);
    bool AccessXmlNode(XMLNODEINFO &struNote, int nAccessType = MODIFY);
    bool GetXml(string &strXml);

    // 将xml转换成list<map<string, string> >
    void Xml2Listmap(list<map<string, string> > &lstmapData);

    // 将list<map<string, string> >转换成xml
    void Listmap2Xml(list<map<string, string> > &lstmapData, string &strXml);

    // 将指定节点下的节点装入map，strNode只支持第一层
    void GetSpecifyNode(const string &strNode, map<string, string> &mapNode, TiXmlNode *begin = NULL);

    // 找到指定路径的第一个，并返回map
    bool FirstSpecifyNode(const string &strNode, map<string, string> &mapNode);

    // 找到下一个
    bool NextSpecifyNode(const string &strNode, map<string, string> &mapNode);

    bool ModifyXmlAttri(list<XMLNODEINFO> &lstNode);

    bool ModifyOneAttri(XMLNODEINFO &xmlnode);

    bool AccessXmlAttri(XMLNODEINFO &xmlnode);

    string GetAttri(const string &strPath, const string strAttri = "value");

    bool AddNodes(const string &strPath, list<XMLNODEINFO> &lstnode);

    bool AddOneNode(TiXmlElement **ppNode, list<XMLNODEINFO> &lstnode);

    //add by yinxiao
    bool ModifyXmlAttrContinue(list<XMLNODEINFO> &lstNode);

private:
    string m_strFileName;
    TiXmlDocument *m_pDoc;
    TiXmlElement *m_pRoot;
    string m_strXml;

    TiXmlNode *m_pCurrNode;
};
//*===========add by Brince.S.J========
typedef struct XmlSimpleNode_tag
{
    string szNodeName;
    string szData;
    map<string,string> mpAttribute;
    list<struct XmlSimpleNode_tag*> lsSubNode;
} XmlSimpleNode;

class QSimpleXmlReader
{
public:
    QSimpleXmlReader()
    {
        m_pRootNode = NULL;
        m_pDoc = NULL;
    };

    ~QSimpleXmlReader()
    {
        if(m_pRootNode)
            release();
    };
    //parse xml into XmlSimpleNode*
    bool loadFromFile(const char* strFileName)
    {
        if(strFileName)
        {
            m_pDoc = new TiXmlDocument(strFileName);
            if(!m_pDoc->LoadFile())
            {
                delete m_pDoc;
                m_pDoc = NULL;

                return false;
            }
            m_pRootEle = m_pDoc->RootElement();

            return true;
        }
        return false;
    }

    bool parseXml(const char* strXmlContent)
    {
        if(strXmlContent)
        {
            m_pDoc = new TiXmlDocument();
            if(m_pDoc->Parse(strXmlContent))
            {
                m_pRootEle = m_pDoc->RootElement();
                return true;
            }
            delete m_pDoc;
            m_pDoc = NULL;
        }

        return false;
    }

    //get the root Element
    XmlSimpleNode *rootNode()
    {
        return m_pRootNode;
    }

    //get the first Element by the specific path
    XmlSimpleNode *getFirstNode(const char* szXmlNodePath)
    {
        return NULL;
    }

    //release memory
    void release()
    {

    }

protected:
    void parseEleAttribute(const TiXmlElement* ele,XmlSimpleNode *node)
    {
        if(ele && node)
        {
            const TiXmlAttribute* att = ele->FirstAttribute();
            while(att)
            {
                node->mpAttribute.insert(make_pair(att->Name(),att->Value()));
                att = att->Next();
            }
        }
    }

    void parseEleChildren(const TiXmlElement* ele,XmlSimpleNode *node)
    {
        if(ele && node)
        {
            node->szNodeName = ele->Value();
            parseEleAttribute(ele,node);
        }
    }

private:
    XmlSimpleNode *m_pRootNode;
    TiXmlElement  *m_pRootEle;
    TiXmlDocument *m_pDoc;
};
//===================================*/
#endif // _SIMPLE_XML_H
