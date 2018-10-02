#ifndef WORLD_H
#define WORLD_H

#include "Background.h"
#include "Bird.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Pipe.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/NonCopyable.hpp"

#include <array>

// Forward declaration
namespace sf {
class RenderWindow;
}

class World : private sf::NonCopyable {
public:
  enum Layer { BackgroundLayer, PipeLayer, BirdLayer, LayerCount };

public:
  explicit World(sf::RenderWindow &window, CommandQueue &commandQueue,
                 unsigned int nBird);
  explicit World(sf::RenderWindow &window, CommandQueue &commandQueue);
  std::vector<unsigned int> update(sf::Time dt);
  void draw();
  CommandQueue &getCommandQueue();
  bool hasAlivePlayer() const;
  void reset(unsigned int nBird);
  std::array<SceneNode *, LayerCount> &getScene();
  void speedUp();
  void speedDown();
  void speedPipeUp();
  void speedPipeDown();

private:
  void loadTextures();
  void buildScene(unsigned int nBird);
  sf::FloatRect getViewBounds() const;
  sf::FloatRect getBattlefieldBounds() const;
  void spawnHoles(sf::Time dt);
  void handleCollision();
  void destroyEntitiesOutsideView();

private:
  sf::RenderWindow &mWindow;
  sf::View mWorldView;
  TextureHolder mTextures;

  SceneNode mSceneGraph;
  std::array<SceneNode *, LayerCount> mSceneLayers;
  CommandQueue &mCommandQueue;
  sf::FloatRect mWorldBounds;
  float mBackgroundX;
  Background *mBackground;
  Bird *mBird;

  static const float MIN_PILE_SPEED;
  static const float MAX_PILE_SPEED;
  Pipe *mPipe;
  float mDeltaBord;
  float mPipeHole;
  float mSpawnRate;
  sf::Vector2f mPipeVelocity;

  static const float MIN_GAME_SPEED;
  static const float MAX_GAME_SPEED;
  float mGameSpeed;
};

#endif // WORLD_H
