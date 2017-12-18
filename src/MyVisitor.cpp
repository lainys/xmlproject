
#include "MyVisitor.h"

MyVisitor::MyVisitor(int operationType) {
    this->operationType = operationType;
}

bool MyVisitor::VisitEnter(const TiXmlElement &element, const TiXmlAttribute *firstAttribute) {

    TiXmlAttribute *attribute = const_cast<TiXmlAttribute *>(firstAttribute);

    if (!attribute) {
        std::cout<<"false"<<std::endl;
        return false;
    }

    //change attribute depending on operation type
    if (!changeAttribute(attribute)) {
        std::cout<<"false"<<std::endl;
        return false;
    }

    //change all other attribute for this element
    while (attribute = attribute->Next()) {
        if (!changeAttribute(attribute)) {
            std::cout<<"false"<<std::endl;
            return false;
        }
    }
    return true;

}

//method for change attribute depending on operation type
bool MyVisitor::changeAttribute(TiXmlAttribute *attribute) {
    //get value from attribute
    if (attribute->Value()!= NULL) {
        std::string value = attribute->Value();

        switch (operationType) {
            case 1: {
                //reverse value
                attribute->SetValue(reverseValue(value).c_str());
                break;
            }
            case 2: {
                //length value
                attribute->SetIntValue(lengthValue(value));
                break;
            }
            default: {
                std::cout << "Bad operation type!" << std::endl;
                return false;
            }
        }
    }
    return true;
}

//method for reverse value of attribute
std::string MyVisitor::reverseValue(std::string value) {
    std::reverse(value.begin(), value.end());
    return value;
}

//method for counting length value of attribute
int MyVisitor::lengthValue(std::string value) {
    return (value.length());
}