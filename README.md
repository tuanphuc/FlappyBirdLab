# FlappyBirdLab

Another clone of FlappyBird game written in C++11 using SFML + Genetic Algorithm.

# Requirements
Install SFML (https://github.com/SFML/SFML)

# Install
This project is built with CMake. To compile:
```
git clone https://github.com/tuanphuc/FlappyBirdLab.git
cd FlappyBirdLab
mkdir build
cd build
cmake ..
make
make install
```
# Play mode

You can have fun with the bird in this mode:

![play_mode](https://github.com/tuanphuc/FlappyBirdLab/blob/master/gifs/recorded_play.gif)

# Learning mode

In this mode (inspired from https://github.com/xviniette/FlappyLearning), the genetic algrithm generates generations of 50 birds and then mixed birds' genomes to find the best one to survive:

![learning_mode](https://github.com/tuanphuc/FlappyBirdLab/blob/master/gifs/recorded_learning.gif)


