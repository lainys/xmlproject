
#include "MyVisitor.h"

MyVisitor::MyVisitor(int operationType) {
    this->operationType = operationType;
}

bool MyVisitor::VisitEnter(const TiXmlElement &element, const TiXmlAttribute *firstAttribute) {

    std::cout << "1" << std::endl;
    std::cout<<firstAttribute->Value()<<std::endl;

    TiXmlAttribute *attribute = const_cast<TiXmlAttribute *>(firstAttribute);

    std::cout << "1" << std::endl;
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
    std::cout << "1" << std::endl;
    return true;

}

/*bool MyVisitor::VisitEnter(const TiXmlElement& i_element, const TiXmlAttribute* io_attr)
{
    while(io_attr)
    {
        TiXmlAttribute* attr = const_cast<TiXmlAttribute*>(io_attr);
        if (!changeAttribute(attr))
        {
            return false;
        }
        io_attr = io_attr->Next();
    }
    return true;
}*/

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
    std::cout<<"tyt"<<std::endl;
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