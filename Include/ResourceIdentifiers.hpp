#if !defined(RESOURCE_IDENTIFIERS_H)
#define RESOURCE_IDENTIFIERS_H

#define DEFAULT_CHAR_SIZE 70
namespace Textures
{
    enum class ID
    {
        Undefined,
        Terrain
    };
}

namespace Shaders
{
    enum class ID
    {
        AddPass
    };
}

namespace Fonts
{
    enum class ID
    {
        Main
    };
}

namespace Music
{
    enum class ID
    {
        MenuTheme,
        MissionTheme
    };
}

namespace Sound
{
    enum class ID
    {
        AlliedGunfire,
        Button,
    };
}

namespace sf
{
    class Texture;
    class Font;
    class Shader;
    class Music;
    class SoundBuffer;
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> texture_holder;
typedef ResourceHolder<sf::Font, Fonts::ID> font_holder;
typedef ResourceHolder<sf::Shader, Shaders::ID> shader_holder;
typedef ResourceHolder<sf::Music, Music::ID> music_holder;
typedef ResourceHolder<sf::SoundBuffer, Sound::ID> sound_holder;

#endif // RESOURCE_IDENTIFIERS_H
