#include "ResourceHolder.hpp"

template <typename Resource, typename Identifier>
template <typename Parameter>
inline void ResourceHolder<Resource, Identifier>::load(Identifier id,
                                                       const std::string &filename, const Parameter &second_param)
{
    /*Create a new temporary object to load the resource into.*/
    std::unique_ptr<Resource> resource(new Resource());

    /*Throw an error if the resource cannot be loaded. */
    if (!resource.loadFromFile(filename, second_param))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    /*
    The insert function in std::map returns a std::pair of iterators along
    with a boolean value. The std::pair contains the iterator to the element with the
    given key (or an iterator pointing to the element if it already
    exists) and a boolean indicating whether the insertion was successful or not.
    */
    auto inserted = resource_map.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
inline void ResourceHolder<Resource, Identifier>::load(Identifier id,
                                                       const std::string &filename)
{
    /*Create a new temporary object to load the resource into.*/
    std::unique_ptr<Resource> resource(new Resource());

    /*Throw an error if the resource cannot be loaded. */
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    /*
    The insert function in std::map returns a std::pair of iterators along
    with a boolean value. The std::pair contains the iterator to the element with the
    given key (or an iterator pointing to the element if it already
    exists) and a boolean indicating whether the insertion was successful or not.
    */
    auto inserted = resource_map.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
inline Resource &ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = resource_map.find(id);
    /*Make sure the element is found.*/
    assert(found != resource_map.end());
    return *found->second;
}

template <typename Resource, typename Identifier>
inline const Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = resource_map.find(id);
    assert(found != resource_map.end());
    return *found->second;
}
