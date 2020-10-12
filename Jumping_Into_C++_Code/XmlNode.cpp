#include <map>
#include <vector>
#include <string>
#include "XmlNode.h"

using namespace std;

char XmlNode::TagOpen() const
{
    return _tagOpen;
}

char XmlNode::CloseTagStart() const
{
    return _closeTagStart;
}

char XmlNode::TagClose() const
{
    return _tagClose;
}

string XmlNode::Name() const
{
    return _name;
}

vector<string> XmlNode::Attributes()
{
    vector<string> attributeKeys;
    for (map<string, string>::iterator itr = _attributes.begin(), end = _attributes.end(); itr != end; ++itr)
    {
        attributeKeys.push_back(itr->first);
    }
    return attributeKeys;
}

string XmlNode::AttributeValue(string attribute)
{
    return _attributes[attribute];
}

string XmlNode::InnerText() const
{
    return _innerText;
}

int XmlNode::NumberOfChildren() const
{
    return _children.size();
}

XmlNode *XmlNode::Child(int index)
{
    return _children[index];
}

XmlNode::XmlNode()
{
    _tagOpen = '<';
    _closeTagStart = '/';
    _tagClose = '>';
}

XmlNode::XmlNode(const string &input) : XmlNode()
{
    _name = _textNode;
    _innerText = input;
}

XmlNode::XmlNode(char tagOpen, char tagClose, char nodeClose)
{
    _tagOpen = tagOpen;
    _tagClose = tagClose;
    _closeTagStart = nodeClose;
}

XmlNode::~XmlNode()
{
    for (vector<XmlNode *>::iterator itr = _children.begin(), end = _children.end(); itr != end; ++itr)
    {
        delete *itr;
    }
    _children.clear();
}

XmlNode *XmlNode::createNode(const string &input)
{
    XmlNode *node = new XmlNode();
    node->nodeStart(input);
    return node;
}

XmlNode *XmlNode::createTextNode(const string &input)
{
    XmlNode *node = new XmlNode(input);
    return node;
}

void XmlNode::nodeStart(const string &input)
{
    int startTagOpenIndex = input.find_first_of(_tagOpen);
    int spaceIndex = input.find_first_of(' ', startTagOpenIndex);
    int startTagCloseIndex = input.find_first_of(_tagClose, startTagOpenIndex);
    if (spaceIndex != string::npos && spaceIndex < startTagCloseIndex)
    {
        _name = input.substr(startTagOpenIndex + 1, (spaceIndex - 1) - startTagOpenIndex);
        attributeRead(input.substr(spaceIndex + 1, (startTagCloseIndex - 1) - spaceIndex));
    }
    else
    {
        _name = input.substr(startTagOpenIndex + 1, (startTagCloseIndex - 1) - startTagOpenIndex);
    }

    string closeTag = nodeEnd(_name);
    int endTagOpenIndex = input.find_last_of(closeTag);
    string innerText = input.substr( startTagCloseIndex + 1, (endTagOpenIndex - 1) - startTagCloseIndex - ( closeTag.length() - 1 ) );
    nodeTextRead(innerText);
}

void XmlNode::attributeRead(const string &attributesStream)
{
    string currentKey = "";
    string currentEntry = "";
    bool isInValue = false;
    for (int i = 0; i < attributesStream.length(); i++)
    {
        if (attributesStream[i] == '=')
        {
            currentKey = currentEntry;
            currentEntry.clear();
        }
        else if (attributesStream[i] == '"' && !isInValue)
        {
            isInValue = true;
        }
        else if (attributesStream[i] == '"' && isInValue)
        {
            isInValue = false;
            currentEntry = clearEmpty(currentEntry);
            _attributes[currentKey] = currentEntry;
            currentKey.clear();
            currentEntry.clear();
        }
        else if (attributesStream[i] != '=' &&
                 attributesStream[i] != '"' &&
                 !(attributesStream[i] == ' ' && !isInValue))
        {
            currentEntry += attributesStream[i];
        }
    }
}

void XmlNode::nodeTextRead(const string &innerText)
{
    if (innerText.empty())
    {
        return;
    }
    int startTagOpenIndex = innerText.find_first_of(_tagOpen);
    if (startTagOpenIndex == string::npos)
    {
        _innerText = innerText;
        _innerText = clearEmpty(_innerText);
        return;
    }

    if (startTagOpenIndex > 0)
    {
        _innerText += innerText.substr(0, startTagOpenIndex);
    }

    int openTagCount = 0;
    int tagCount = 0;
    string innerInnerText;
    for (int i = startTagOpenIndex; i < innerText.length(); i++)
    {
        char currentCharacter = innerText[i];
        if (currentCharacter == _tagOpen)
        {
            if (openTagCount == 0 && !_innerText.empty())
            {
                _innerText = clearEmpty(_innerText);
                if (!_innerText.empty())
                {
                    _children.push_back(createTextNode(_innerText));
                    _innerText.clear();
                }
            }
            tagCount++;
            if ( (i + 1) < innerText.length() && innerText[i + 1] == _closeTagStart)
            {
                openTagCount--;
            }
            else
            {
                openTagCount++;
            }
        }
        else if (currentCharacter == _tagClose)
        {
            tagCount--;
        }

        if (openTagCount == 0 && tagCount == 0 && currentCharacter != _tagClose)
        {
            _innerText.push_back(currentCharacter);
            if ( (i + 1) >= innerText.length() && !_innerText.empty() )
            {
                _innerText = clearEmpty(_innerText);
                if (!_innerText.empty())
                {
                    _children.push_back(createTextNode(_innerText));
                    _innerText.clear();
                }
            }
        }
        else
        {
            innerInnerText.push_back(currentCharacter);
        }

        if (currentCharacter == _tagClose && openTagCount == 0)
        {
            _children.push_back(createNode(innerInnerText));
            innerInnerText.clear();
        }
    }
    _innerText = clearEmpty(_innerText);
}


string XmlNode::nodeEnd(const string &nameNode) const
{
    string nodeEndTag;
    nodeEndTag.push_back(_tagOpen);
    nodeEndTag.push_back(_closeTagStart);
    return (nodeEndTag + nameNode + _tagClose);
}

string XmlNode::getTabs(int indentationLevel, const string &spacer) const
{
    string tabs = "";
    string currentSpacer;
    spacer.empty() ? currentSpacer = _spacer : currentSpacer = spacer;
    for (int i = 0; i < indentationLevel; i++)
    {
        tabs += currentSpacer;
    }
    return tabs;
}

string XmlNode::printOpeningTag(XmlNode *node, const string &tabs)
{
    string currentNode = tabs;
    currentNode.push_back(_tagOpen);
    currentNode += node->Name();
    vector<string> attributes = node->Attributes();
    for (vector<string>::iterator itr = attributes.begin(), end = attributes.end(); itr != end; ++itr)
    {
        currentNode += " " + *itr + "=\"" + node->AttributeValue(*itr) + "\"";
    }
    currentNode += _tagClose;
    return currentNode;
}

string XmlNode::printInnerText(XmlNode *node, const string &tabs, const string &currentSpacer)
{
    string currentNode;
    if (!node->InnerText().empty())
    {
        currentNode += '\n' + tabs + currentSpacer;
        currentNode += node->InnerText();
    }
    return currentNode;
}

string XmlNode::printChildNodes(XmlNode *node, int childIndex, int indentLevel)
{
    string currentNode;
    currentNode += '\n';
    currentNode += print(node->Child(childIndex), indentLevel + 1);
    return currentNode;
}

string XmlNode::printClosingTag(XmlNode *node, const string &tabs)
{
    string currentNode = '\n' + tabs;
    currentNode += nodeEnd(node->Name());
    return  currentNode;
}

string XmlNode::print(XmlNode *node, int indentLevel, const string &spacer)
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

string XmlNode::clearEmpty(string &text)
{
    if (text.find_first_not_of(' ') == string::npos)
    {
        return "";
    }
    if (text.find_first_not_of('\t') == string::npos)
    {
        return "";
    }
    return text;
}
