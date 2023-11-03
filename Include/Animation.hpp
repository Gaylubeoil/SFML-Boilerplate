#if !defined(ANIMATION_H)
#define ANIMATION_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class Animation : public sf::Drawable, public sf::Transformable
{
public:
                        Animation();
    explicit            Animation(const sf::Texture& texture);

    void                set_texture(const sf::Texture& texture);
    const sf::Texture*  get_texture() const;

    void                set_frame_size(sf::Vector2i frame_size);
    sf::Vector2i        get_frame_size() const;

    void                set_num_frames(std::size_t num_frames);
    std::size_t         get_num_frames() const;

    void                set_duration(sf::Time duration);
    sf::Time            get_duration() const;

    void                set_repeating(bool flag);
    bool                get_repeating() const;

    void                restart();
    bool                is_finished() const;

    sf::FloatRect       get_local_bounds() const;   //todo: might not work if not overloaded?    
    sf::FloatRect       get_global_bounds() const;  //todo: might not work if not overloaded?

    void                update(sf::Time dt);

private:    
    void                draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite          sprite;
    sf::Vector2i        frame_size;
    std::size_t         num_frames;
    std::size_t         current_frame;
    sf::Time            duration;
    sf::Time            elapsed_time;
    bool                repeat;
};

#endif // ANIMATION_H
