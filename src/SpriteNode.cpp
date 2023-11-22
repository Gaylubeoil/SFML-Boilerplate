#include "SpriteNode.hpp"

SpriteNode::SpriteNode(const sf::Texture &texture)
    : sprite(texture) {}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &rect)
    : sprite(texture, rect) {}

void SpriteNode::draw_current(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}