#include "Entity.hpp"

Entity::Entity() : velocity(), hp(1) {}
Entity::Entity(const int hp) : velocity(), hp(hp) {}

void Entity::regen(const int hp) { this->hp += hp; }
void Entity::damage(const int hp) { this->hp -= hp; }
void Entity::destroy() { this->hp = 0; }
int Entity::get_hp() const { return this->hp; }
bool Entity::is_destroyed() const { return (this->hp <= 0); }

void Entity::remove() {
    destroy();
}

void Entity::set_velocity(const sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void Entity::set_velocity(const float vx, const float vy)
{
    velocity.x = vx;
    velocity.y = vy;
}

sf::Vector2f Entity::get_velocity() const
{
    return velocity;
}

void Entity::accelerate(const sf::Vector2f factor)
{
    velocity += factor;
}

void Entity::accelerate(const float vx, const float vy)
{
    velocity.x += vx;
    velocity.y += vy;
}

void Entity::update_current(sf::Time dt, CommandQueue &commands)
{
    // Same as setPosition(getPosition() + offset);
    move(velocity * dt.asSeconds());
}