#include "../headers/flame.hpp"
#include<stdio.h>
using namespace sf;

Flame::Flame()
{
    //ctor
}

Flame::Flame(Vector2f position, float f){
    initial_location = position;
    fact = f;

	texture.loadFromFile("img/icon_fire.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(position);
    sprite.scale(0.5,0.5);

    updateHitboxSize();
    updateHitboxPosition();

	speed = Vector2f(-2.7,1);

}

void Flame::update(float elapsedTime){

    lifespan += elapsedTime;

    //Make the flame follow a curve
    this->setPosition(this->getPosition().x + elapsedTime*speed.x/10,initial_location.y + 2*fact *sin(lifespan/(9*fact)));

    //Make the flame smaller when it goes up (when it's derivative (cos) is < 0 and bigger when it goes down
    if(cos(lifespan/(9*fact)) > 0 && sprite.getScale().x <= 1)
        sprite.setScale(sprite.getScale().x + 0.01, sprite.getScale().y + 0.01);
    else{
        span_left += elapsedTime;
        sprite.setScale(sprite.getScale().x - 0.01, sprite.getScale().y - 0.01);
    }
    //Begin a timer when the flame begin to go up to make it disappear
    if(span_left > 800)
        is_dead = true;

}

bool Flame::isDead(){
    return is_dead;
}

Flame::~Flame()
{
    //dtor
}