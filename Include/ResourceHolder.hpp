#if !defined(TEXTURE_HOLDER_H)
#define TEXTURE_HOLDER_H

#include "ResourceIdentifiers.hpp"

#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <assert.h>

/**
 * @brief
 *   This template class's job is to handle and store different resources, ranging from textures, sounds, founts, etc.
 *   The type of resources is designed to work in correlation with SFML classes, but anything that
 *   supports loadFromFile methods and similar interface should work as well.
 */

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    /**
     * @brief The Resource object must contain a loadFromFile function.
     * The resource is then loaded from the passed file and added to the map
     * holding the actual resources.
     *
     * @param id
     * @param filename
     */
    void load(Identifier id, const std::string &filename);

    /**
     * @brief This overload of the load function enables the ResourceHolder to
     * handle SFML shaders, as well as load IntRects for regular sf::Texture objects.
     *
     * @tparam Parameter
     * @param id
     * @param filename
     * @param second_param
     */
    template <typename Parameter>
    void load(Identifier id, const std::string &filename, const Parameter &second_param);
    Resource &get(Identifier id);
    const Resource &get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> resource_map;
};

#include "ResourceHolder.inl"

#endif // TEXTURE_HOLDER_H
