#include "../headers/itemWeapon.hpp"

using namespace sf;

ItemWeapon::ItemWeapon(WeaponType type, Vector2f position) {

    weapon_type = type;
    if(type == Sword)
        bonus_type = Item_Sword;
    else if(type == Axe)
        bonus_type = Item_Axe;
    else if(type == Bow)
        bonus_type = Item_Bow;
    else if(type == GreatSword)
        bonus_type = Item_Greatsword;

    texture.loadFromFile(getWeaponPath(type));
    sprite.setTexture(texture);

    sprite.setPosition(position);
    updateHitboxSize();
    updateHitboxPosition();
}

ItemWeapon::~ItemWeapon() {
    //dtor
}

WeaponType ItemWeapon::getWeaponType(){
    return weapon_type;
}

bool ItemWeapon::checkIfDropped(){
    return is_dropped;
}

void ItemWeapon::setDropped(bool v){
    is_dropped = v;
}