#include<time.h>

#include "../headers/dragon.hpp"
#include "../headers/config.hpp"

using namespace sf;
using namespace std;


Dragon::Dragon(Vector2f position) : Enemy (DRAGON_HP) {

    srand(time(NULL));

    attack_damage = DRAGON_DAMAGE;
    enemy_type = Enemy_Dragon;

    flame_timer = 0;

	texture.loadFromFile(GSP_ENEMY_DRAGON);
	sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, texture.getSize().y/2,texture.getSize().x/2, texture.getSize().y/2));
    sprite.setPosition(position);

    hitbox.setPosition(position);
	hitbox.setSize(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
    hitbox.setFillColor(Color::Red);

	hitboxes.push_back(RectangleShape(Vector2f(530,120)));
	hitboxes.at(0).setOrigin(-270, -410);

    hitboxes.push_back(RectangleShape(Vector2f(220,290)));
	hitboxes.at(1).setOrigin(-270, -120);

    hitboxes.push_back(RectangleShape(Vector2f(310,180)));
	hitboxes.at(2).setOrigin(-50, -30);

	for(unsigned int i =0;i < hitboxes.size();i++)
        hitboxes.at(i).setPosition(position);

	//sprite.setOrigin(sprite.getGlobalBounds().width*0.27,sprite.getGlobalBounds().height*0.5 );
    updateSpritePosition();

	speed = Vector2f(DRAGON_SPEED,0);

}

Dragon::~Dragon(){
    for(unsigned int i = 0;i < flames.size();i++){
        delete(flames.at(i));
    }
}

 void Dragon::update(float elapsedTime) {

    if(!this->isDying()){

        //Move dragon back and forth
        movement_timer += elapsedTime;
        if(movement_timer > MOVEMENT_DURATION){

            speed = Vector2f( -speed.x, speed.y);
            movement_timer = 0;
        }

        this->move(computeMove(elapsedTime));

        //Breathe fire
        flame_timer += elapsedTime;
        if(fire_breathing){
            if(flame_timer > DELAY_BETWEEN_FLAMES){
                flames.push_back(new Flame(Vector2f(sprite.getPosition().x - sprite.getOrigin().x + 100 ,
                                                            sprite.getPosition().y -sprite.getOrigin().y + 100 + (float)(rand()%100) ), 70 + (float)(rand()%130), this->getDepth()));
                flame_timer=0;
            }
        }
    }
    //Dying animation
    else{
        fire_breathing = true;
        //Delete the hitbox at the start of the dying animation
        if(dying_timer == 0){
            for(unsigned int i =0;i < hitboxes.size();i++)
                hitboxes.at(i).setSize(Vector2f(0,0));
            sprite.setOrigin(350 ,400);
            sprite.move( 350, 400);
            dying_timer = 1;
            movement_timer = 0;
            speed = Vector2f(3,3);
            flame_timer = 1000;
        }
        else if(dying_timer < DEAD_ANIMATION_DURATION){
            dying_timer += elapsedTime;
            if(sprite.getRotation() < 90)
                sprite.setRotation(90 * dying_timer / DEAD_ANIMATION_DURATION *6);
            else{
                sprite.move(speed.x,speed.y);
                movement_timer += elapsedTime;
                if(movement_timer > 40){
                    speed.x = -speed.x;
                    movement_timer = 0;
                }
                flame_timer += elapsedTime;
                if(flame_timer > 600){
                    flames.push_back(new Flame(Vector2f(sprite.getPosition().x + 270, sprite.getPosition().y - 150), 70, this->getDepth(), true));
                    flame_timer=0;
                }

            }

        }


    }
    //Update animation
    if(clock.getElapsedTime().asSeconds() > ANIMATION_DELAY){
            progressAnimation();
            clock.restart();
    }

    //Delete old flames
    for(unsigned int i = 0;i < flames.size();i++){
        flames.at(i)->update(elapsedTime);
        if(flames.at(i)->isDead()){
            delete(flames.at(i));
            flames.erase(flames.begin()+i);
        }
    }

 }

 void Dragon::progressAnimation(){
    if(fire_breathing){

        if(animation_state == 0){
            animation_state = 1;
            sprite.setTextureRect(IntRect(texture.getSize().x/2, 0, texture.getSize().x, texture.getSize().y/2));
        }
        else{
            animation_state = 0;
            sprite.setTextureRect(IntRect(0, 0, texture.getSize().x/2, texture.getSize().y/2));
        }
    }
    else{
        if(animation_state == 0){
            animation_state = 1;
            sprite.setTextureRect(IntRect(texture.getSize().x/2 , texture.getSize().y/2, texture.getSize().x,texture.getSize().y));
        }
        else{
            animation_state = 0;
            sprite.setTextureRect(IntRect(0, texture.getSize().y/2,texture.getSize().x/2, texture.getSize().y));
        }

    }
}

void Dragon::breathFire(){
    flame_timer = 0;
    fire_breathing = !fire_breathing;
}

void Dragon::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    /*target.draw(hitbox, states);
    for(RectangleShape var : hitboxes)
        target.draw(var, states);*/
    target.draw(sprite, states);
}

bool Dragon::isBreatingFire(){
    return fire_breathing;
}

vector<Flame*> Dragon::getFlames(){
    return flames;
}

//void Dragon::setPosition(int x, int y){
//    sprite.setPosition(x,y);
//    for(unsigned int i =0;i < hitboxes.size();i++)
//        hitboxes.at(i).setPosition(x,y);
//}
//
sf::Vector2f Dragon::computeMove(float elapsedTime){

    sf::Vector2f r  = Vector2f(speed.x*elapsedTime, speed.y*elapsedTime);
    //for(unsigned int i =0;i < hitboxes.size();i++)
    //    hitboxes.at(i).move(speed.x*elapsedTime, speed.y*elapsedTime);

	return r;
}
//
//void Dragon::move(sf::Vector2f g_speed, float elapsedTime){
//    sprite.move(g_speed.x*elapsedTime, g_speed.y*elapsedTime);
//    for(unsigned int i =0;i < hitboxes.size();i++)
//        hitboxes.at(i).move(g_speed.x*elapsedTime, g_speed.y*elapsedTime);
//
//}
//
//bool Dragon::detectHit(Entity* entity){
//
//    if(this->getDepth() + Entity::DEPTH_DIFF > entity->getDepth() && this->getDepth() - Entity::DEPTH_DIFF < entity->getDepth())
//        for(unsigned int i =0;i < hitboxes.size();i++)
//            if(entity->getHitbox().getGlobalBounds().intersects(hitboxes.at(i).getGlobalBounds()))
//                return true;
//    return false;
//}
//
//float Dragon::getDepth(){
//    return hitboxes.at(0).getGlobalBounds().top + hitboxes.at(0).getGlobalBounds().height +70;
//}
