#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "XmlNode.h"

using namespace std;

string readXMLFileAsStream(string &fileName);

int main()
{
    string xmlToString;
    string xmlDOMStream;
    string fileName;
    XmlNode *root;
    vector<string> fileNames =
    {
        "addresses",
        "books",
        "attributesSample"
    };

    for(vector<string>::iterator itr = fileNames.begin(), end = fileNames.end(); itr != end; ++itr)
    {
        cout << "Reading & parsing " << *itr << ".xml\n";
        xmlDOMStream = readXMLFileAsStream(*itr);
        if (!xmlDOMStream.empty())
        {
            root = XmlNode::createNode(xmlDOMStream);
            cout << "Printing XML object...\n\n";
            xmlToString = root->print();
            cout << xmlToString;
            delete root;
        }
        cout << "\n\n";
    }
}

string readXMLFileAsStream(string &fileName)
{
    cout << "Opening XML file " << fileName << '\n';
    ifstream fileReader(fileName + ".xml");
    if (!fileReader.is_open())
    {
        cout << "Could not open file!" << '\n';
        return "";
    }
    cout << "File is opened!\n";

    cout << "Reading file...\n";
    string stream;
    string line;
    while (getline(fileReader, line, '\n'))
    {
        stream += line;
    }

    return stream;
}
