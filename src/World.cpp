#include "World.hpp"

World::World(State::Context context)
    : target(*context.window),
      scene_texture(),
      world_view(target.getDefaultView()),
      textures(*context.textures),
      fonts(*context.fonts),
      scene_graph(),
      scene_layers(),
      world_bounds(
          0.f,                    // left X position
          0.f,                    // top Y position
          world_view.getSize().x, // width
          2000.f                  // height
          ),
      spawn_position(
          world_view.getSize().x / 2.f,
          world_bounds.height - world_view.getSize().y / 2.f //
          ),
      c_queue()
{
    scene_texture.create(target.getSize().x, target.getSize().y);
    load_textures();
    build_scene();
    world_view.setCenter(spawn_position);
}

void World::load_textures()
{
}

void World::build_scene()
{
    // Initialize all the different layers.
    for (size_t i = 0; i < size_t(Layer::LayerCount); ++i)
    {
        Category::Type category = Category::None;

        SceneNode::Ptr layer(new SceneNode(category));
        scene_layers[i] = layer.get();
        scene_graph.attach_child(std::move(layer));
    }
    // std::unique_ptr<SpriteNode> terrain(new SpriteNode());
}

CommandQueue &World::get_command_queue() { return c_queue; }

sf::FloatRect World::get_view_bounds() const
{
    return sf::FloatRect(world_view.getCenter() - world_view.getSize() / 2.f, world_view.getSize());
}

sf::FloatRect World::get_battlefiled_bounds() const
{
    sf::FloatRect rect = get_view_bounds();
    return rect;
}

void World::update(sf::Time dt)
{
}

void World::draw()
{
    target.setView(world_view);
    target.draw(scene_graph);
}
