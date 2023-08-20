/*
 * main.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: hesterg
 */
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <memory>

#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

#include "attributes.h"

// global abstract class for an attribute

template <typename K, typename V>
class Collection {
public:
    typedef std::map<K,std::shared_ptr<V>>    map_type;
    typedef typename map_type::iterator       map_itr;
    typedef typename map_type::const_iterator map_citr;

    Collection()
    {}
    virtual ~Collection()
    {}
    void add(K key, V& obj) {
        add(key, &obj);
    }
    void add(K key, V *obj) {
        _c.insert(std::make_pair(key, std::shared_ptr<V>(obj)));
    }
    bool contains(K key) {
        return get(key) != nullptr;
    }

    V* get(K key) {
        map_itr ret = _c.find(key);
        if ( ret == _c.end() )
            return nullptr;
        return ret->second.get();
    }
private:
    map_type _c;
};

class AttributeCollection : public Collection<Attribute::Type, Attribute> {
public:
    void add(Attribute* obj) {
        Collection::add(obj->type(), obj);
    }
};



class Shield {
private:
};

class Component {

};

class ComponentCollection {

};

class Section {
public:
	enum Type:uint64_t {
		Unknown      = 0,
		Invulnerable = 0x00000001,
		Manned       = 0x00000002,
		Launcher     = 0x00000004,
		Chargable    = 0x00000008
	}	_type;
};

typedef Collection<Section::Type, Section> SectionCollection;

class System {
public:
	enum Type:uint64_t {
		Unknown      = 0,
		Invulnerable = 0x00000001,
		Manned       = 0x00000002,
		Launcher     = 0x00000004,
		Chargable    = 0x00000008
	}	_type;
};

typedef Collection<System::Type, System> SystemCollection;

class Ship {
private:
    Shield                         _shield[6];
    std::vector<SectionCollection> _hull;
    SystemCollection               _system;
    AttributeCollection            _attrs;
public:
    void parse(DOMElement *root);    
};

class XercesGuard {
private:
    bool init;
public:    
    XercesGuard() : init(false) {
        try {
            XMLPlatformUtils::Initialize();
            init = true;
        } catch( const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            std::cout << "Error during initialization! :\n"
                 << message << "\n";
            XMLString::release(&message);
        } 
    }

    const bool isInit() const { return init; }

    ~XercesGuard() {
        std::cout << "dtor" << std::endl;
        if (init) {
            XMLPlatformUtils::Terminate();
        }
    }
};


int main(int argc, char **argv)
{
    XercesGuard xmlGuard;

    if ( !xmlGuard.isInit() ) {
        exit(1);
    }

    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);    // optional

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    try {
        parser->parse("/work/trek/drydock/example.xml");
        DOMDocument *doc = parser->getDocument();
        DOMElement *root = doc->getDocumentElement();
        std::cout << XMLString::transcode(root->getNodeName()) << std::endl;
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
                << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        std::cout << "Exception message is: \n"
                << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (...) {
        std::cout << "Unexpected Exception \n" ;
        return -1;
    }

    delete parser;
    delete errHandler;


    MannedAttribute* ma = (MannedAttribute*)Attribute::factory(Attribute::Manned);
    ma->init(10,10);
    AttributeCollection col;
    col.add(ma);
    MannedAttribute *atr = (MannedAttribute*)(col.get(Attribute::Manned));





    // rapidxml::file<> myfile("example.xml");
    // xml_document<> doc;  // character type defaults to char
    // doc.parse<parse_full>(myfile.data());
    // std::cout << "Name of first node is: " << doc.first_node()->name()
    // 		  << std::endl;
    return 0;
}

void Ship::parse(DOMElement *root) {




}
