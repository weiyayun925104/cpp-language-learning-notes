#pragma once
#ifndef HTMLPRINTER_H_
#define HTMLPRINTER_H_

#include <string>
#include "XmlNode.h"

class HtmlPrinter : public XmlNode
{
public:
    HtmlPrinter(const std::string &XmlDOMStream);

    static HtmlPrinter *createNode(const std::string &input);
    std::string print(XmlNode *node, int indentLevel = 0, const std::string &spacer = "");
protected:
    std::string printOpeningTag(XmlNode *node, const std::string &tabs = "");
    std::string printClosingTag(XmlNode *node, const std::string &tabs = "");
    std::string printInnerText(XmlNode *node, const std::string &tabs = "", const std::string &currentSpacer = "");
    std::string printChildNodes(XmlNode *node, int childIndex, int indentLevel);
};

#endif
