#include "attributes.h"

void MannedAttribute::init(int minCrew, int maxCrew) {
    _minCrew = minCrew;
    _maxCrew = maxCrew;
}

Attribute* Attribute::factory(Attribute::Type type) {
    switch(type) {
        case Unknown: return new Attribute();
        case Invulnerable: return new InvulerableAttribute();
        case Manned: return new MannedAttribute();
        case Launcher: return new LauncherAttribute();
        case Chargable: return new ChargingAttribute();
    }
    return nullptr;
}