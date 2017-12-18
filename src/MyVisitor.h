#ifndef VISITOR_H
#define VISITOR_H

#include <iostream>
#include <algorithm>
#include "tinyxml.h"


//class visitor for access xml elements
class MyVisitor : public TiXmlVisitor {
private:
    int operationType;

public:
    //constructor
    MyVisitor(int operationType);

    //method for enter xml elements
    bool VisitEnter(const TiXmlElement &element, const TiXmlAttribute *firstAttribute);

    //function for change attribute depending on operation type
    bool changeAttribute(TiXmlAttribute *attribute);

    //method for reverse value of attribute
    std::string reverseValue(std::string value);

    //method for counting length value of attribute
    int lengthValue(std::string value);
};

#endif