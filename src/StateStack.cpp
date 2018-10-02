#include "StateStack.h"

#include <cassert>

StateStack::StateStack(State::Context context)
    : mStack(), mPendingList(), mContext(context), mFactories() {}

void StateStack::update(sf::Time dt) {
  // Iterate from top to bottom, stop as soon as update() returns false
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
    // Stopping of update propagation to lower states
    if (!(*itr)->update(dt))
      break;
  }

  applyPendingChanges();
}

void StateStack::draw() {
  // Draw all active states from bottom to top
  for (auto &state : mStack)
    state->draw();
}

void StateStack::handleEvent(sf::Event &event) {
  // Iterate from top to bottom, stop as soon as handleEvent() returns false
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
    // Gives the control to the states that may not want to
    // let input flow to other states than itself
    if (!(*itr)->handleEvent(event))
      break;
  }

  applyPendingChanges();
}

void StateStack::pushState(States::ID stateID) {
  mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState() { mPendingList.push_back(PendingChange(Pop)); }

void StateStack::clearState() { mPendingList.push_back(PendingChange(Clear)); }

bool StateStack::isEmpty() const { return mStack.empty(); }

State::Ptr StateStack::createState(States::ID stateID) {
  auto found = mFactories.find(stateID);
  assert(found != mFactories.end());

  return found->second();
}

void StateStack::applyPendingChanges() {
  for (auto change : mPendingList) {
    switch (change.action) {
    case Push:
      mStack.push_back(createState(change.stateID));
      break;
    case Pop:
      mStack.pop_back();
      break;
    case Clear:
      mStack.clear();
      break;
    }
  }
  mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action), stateID(stateID) {}
