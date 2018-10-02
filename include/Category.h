#ifndef CATEGORY_H
#define CATEGORY_H

namespace Category {
enum Type {
  None = 0,
  Scene = 1 << 0,
  Bird = 1 << 1,
  Pipe = 1 << 2,
};
}

#endif // CATEGORY_H
