#include "World.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include <iostream>

World::World(sf::RenderWindow& window, CommandQueue& commandQueue, unsigned int nBird)
: mWindow(window),
  mWorldView(window.getDefaultView()),
  mTextures(),
  mSceneGraph(),
  mSceneLayers(),
  mCommandQueue(commandQueue),
  mBackgroundX(0),
  mBackground(nullptr),
  mDeltaBord(50.f),
  mPipeHole(120.f),
  mSpawnRate(0.f),
  mPipe(nullptr),
  mScrollSpeed(-3.f)
{
  loadTextures();
  buildScene(nBird);
}

World::World(sf::RenderWindow& window, CommandQueue& commandQueue): World(window, commandQueue, 0)
{

}

std::vector<unsigned int> World::update(sf::Time dt)
{
  while (!mCommandQueue.isEmpty())
  mSceneGraph.onCommand(mCommandQueue.pop());

  // Setup commands to destroy entities
  destroyEntitiesOutsideView();
  handleCollision();
  std::vector<unsigned int> dyingNodes = mSceneLayers[BirdLayer]->getDyingNode(Category::Bird);
  mSceneGraph.removeWrecks();
  spawnHoles(dt);
  mSceneGraph.update(dt);
  return dyingNodes;
}

void World::draw()
{
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
  return mCommandQueue;
}

bool World::hasAlivePlayer() const
{
  return mSceneLayers[BirdLayer]->getNumerOfChild() > 0;
}

void World::reset(unsigned int nBird)
{
  // Destroy pipes
  Command command;
  command.category = Category::Pipe;
  command.action = derivedAction<Entity>([this] (Entity& e)
  {
    e.die();
  });
  mCommandQueue.push(command);
  // When all pipes are destroyed, add a new one
  mSpawnRate=0.0f;
  // Add bird
  while(nBird > 0)
  {
    // At the beginning, all birds are alives
    unsigned int id = mSceneLayers[BirdLayer]->getNumerOfChild();
    std::unique_ptr<Bird> bird(new Bird(mTextures, sf::Vector2f(100.f, 256), id)); //50 + rand()%412
    mSceneLayers[BirdLayer]->attachChild(std::move(bird));
    nBird -= 1;
  }
}

std::array<SceneNode*, World::LayerCount>& World::getScene()
{
  return mSceneLayers;
}

void World::loadTextures()
{
  mTextures.load(Textures::Bird, "assets/bird.png");
  mTextures.load(Textures::PipeTop, "assets/pipetop.png");
  mTextures.load(Textures::PipeBottom, "assets/pipebottom.png");
  mTextures.load(Textures::Background, "assets/background.png");
}

void World::buildScene(unsigned int nBird)
{
  // Initialize the different layers
  for (std::size_t i = 0; i < LayerCount; ++i)
  {
    SceneNode::Ptr layer(new SceneNode());
    mSceneLayers[i] = layer.get();
    mSceneGraph.attachChild(std::move(layer));
  }

  // Add background
  std::unique_ptr<Background> background(new Background(mTextures));
  mBackground = background.get();
  mSceneLayers[BackgroundLayer]->attachChild(std::move(background));

  // Add bird
  while(nBird > 0)
  {
    // At the beginning, all birds are alives
    unsigned int id = mSceneLayers[BirdLayer]->getNumerOfChild();
    std::unique_ptr<Bird> bird(new Bird(mTextures, sf::Vector2f(100.f, 256), id));
    mSceneLayers[BirdLayer]->attachChild(std::move(bird));
    nBird -= 1;
  }
}

sf::FloatRect World::getViewBounds() const
{
  return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const
{
  sf::FloatRect bounds = getViewBounds();
  return bounds;
}

void World::spawnHoles(sf::Time dt)
{
  if (mSpawnRate > 0)
  mSpawnRate -= dt.asSeconds();
  else
  {
    mSpawnRate = 1.5f;
    double r = ((double) rand() / (RAND_MAX));
    int mHolePosition = (int) (r * (512 - mDeltaBord * 2 - mPipeHole)
    + mDeltaBord);
    // Add pipes
    std::unique_ptr<Pipe> pipeTop(new Pipe(Pipe::PipeTop, mTextures, sf::Vector2f(500.f, mHolePosition - 512.f)));
    mSceneLayers[PipeLayer]->attachChild(std::move(pipeTop));
    std::unique_ptr<Pipe> pipeBottom(new Pipe(Pipe::PipeBottom, mTextures, sf::Vector2f(500.f, mHolePosition + mPipeHole)));
    mSceneLayers[PipeLayer]->attachChild(std::move(pipeBottom));
  }
}

void World::handleCollision()
{
  // Collision between birds and pipes
  std::set<SceneNode::Pair> collisionPairs;
  mSceneLayers[BirdLayer]->checkCollisionWith(mSceneLayers[PipeLayer], collisionPairs);
  for(SceneNode::Pair pair : collisionPairs)
  {
    auto& bird = static_cast<Bird&>(*pair.first);
    bird.die();
  }
}

void World::destroyEntitiesOutsideView()
{
  Command command;
  command.category = Category::Bird | Category::Pipe;
  command.action = derivedAction<Entity>([this] (Entity& e)
  {
    if(!getBattlefieldBounds().intersects(e.getBoundingRect()))
    e.die();
  });
  mCommandQueue.push(command);
}
