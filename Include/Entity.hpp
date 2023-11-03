#if !defined(ENTITY_H)
#define ENTITY_H
#include "SceneNode.hpp"

class Entity : public SceneNode
{
public:
                    Entity();
    explicit        Entity(const int hp);

    void            regen(const int hp);
    void            damage(const int hp);
    void            destroy();

    int             get_hp() const;
    virtual void    remove();
    virtual bool    is_destroyed() const override;

    void            set_velocity(const sf::Vector2f velocity);
    void            set_velocity(const float vx, const float vy);
    sf::Vector2f    get_velocity() const;

    void            accelerate(const sf::Vector2f factor);
    void            accelerate(const float vx, const float vy);

                    ~Entity() = default;

protected:
    // Overrides from the SceneNode class
    virtual void    update_current(sf::Time dt, CommandQueue& commands) override;

private:
    // The default constructor for Vector2f sets it's members to 0.
    sf::Vector2f     velocity;
    int              hp;
};

#endif // ENTITY_H
