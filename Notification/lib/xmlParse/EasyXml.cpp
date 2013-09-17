//////////////////////////////////////////////////////////////////////////
// EasyXml.cpp
//////////////////////////////////////////////////////////////////////////
//#include "StdAfx.h"
//#include "//TRACELOG.h"
#include "EasyXml.h"


CEasyXml::CEasyXml(void)
{
    m_pDoc = NULL;
    m_pCurrEle = NULL;
}

CEasyXml::~CEasyXml(void)
{
    if (m_pDoc != NULL)
    {
        delete m_pDoc;
    }
}

CEasyXml::CEasyXml(const string &strXml, XMLLOAD xmlload/* = XML_STR*/)
{
    if (!strXml.empty())
    {
        if (XML_FILE == xmlload)
        {
            m_pDoc = new TiXmlDocument(strXml.c_str());
            m_pDoc->LoadFile();
        }
        else if (XML_STR == xmlload)
        {
            m_pDoc = new TiXmlDocument();
            m_pDoc->Parse(strXml.c_str());
        }
    }
}

bool CEasyXml::Open(const string &strXml, XMLLOAD xmlload/* = XML_STR*/)
{
    if (NULL != m_pDoc)
    {
        delete m_pDoc;
    }

    if (!strXml.empty())
    {
        if (XML_FILE == xmlload)
        {
            m_pDoc = new TiXmlDocument(strXml.c_str());
            return m_pDoc->LoadFile();
        }
        else if (XML_STR == xmlload)
        {
            m_pDoc = new TiXmlDocument();
            m_pDoc->Parse(strXml.c_str());

            TiXmlElement *pElement = m_pDoc->RootElement();
            if (NULL != pElement)
            {
                return true;
            }
        }
    }
    return false;
}

string CEasyXml::GetXml(const string& strIndent/* = ""*/, const string &strLineBreak/* = ""*/)
{
    if (NULL == m_pDoc)
    {
        return "";
    }

    TiXmlPrinter printer;
    printer.SetIndent(strIndent.c_str());
    printer.SetLineBreak(strLineBreak.c_str());
    if(m_pDoc->Accept( &printer ))
    {
        return printer.CStr();
    }
    return "";
}

bool CEasyXml::GenXmlRecord(XMLRECORD &xmlRec)
{
    if (NULL == m_pDoc)
    {
        return false;
    }

    TiXmlElement *pnode = m_pDoc->RootElement();
    pnode = pnode->FirstChildElement();
    while(NULL != pnode)
    {
        map<string, NODERECORD> mapNode;

        string strKey = pnode->Value();
        TiXmlElement *pChild = pnode->FirstChildElement();
        while (NULL != pChild)
        {
            NODERECORD nodeRec;
            GetAttri(pChild, nodeRec.mapAttri);

            TiXmlElement *pGrand = pChild->FirstChildElement();
            while(NULL != pGrand)
            {
                SUBNODE subnode;
                GetAttri(pGrand, subnode.mapAttri);
                subnode.strName = pGrand->Value();
                nodeRec.vecSubNode.push_back(subnode);

                pGrand = pGrand->NextSiblingElement();
            }
            mapNode.insert(make_pair(pChild->Value(), nodeRec));
            pChild = pChild->NextSiblingElement();
        }
        xmlRec.insert(make_pair(strKey, mapNode));
        pnode = pnode->NextSiblingElement();
    }
    return true;
}

bool CEasyXml::Query(const string& strPath, string &strValue)
{
    if (strPath.empty() || NULL == m_pDoc)
    {
        return false;
    }

    TiXmlElement *pElement = FindPath(strPath, m_pDoc->RootElement());
    if (NULL != pElement)
    {
        if (!pElement->NoChildren())
        {
            strValue = pElement->GetText();
        }
        else
        {
            strValue.clear();
        }
        return true;
    }
    return false;
}

bool CEasyXml::QueryAttri(const string& strPath, const string &strAttri, string &strValue)
{
    if (strPath.empty() || NULL == m_pDoc)
    {
        return false;
    }

    TiXmlElement *pElement = FindPath(strPath, m_pDoc->RootElement());
    if (NULL != pElement)
    {
        strValue = pElement->Attribute(strAttri.c_str());
        return true;
    }
    return false;
}

bool CEasyXml::Modify(const string& strPath, const string &strValue)
{
    if (!strPath.empty())
    {
        TiXmlElement *pElement = FindPath(strPath, m_pDoc->RootElement());
        if (NULL != pElement)
        {
            TiXmlNode *pNode = pElement->FirstChild();
            if (NULL != pNode)
            {
                pNode->SetValue(strValue.c_str());
            }
            else
            {
                TiXmlText* pText = new TiXmlText(strValue.c_str()); // 一个指向Text的指针
                pElement->InsertEndChild(*pText);
            }
            return true;
        }
        else
        {
            char szLog[1024];
            sprintf(szLog, "Failed to CEasyXml::Modify. path=[%s], value=[%s].", strPath.c_str(), strValue.c_str());
            ////ERRORLOG(szLog);
            ////ERRORLOG(GetXml().c_str());
        }
    }

    return false;
}

bool CEasyXml::Modify(list<XMLNODE> &lstXmlNode)
{
    list<XMLNODE>::iterator itlst = lstXmlNode.begin();
    for(; itlst != lstXmlNode.end(); ++itlst)
    {
        if(!Modify(*itlst))
        {
            return false;
        }
    }
    return true;
}

bool CEasyXml::ModifyAttri(const string& strPath, const string &strAttri, const string &strValue)
{
    if (strPath.empty() || NULL == m_pDoc)
    {
        return false;
    }

    TiXmlElement *pElement = FindPath(strPath, m_pDoc->RootElement());
    if (NULL != pElement)
    {
        pElement->SetAttribute(strAttri.c_str(), strValue.c_str());
        return true;
    }
    return false;
}

// 找到指定路径的第一个，并返回map
bool CEasyXml::FirstSpecifyNode(const string &strPath, map<string, string> &mapNode)
{
    if (strPath.empty() || NULL == m_pDoc)
    {
        return false;
    }

    TiXmlElement *pElement = FindPath(strPath, m_pDoc->RootElement());
    if (NULL != pElement)
    {
        GetSpecifyNode(pElement, mapNode);
        m_pCurrEle = pElement;
        return true;
    }
    return false;
}

// 找到下一个
bool CEasyXml::NextSpecifyNode(const string &strPath, map<string, string> &mapNode)
{
    if (NULL != m_pCurrEle )
    {
        size_t nPos = strPath.rfind("/");
        if (nPos != string::npos)
        {
            string strEnd = strPath.substr(nPos+1);
            TiXmlElement *pElement = m_pCurrEle->NextSiblingElement(strEnd.c_str());
            if (NULL != pElement)
            {
                GetSpecifyNode(pElement, mapNode);
                m_pCurrEle = pElement;
                return true;
            }
        }
    }
    return false;
}

bool CEasyXml::GetNodesFromCurr(const string &strPath, const string &strSubPath, list<string> &lstNode)
{
    if (NULL == m_pCurrEle)
    {
        return false;
    }

    TiXmlElement *pElement = FindPath(strPath, m_pCurrEle);
    while (NULL != pElement)
    {
        TiXmlElement *pChildElement = pElement->FirstChildElement(strSubPath.c_str());

        while (NULL != pChildElement)
        {
            if (pChildElement->Value() == strSubPath)
            {
                lstNode.push_back(pChildElement->GetText());
            }
            pChildElement = pChildElement->NextSiblingElement(strSubPath.c_str());
        }

        pElement = pElement->NextSiblingElement();
    }
    return true;
}

bool CEasyXml::InsertXml(const string &strPath, CEasyXml &xml)
{
    if (NULL != m_pDoc && !strPath.empty())
    {
        TiXmlElement *pElement = FindPath(strPath, m_pDoc->RootElement());
        if (NULL != pElement)
        {
            if (NULL != pElement->LinkEndChild(xml.GetRootElement()->Clone()))
            {
                return true;
            }
        }
    }
    return false;
}

TiXmlElement *CEasyXml::GetRootElement()
{
    if (NULL != m_pDoc)
    {
        return m_pDoc->RootElement();
    }
    return NULL;
}



//////////////////////////////////////////////////////////////////////////
// private:
//////////////////////////////////////////////////////////////////////////

bool CEasyXml::Modify(XMLNODE &xmlNode)
{
    if (!xmlNode.strKey.empty())
    {
        TiXmlElement *pElement = FindPath(xmlNode.strKey, m_pDoc->RootElement());
        if (NULL != pElement)
        {
            TiXmlNode *pNode = pElement->FirstChild();
            if (NULL != pNode)
            {
                pNode->SetValue(xmlNode.strValue.c_str());
                return true;
            }
            else
            {
                TiXmlText* pText = new TiXmlText(xmlNode.strValue.c_str()); // 一个指向Text的指针
                pElement->InsertEndChild(*pText);
            }
        }
    }
    return false;
}

void CEasyXml::GetAttri(TiXmlElement *pnode, map<string, string> &mapAttri)
{
    TiXmlAttribute* pAttrib = pnode->FirstAttribute();
    while (NULL != pAttrib)
    {
        mapAttri.insert(make_pair(pAttrib->Name(), pAttrib->Value()));
        pAttrib=pAttrib->Next();
    }
}

TiXmlElement *CEasyXml::FindPath(const string &strPath, TiXmlElement *pnode)
{
    string strFront;
    string strExceptFront;

    size_t pos = strPath.find("/");
    if (pos != string::npos)
    {
        strFront = strPath.substr(0, pos);
        strExceptFront = strPath.substr(pos+1);
    }
    else
    {
        strFront = strPath;
    }

    while (NULL != pnode)
    {
        string strValue = pnode->Value();
        if (pnode->Value() == strFront)
        {
            if (strExceptFront.empty())
            {
                return pnode;
            }
            else
            {
                return FindPath(strExceptFront, pnode->FirstChildElement());
            }
        }
        pnode = pnode->NextSiblingElement(strFront.c_str());
    }

    if (NULL != pnode)
    {
        return NULL;
    }

    return NULL;
}

void CEasyXml::GetSpecifyNode(TiXmlElement *pElement, map<string, string> &mapNode)
{
    if (NULL == pElement)
    {
        return;
    }

    map<string, string>::iterator itmapNode = mapNode.begin();
    for (; itmapNode != mapNode.end(); ++itmapNode)
    {
        TiXmlElement *pRes = FindPath(itmapNode->first, pElement->FirstChildElement());
        if (NULL != pRes && !pRes->NoChildren())
        {
            itmapNode->second = pRes->GetText();
        }
        else
        {
            itmapNode->second.clear();
        }
    }
}


bool CEasyXml::ModifyNodeBySequence(const string& strPath, const string& strChildElement, int nSequence, const string& strElementName,  const string& strValue)
{
    TiXmlElement* pElement  = FindPath(strPath,m_pDoc->RootElement());
    if (pElement == NULL)
    {
        return -1;
    }
    TiXmlHandle docHandle( pElement );
    TiXmlElement* child2 = docHandle.Child(strChildElement.c_str(),nSequence).FirstChild( strElementName.c_str()).ToElement();
    if ( child2 )
    {
        child2->FirstChild()->SetValue(strValue.c_str());
        return true;
    }

    return false;
}
