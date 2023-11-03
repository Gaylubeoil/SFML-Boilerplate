#include "Animation.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Animation::Animation()
    : sprite(), frame_size(), num_frames(0), current_frame(0), duration(sf::Time::Zero), elapsed_time(sf::Time::Zero), repeat(false) {}

Animation::Animation(const sf::Texture &texture)
    : sprite(texture), frame_size(), num_frames(0), current_frame(0), duration(sf::Time::Zero), elapsed_time(sf::Time::Zero), repeat(false) {}

void Animation::set_texture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
}

const sf::Texture *Animation::get_texture() const
{
    return sprite.getTexture();
}

void Animation::set_frame_size(sf::Vector2i frame_size)
{
    this->frame_size = frame_size;
}

sf::Vector2i Animation::get_frame_size() const
{
    return this->frame_size;
}

void Animation::set_num_frames(std::size_t num_frames)
{
    this->num_frames = num_frames;
}

std::size_t Animation::get_num_frames() const
{
    return this->num_frames;
}

void Animation::set_duration(sf::Time duration)
{
    this->duration = duration;
}

sf::Time Animation::get_duration() const
{
    return this->duration;
}

void Animation::set_repeating(bool flag)
{
    this->repeat = flag;
}

bool Animation::get_repeating() const
{
    return this->repeat;
}

void Animation::restart()
{
    current_frame = 0;
}

bool Animation::is_finished() const
{
    return current_frame >= num_frames;
}

sf::FloatRect Animation::get_local_bounds() const
{
    return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(get_frame_size()));
}

sf::FloatRect Animation::get_global_bounds() const
{
    return getTransform().transformRect(get_local_bounds());
}

void Animation::update(sf::Time dt) {
    sf::Time time_per_frame = duration / float(num_frames);
    elapsed_time += dt;

    sf::Vector2i texture_bounds(sprite.getTexture()->getSize());
    sf::IntRect texture_rect = sprite.getTextureRect();

    if (current_frame == 0) 
        texture_rect = sf::IntRect(0,0,frame_size.x,frame_size.y);
    
    while(elapsed_time >= time_per_frame && 
          (current_frame <= num_frames || repeat)) {
            texture_rect.left += texture_rect.width;

            if (texture_rect.left + texture_rect.width > texture_bounds.x){
                texture_rect.left = 0;
                texture_rect.top += texture_rect.height;
            }

            elapsed_time -= time_per_frame;
            if (repeat) {
                current_frame = (current_frame + 1) % num_frames;
                if (current_frame == 0) 
                    texture_rect = sf::IntRect(0,0,frame_size.x, frame_size.y);
            }
            else {
                current_frame++;
            }
          }
    sprite.setTextureRect(texture_rect);
}

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}