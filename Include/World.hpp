#if !defined(WORLD_H)
#define WORLD_H
#include "ResourceHolder.hpp"
#include "CommandQueue.hpp"
#include "SceneNode.hpp"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <math.h>
#include <limits>

class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderTarget &output_target, font_holder &fonts);
    CommandQueue &get_command_queue();

    void update(sf::Time dt);
    void draw();

private:
    enum class Layer
    {
        Background = 0,
        LowerAir,
        UpperAir,
        LayerCount,
    };

private:
    void load_textures();
    void build_scene();

    void destroy_entities_outside_vision();

    /**
     * @brief Effectively creates a SpawnPoint() object.
     * The x and y coordinates are relative to the player aircraft's spawn position.
     *
     * @param type
     * @param x
     * @param y
     */

    sf::FloatRect get_battlefiled_bounds() const;
    sf::FloatRect get_view_bounds() const;

private:
    sf::RenderTarget &target;
    sf::RenderTexture scene_texture;
    sf::View world_view;
    texture_holder textures;
    font_holder &fonts;

    SceneNode scene_graph;
    std::array<SceneNode *, size_t(Layer::LayerCount)> scene_layers;

    sf::FloatRect world_bounds;
    sf::Vector2f spawn_position;

    CommandQueue c_queue;
};

#endif // WORLD_H
