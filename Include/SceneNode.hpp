#if !defined(SCENE_NODE_H)
#define SCENE_NODE_H

#include "Command.hpp"

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>
#include <memory>
#include <assert.h>
#include <algorithm>
#include <utility>
#include <set>
#include <cassert>


class Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode>              Ptr;
    typedef std::pair<SceneNode *, SceneNode *>     Pair;

    explicit                    SceneNode(Category::Type category = Category::Type::None);
    
    /**
     * @brief Takes ownership of the scene node.
     * @param child
     */
    void                        attach_child(Ptr child);

    /**
     * @brief Searches foran occurrence of the specified node,
     * releases it from the container, andreturnsit to the
     * called, again wrapped in a unique_ptr.
     * @param node
     * @return Ptr
     */
    Ptr                         detach_child(const SceneNode &node);

    sf::Transform               getWorldTransform() const;
    sf::Vector2f                getWorldPosition() const;
    virtual sf::FloatRect       getBoundingRect() const;

    virtual bool                is_destroyed() const;
    virtual bool                is_marked_for_removal() const;

    void                        check_scene_collison(SceneNode& scene_graph, std::set<Pair>& collision_pairs);
    void                        check_node_collision(SceneNode& node, std::set<Pair>& collision_pairs);

    void                        on_command(const Command &command, sf::Time dt);
    virtual unsigned int        get_category() const;

    void                        update(sf::Time dt, CommandQueue &commands);

    void                        remove_wrecks();


private:
    /**
     * @brief  No other classes need access to the draw() method, so we can make it private.
     *   The final keyword is used to prevent the function
     *   from being overridden in classes derived from SceneNode.
     *
     * @param target
     * @param states
     * @return * void
     */
    virtual void        draw(sf::RenderTarget &target, sf::RenderStates states) const override final;
    virtual void        draw_current(sf::RenderTarget &target, sf::RenderStates states) const;
    void                draw_children(sf::RenderTarget& target, sf::RenderStates states) const;
    void                draw_bounding_rect(sf::RenderTarget& target, sf::RenderStates) const;

    virtual void        update_current(sf::Time dt, CommandQueue& commands){};
    void                update_children(sf::Time dt, CommandQueue &commands);

private:
    std::vector<Ptr>    children;
    SceneNode *         parent; 

    Category::Type      category;
};

float                   distance(const SceneNode& lhs, const SceneNode& rhs);
bool                    collision(const SceneNode& lhs, const SceneNode& rhs);

#endif // SCENE_NODE_H
