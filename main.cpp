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
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
using namespace rapidxml;

// global abstract class for an attribute
class Attribute
{
public:
	enum Type
	{
		Unknown      = 0,
		Invulnerable = 0x00000001,
		Manned       = 0x00000002,
		Launcher     = 0x00000004,
		Chargable    = 0x00000008
	}	_type;
	const int type( void ) const { return _type; }
	Attribute( Type t = Unknown )
	: _type{ t }
	{}
	virtual ~Attribute()
	{}
};

class AttributeCollection
{
public:
    AttributeCollection()
    {}
    virtual ~AttributeCollection()
    {}
    void add( Attribute *atr )
    {
        _c.insert( std::make_pair( atr->_type, std::shared_ptr<Attribute>( atr ) ) );
    }
private:
    std::map<Attribute::Type, std::shared_ptr<Attribute>> _c;
};

class InvulerableAttribute : public Attribute
{
public:
	InvulerableAttribute()
	: Attribute( Invulnerable )
	{}
	virtual ~InvulerableAttribute()
	{}
private:
	std::vector<std::string> _conflictsWith;
};

class MannedAttribute : public Attribute
{
public:
	MannedAttribute( int minCrew, int maxCrew )
	: Attribute( Manned ), _minCrew( minCrew ), _maxCrew( maxCrew )
	{}
	virtual ~MannedAttribute()
	{}
private:
	int	_minCrew;
	int _maxCrew;
};

class LauncherAttribute : public Attribute
{
public:
	LauncherAttribute( std::string spawnType, int seriesNo, int capacity, bool factory )
	: Attribute( Launcher ), _spawnType( spawnType )
    , _seriesNo( seriesNo ), _capacity( capacity ), _factory( factory )
	{}
	virtual ~LauncherAttribute()
	{}
private:
	std::string	_spawnType;
	int			_seriesNo;
	int			_capacity;
	bool		_factory;
};

class ChargingAttribute : public Attribute
{
public:
	ChargingAttribute( int cost, int time, int hold, int maxHold, int overCost, int overTime, int overHold, int overMaxHold )
	: Attribute( Chargable )
	, _cost( cost ), _time( time ), _hold( hold )
	, _maxHold( maxHold ), _overCost( overCost ), _overTime( overTime )
	, _overHold( overHold ), _overMaxHold( overMaxHold )
	{}
	virtual ~ChargingAttribute()
	{}
private:
	int	_cost;
	int	_time;
	int	_hold;
	int	_maxHold;
	int	_overCost;
	int	_overTime;
	int	_overHold;
	int	_overMaxHold;
};

class Shield
{
private:
};

class Component
{

};

class ComponentCollection
{

};

class Section
{


};

class SectionCollection
{

};

class System
{

};

class SystemCollection
{

};

class Ship : public AttributeCollection
{
private:
    Shield                         _shield[6];
    std::vector<SectionCollection> _hull;
    SystemCollection               _system;
};

/*
 *
 * VAR x
 * VAR y
 * MOV x,y
 * EQU x,y
 * call ship.damage()
 *
 */
int main(int argc, char **argv)
{
    rapidxml::file<> myfile("example.xml");
    xml_document<> doc;  // character type defaults to char
    doc.parse<parse_full>(myfile.data());
    std::cout << "Name of first node is: " << doc.first_node()->name()
    		  << std::endl;
    return 0;
}
