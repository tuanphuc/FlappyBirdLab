#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H

// Forward declaration of SFML classes
namespace sf {
class Texture;
class Font;
} // namespace sf

namespace Textures {
enum ID {
  Background,
  Bird,
  PipeTop,
  PipeBottom,
};
}

namespace Fonts {
enum ID {
  Main,
};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier> class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif // RESOURCEIDENTIFIERS_H
