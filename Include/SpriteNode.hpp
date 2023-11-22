#if !defined(SPRITE_NODE_H)
#define SPRITE_NODE_H

#include "SceneNode.hpp"

/**
 * @brief Used to display our background sprite through the scene graph.
 * It acts as a simple sf::Sprite.
 */
class SpriteNode : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture &texture);
    SpriteNode(const sf::Texture &, const sf::IntRect &);

private:
    virtual void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite;
};

#endif // SPRITE_NODE_H