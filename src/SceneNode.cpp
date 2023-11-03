#include "SceneNode.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>
#include <cmath>

SceneNode::SceneNode(Category::Type category)
    : children(), parent(nullptr), category(category) {}

void SceneNode::attach_child(Ptr child)
{
    child->parent = this;
    children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detach_child(const SceneNode &node)
{
    /*
        InputIt find_if(InputIt first, InputIt last, UnaryPredicate p);
    */
    auto found = std::find_if(children.begin(), children.end(),
                              [&](Ptr &p) -> bool
                              { return p.get() == &node; });

    assert(found != children.end());

    Ptr result = std::move(*found);
    result->parent = nullptr;
    children.erase(found);
    return result;
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode *node = this; node != nullptr; node = node->parent)
        transform = node->getTransform() * transform;
    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::FloatRect SceneNode::getBoundingRect() const
{
    return sf::FloatRect();
}

unsigned int SceneNode::get_category() const
{
    return category;
}

bool SceneNode::is_destroyed() const { return false; }
bool SceneNode::is_marked_for_removal() const { return is_destroyed(); }

void SceneNode::check_node_collision(SceneNode& node, std::set<Pair>& collision_pairs) {
    if (this != &node && collision(*this, node) && 
        !is_destroyed() && !node.is_destroyed()) 
            collision_pairs.insert(std::minmax(this, &node)); 

        for (Ptr& child : children) 
            child->check_node_collision(node, collision_pairs);
        
}

void SceneNode::check_scene_collison(SceneNode& scene_graph, std::set<Pair>& collision_pairs) {
    check_node_collision(scene_graph, collision_pairs);
    for(Ptr& child : scene_graph.children) 
        check_scene_collison(*child, collision_pairs); //TODO
}

void SceneNode::on_command(const Command &command, sf::Time dt)
{
    if (command.category & get_category())
        command.action(*this, dt);

    for (Ptr &child : children)
        child->on_command(command, dt);
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    draw_current(target, states);
    draw_children(target, states);
    draw_bounding_rect(target, states);
}

void SceneNode::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {}

void SceneNode::draw_children(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const Ptr &child : children)
        child->draw(target, states);
}

void SceneNode::draw_bounding_rect(sf::RenderTarget &target, sf::RenderStates) const
{
    sf::FloatRect rect = getBoundingRect();

    sf::RectangleShape shape;
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);
    target.draw(shape);
}

void SceneNode::update(sf::Time dt, CommandQueue &commands)
{
    update_current(dt, commands);
    update_children(dt, commands);
}

void SceneNode::update_children(sf::Time dt, CommandQueue &commands)
{
    for (Ptr &child : children)
        child->update(dt, commands);
}

void SceneNode::remove_wrecks()
{
    // Remove all children which request so
    auto wreckfield_begin = std::remove_if(children.begin(), children.end(),
                                           std::mem_fn(&SceneNode::is_marked_for_removal));

    children.erase(wreckfield_begin, children.end());

    // Call function recursively for all remaining children
    std::for_each(children.begin(), children.end(),
                  std::mem_fn(&SceneNode::remove_wrecks));
}

bool collision(const SceneNode &lhs, const SceneNode &rhs)
{
    return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float distance(const SceneNode &lhs, const SceneNode &rhs)
{
    return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}