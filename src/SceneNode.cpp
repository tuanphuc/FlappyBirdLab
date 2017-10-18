#include "SceneNode.h"
#include "Command.h"

#include <iostream>

unsigned int SceneNode::nSceneNode = 0;

SceneNode::SceneNode()
: mChildren(),
  mParent(nullptr)
{

}

unsigned int SceneNode::getId()
{
  return 0;
}

void SceneNode::attachChild(Ptr child)
{
  child->mParent = this;
  mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild()
{
  Ptr first = std::move(*mChildren.begin());
  first->mParent = nullptr;
  mChildren.erase(mChildren.begin());
  return first;
}

int SceneNode::getNumerOfChild() const
{
  return this->mChildren.size();
}

void SceneNode::update(sf::Time dt)
{
  updateCurrent(dt);
  updateChildren(dt);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
  return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
  sf::Transform transform = sf::Transform::Identity;

  for (const SceneNode* node = this; node != nullptr; node = node->mParent)
  transform = node->getTransform() * transform;

  return transform;
}

std::vector<sf::Vector2f> SceneNode::getWorldPositionChildren()
{
  std::vector<sf::Vector2f> positionChildren;
  for(Ptr& child : mChildren)
  {
    positionChildren.push_back(child->getWorldPosition());
  }
  return positionChildren;
}

void SceneNode::onCommand(const Command &command)
{
  // Command current node, if category matches
  if(command.category & getCategory())
  command.action(*this);

  // Command children
  for(Ptr& child : mChildren)
  child->onCommand(command);
}

unsigned int SceneNode::getCategory() const
{
  return Category::Scene;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
  return sf::FloatRect();
}

bool SceneNode::isMarkedForRemoval() const
{
  // By default, remove node if entity is destroyed
  return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
  // By default, scene node needn't be removed
  return false;
}

std::vector<unsigned int> SceneNode::getDyingNode(unsigned int category)
{
  std::vector<unsigned int> dyingNodes;
  for(Ptr& child : mChildren)
  {
    if(child->getCategory()==category && child->isDestroyed())
    {
      dyingNodes.push_back(child->getId());
    }
  }
  return dyingNodes;
}

void SceneNode::checkCollisionWith(SceneNode* node, std::set<Pair> &collisionPairs)
{
  for(Ptr& fChild : this->mChildren)
  {
    for(Ptr& sChild : node->mChildren)
    {
      if(collision(*fChild, *sChild))
      collisionPairs.insert(Pair(fChild.get(), sChild.get()));
    }
  }
}

void SceneNode::removeWrecks()
{
  // Remove all children which request so
  auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
  mChildren.erase(wreckfieldBegin, mChildren.end());

  // Call function recursively for all remaining children
  std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

void SceneNode::updateCurrent(sf::Time dt)
{

}

void SceneNode::updateChildren(sf::Time dt)
{
  for(Ptr& child : mChildren)
  child->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  drawCurrent(target, states);
  drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const
{
  for(const Ptr& child : mChildren)
  child->draw(target, states);
}

bool collision(const SceneNode &lhs, const SceneNode &rhs)
{
  return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}
