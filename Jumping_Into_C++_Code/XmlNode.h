#pragma once
#ifndef XMLNODE_H_
#define XMLNODE_H_

#include <map>
#include <vector>
#include <string>

class XmlNode
{
public:
    char TagOpen() const;
    char CloseTagStart() const;
    char TagClose() const;
    std::string Name() const;
    std::vector<std::string> Attributes();
    std::string AttributeValue(std::string attribute);
    std::string InnerText() const;
    int NumberOfChildren() const;
    XmlNode *Child(int index);

    XmlNode();
    XmlNode(const std::string &input);
    XmlNode(char tagOpen, char tagClose, char nodeClose);
    virtual ~XmlNode();

    static XmlNode *createNode(const std::string &input);
    void nodeStart(const std::string &input);
    virtual std::string print(XmlNode *node, int indentLevel = 0, const std::string &spacer = "");
protected:
    const std::string _spacer = "  ";
    const std::string _textNode = "#text";

    virtual std::string printOpeningTag(XmlNode *node, const std::string &tabs = "");
    virtual std::string printClosingTag(XmlNode *node, const std::string &tabs = "");
    virtual std::string printInnerText(XmlNode *node, const std::string &tabs = "", const std::string &currentSpacer = "");
    virtual std::string printChildNodes(XmlNode *node, int childIndex, int indentLevel);

    std::string nodeEnd(const std::string &nameNode) const;
    std::string getTabs(int indentationLevel, const std::string &spacer = "") const;
private:
    char _tagOpen;
    char _closeTagStart;
    char _tagClose;
    std::string _name;
    std::map<std::string, std::string> _attributes;
    std::vector<XmlNode *> _children;
    std::string _innerText;

    static XmlNode *createTextNode(const std::string &input);
    void attributeRead(const std::string &attributesStream);
    void nodeTextRead(const std::string &innerText);
    static std::string clearEmpty(std::string &text);
};

#endif
