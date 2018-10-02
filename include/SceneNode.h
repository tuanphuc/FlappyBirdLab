#ifndef SCENENODE_H
#define SCENENODE_H

#include "Category.h"

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System/NonCopyable.hpp"
#include "SFML/System/Time.hpp"

#include <memory>
#include <set>
#include <vector>

struct Command;

class SceneNode : public sf::Transformable,
                  public sf::Drawable,
                  private sf::NonCopyable {
public:
  static unsigned int nSceneNode;
  typedef std::unique_ptr<SceneNode> Ptr;
  typedef std::pair<SceneNode *, SceneNode *> Pair;

public:
  SceneNode();
  void attachChild(Ptr child);
  Ptr detachChild();
  int getNumerOfChild() const;
  virtual unsigned int getId();

  virtual void update(sf::Time dt);
  sf::Vector2f getWorldPosition() const;
  sf::Transform getWorldTransform() const;
  std::vector<sf::Vector2f> getWorldPositionChildren();

  void onCommand(const Command &command);
  virtual unsigned int getCategory() const;

  virtual sf::FloatRect getBoundingRect() const;
  virtual bool isMarkedForRemoval() const;
  virtual bool isDestroyed() const;
  std::vector<unsigned int> getDyingNode(unsigned int category);

  // Check node in different layers
  void checkCollisionWith(SceneNode *node, std::set<Pair> &collisionPairs);
  void removeWrecks();

private:
  virtual void updateCurrent(sf::Time dt);
  void updateChildren(sf::Time dt);

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  virtual void drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const;
  void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

private:
  std::vector<Ptr> mChildren;
  SceneNode *mParent;
};

bool collision(const SceneNode &lhs, const SceneNode &rhs);

#endif // SCENENODE_H
