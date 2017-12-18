#include <iostream>
#include <getopt.h>
#include "MyVisitor.h"

//function for saving xml file to outputPath
bool saveFile(TiXmlDocument *document, std::string outputPath) {
    std::cout << "Saving xml document to " << outputPath << std::endl;

    if (!document->SaveFile(outputPath)) {
        std::cout << "Bad output file!" << std::endl;
        return false;
    }

    std::cout << "Saving successfully!" << std::endl;
    return true;
}

//function for loading xml file from inputPath
bool loadFile(TiXmlDocument *document, std::string inputPath) {
    std::cout << "Loading xml document from " << inputPath << std::endl;

    if (!document->LoadFile(inputPath)) {
        std::cout << "Bad input file!" << std::endl;
        return false;
    }

    std::cout << "Loading successfully!" << std::endl;
    return true;
}

void parseArgs(int argc, char *argv[], std::string &inputPath, std::string &outputPath, std::string &operationType) {

    //list of arguments
    static struct option arguments[]{
            {"in",        1, 0, 'I'},
            {"out",       1, 0, 'O'},
            {"operation", 1, 0, 'T'},
            {0,           0, 0, 0}
    };

    std::string argString = "in:out:operation:";

    //result of getting argument
    int result;
    //index of current argument
    int argIndex;
    //get all argument in array arguments
    while ((result = getopt_long(argc, argv, argString.c_str(), arguments, &argIndex)) != -1) {
        switch (result) {
            case 'I': {
                inputPath = optarg;
                break;
            }
            case 'O': {
                outputPath = optarg;
                break;
            }
            case 'T': {
                operationType = optarg;
                break;
            }
            default: {
                break;
            }

        }
    }

}


int main(int argc, char *argv[]) {

    std::string inputPath = "";
    std::string outputPath = "";
    std::string operationType = "0";

    //parse arguments from command line
    parseArgs(argc, argv, inputPath, outputPath, operationType);

    if (inputPath == "") {
        std::cout << "Bad input file!" << std::endl;
        return 1;
    }

    if (outputPath == "") {
        std::cout << "Bad output file!" << std::endl;
        return 1;
    }

    if (atoi(operationType.c_str()) > 2 || atoi(operationType.c_str()) < 1) {
        std::cout << "Bad operation type!" << std::endl;
        return 1;
    }

    //create xml document
    TiXmlDocument doc;


    //loadFile(&doc,inputPath);
    //open xml file
    if (!doc.LoadFile(inputPath)) {
        std::cout << "Bad input file!" << std::endl;
        return 1;
    }


    //visitor for enter element with attribute
    MyVisitor *visitor = new MyVisitor(atoi(operationType.c_str()));

    std::cout << "1" << std::endl;
    //getting first element of xml document
    TiXmlNode *element = doc.FirstChild();
    if (element != NULL) {
        //visit all elements in element
        element->Accept(visitor);
    }

    std::cout << "2" << std::endl;
    //visit other elements in doc
    while((element = doc.IterateChildren(element))!=NULL){
        element->Accept(visitor);
    }

    std::cout << "3" << std::endl;
    //save xml file
    //saveFile(&doc,outputPath);
    if (!doc.SaveFile(outputPath)) {
        std::cout << "Bad output file!" << std::endl;
        return 1;
    }

    return 0;
}