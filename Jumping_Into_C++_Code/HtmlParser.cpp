#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "XmlNode.h"
#include "HtmlPrinter.h"

using namespace std;

string readFileAsStream(const string &fileName, const string &fileExtension);
int writeToTextFile(const string &fileName, const string &content);

int main()
{
    string XmlToString;
    string XmlDOMStream;
    HtmlPrinter *root;
    map<string, string> files;
    files["addresses"] = "xml";
    files["books"] = "xml";
    files["attributesSample"] = "xml";
    files["sampleHTML"] = "html";

    for (map<string, string>::iterator itr = files.begin(), end = files.end(); itr != end; ++itr)
    {
        string fileName = itr->first;
        string fileExtension = itr->second;
        cout << "Reading & parsing " << fileName << "." << fileExtension << "\n";
        XmlDOMStream = readFileAsStream(fileName, fileExtension);
        if (!XmlDOMStream.empty())
        {
            root = HtmlPrinter::createNode(XmlDOMStream);
            cout << "Printing XML object...\n\n";
            XmlToString = root->print(root);
            writeToTextFile(fileName + "_output", XmlToString);
            cout << XmlToString;
            delete root;
        }
        cout << "\n\n";
    }
}

string readFileAsStream(const string &fileName, const string &fileExtension)
{
    cout << "Opening '" << fileExtension << "' file " << fileName << '\n';
    ifstream fileReader(fileName + "." + fileExtension);
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

int writeToTextFile(const string &fileName, const string &content)
{
    cout << "Writing file to text format..." << '\n';
    ofstream fileWriter(fileName + ".txt");
    if (!fileWriter.is_open())
    {
        cout << "Could not open file!" << '\n';
        return 1;
    }

    fileWriter << content;
    return 0;
}
