#pragma once

#include <stdint.h>
#include <string>
#include <vector>

class Attribute {
public:
	enum Type:uint64_t {
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
    Type type() { return _type; }
    static Attribute* factory(Type type);
};

class InvulerableAttribute : public Attribute {
public:
	InvulerableAttribute()
	: Attribute( Invulnerable )
	{}
	virtual ~InvulerableAttribute()
	{}
};

class MannedAttribute : public Attribute {
public:
    MannedAttribute(): Attribute( Manned ){}
	MannedAttribute( int minCrew, int maxCrew )
	: Attribute( Manned ), _minCrew( minCrew ), _maxCrew( maxCrew )
	{}
	virtual ~MannedAttribute()
	{}
    void init(int minCrew, int maxCrew);
private:
	int	_minCrew;
	int _maxCrew;
};

class LauncherAttribute : public Attribute {
public:
	LauncherAttribute() : Attribute(Launcher){}
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

class ChargingAttribute : public Attribute {
public:
    ChargingAttribute() : Attribute(Chargable) {}
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
