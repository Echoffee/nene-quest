#include "../headers/weaponType.hpp"
#include <SFML/Graphics.hpp>

sf::Vector2f getWeaponOrigin(WeaponType w) {
    switch (w) {
        case Bow:
            break;
        case Axe:
            return sf::Vector2f(90,190);
        case Sword:
            return sf::Vector2f(80,270);
        case GreatSword:
            return sf::Vector2f(35,260);
    }
    return sf::Vector2f(1,1);
}

std::string getWeaponPath(WeaponType w) {

    switch (w) {
        case Bow:
            return "img/weapon_bow.png";
        case Axe:
            return "img/weapon_axe.png";
        case Sword:
            return "img/weapon_sword.png";
        case GreatSword:
            return "img/weapon_sword2.png";
        default:
            return "";
    }
}

int getWeaponDamaga(WeaponType w)
{
     switch (w) {
        case Bow:
            return 1;
        case Axe:
            return 3;
        case Sword:
            return 1;
        case GreatSword:
            return 2;
    }
}
