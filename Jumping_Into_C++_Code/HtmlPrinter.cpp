#include <string>
#include "HtmlPrinter.h"

using namespace std;

HtmlPrinter *HtmlPrinter::createNode(const string &XmlDOMStream)
{
    HtmlPrinter *node = new HtmlPrinter(XmlDOMStream);
    return node;
}

HtmlPrinter::HtmlPrinter(const string &XmlDOMStream)
{
    nodeStart(XmlDOMStream);
}

string HtmlPrinter::print(XmlNode *node, int indentLevel, const string &spacer)
{
    string currentSpacer;
    spacer.empty() ? currentSpacer = _spacer : currentSpacer = spacer;
    string tabs = getTabs(indentLevel, currentSpacer);

    string currentNode = printOpeningTag(node, tabs);

    currentNode += printInnerText(node, tabs, currentSpacer);

    int children = node->NumberOfChildren();
    for (int i = 0; i < children; i++)
    {
        currentNode += printChildNodes(node, i, indentLevel);
    }

    currentNode += printClosingTag(node, tabs);

    return currentNode;
}

string HtmlPrinter::printOpeningTag(XmlNode *node, const string &tabs)
{
    string currentNode;
    if (node->Name() == _textNode)
    {
        return "";
    }
    if (node->Name() == "html")
    {
        return "";
    }
    if (node->Name() == "br")
    {
        return "";
    }
    if (node->Name() == "a")
    {
        return "";
    }
    if (node->Name() == "ul")
    {
        return "\n";
    }
    if (node->Name() == "ol")
    {
        return "\n";
    }
    if (node->Name() == "li")
    {
        return "";
    }
    if (node->Name() == "b")
    {
        return "*";
    }
    if (node->Name() == "i")
    {
        return "_";
    }
    if (node->Name() == "body")
    {
        currentNode = "\n" + tabs;
        currentNode.push_back(TagOpen());
        currentNode += node->Name() + TagClose() + '\n';
        return currentNode;
    }
    return XmlNode::printOpeningTag(node, tabs);
}

string HtmlPrinter::printClosingTag(XmlNode *node, const string &tabs)
{
    if (node->Name() == _textNode)
    {
        return "";
    }
    if (node->Name() == "html")
    {
        return "";
    }
    if (node->Name() == "br")
    {
        return "";
    }
    if (node->Name() == "a")
    {
        return "";
    }
    if (node->Name() == "ul")
    {
        return "";
    }
    if (node->Name() == "ol")
    {
        return "";
    }
    if (node->Name() == "li")
    {
        return "";
    }
    if (node->Name() == "b")
    {
        return "*";
    }
    if (node->Name() == "i")
    {
        return "_";
    }
    return XmlNode::printClosingTag(node, tabs);
}

string HtmlPrinter::printInnerText(XmlNode *node, const string &tabs, const string &currentSpacer)
{
    if (node->Name() == _textNode)
    {
        return node->InnerText();
    }
    if (node->Name() == "head")
    {
        return "";
    }
    if (node->Name() == "br")
    {
        return "\n";
    }
    if (node->Name() == "b")
    {
        return node->InnerText();
    }
    if (node->Name() == "i")
    {
        return node->InnerText();
    }
    if (node->Name() == "ul")
    {
        return "";
    }
    if (node->Name() == "ol")
    {
        return "";
    }
    if (node->Name() == "li")
    {
        return node->InnerText() + '\n';
    }
    if (node->Name() == "a")
    {
        return node->InnerText() + '(' + node->AttributeValue("href") + ')';
    }
    return XmlNode::printInnerText(node, tabs, currentSpacer);
}

string HtmlPrinter::printChildNodes(XmlNode *node, int childIndex, int indentLevel)
{
    string currentNode;
    XmlNode *childNode = node->Child(childIndex);
    if (node->Name() == _textNode)
    {
        return "";
    }
    if (node->Name() == "html")
    {
        return print(childNode, indentLevel + 1);
    }
    if (node->Name() == "head")
    {
        return "";
    }
    if (node->Name() == "b")
    {
        return print(childNode);
    }
    if (node->Name() == "i")
    {
        return print(childNode);
    }
    if (node->Name() == "a")
    {
        return print(childNode);
    }
    if (node->Name() == "ul" && childNode->Name() == "li")
    {
        string tabs = getTabs(indentLevel, _spacer);
        currentNode += tabs;
        currentNode += "* ";
        currentNode += print(childNode, indentLevel + 1);
        return currentNode;
    }
    if (node->Name() == "ol" && childNode->Name() == "li")
    {
        string tabs = getTabs(indentLevel, _spacer);
        currentNode += tabs;
        currentNode += to_string(childIndex + 1) + ". ";
        currentNode += print(childNode, indentLevel + 1);
        return currentNode;
    }

    currentNode += print(childNode, indentLevel + 1);
    return currentNode;
}
