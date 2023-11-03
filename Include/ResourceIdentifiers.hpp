#if !defined(RESOURCE_IDENTIFIERS_H)
#define RESOURCE_IDENTIFIERS_H

#define DEFAULT_CHAR_SIZE 70
namespace Textures
{
    enum class ID
    {
        Undefined,
        Entities,
        Jungle,
        TitleScreen,
        Buttons,
        Explosion,
        Particle,
        FinishLine,
    };
}

namespace Shaders
{
    enum class ID
    {
        BrightnessPass,
        DownSamplePass,
        GaussianBlurPass,
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
        EnemyGunfire,
        Explosion1,
        Explosion2,
        LaunchMissile,
        CollectPickup,
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
