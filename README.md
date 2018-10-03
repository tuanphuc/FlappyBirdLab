# FlappyBirdLab
[![Build Status](https://travis-ci.org/tuanphuc/FlappyBirdLab.svg?branch=master)](https://travis-ci.org/tuanphuc/FlappyBirdLab)

This project implements FlappyBird game in C++11 using SFML. The game design is inspired by the book [SFML Game Development](https://github.com/SFML/SFML-Game-Development-Book)
by Jan Haller, Henrik Vogelius Hansson, Artur Moreira.

![play_mode](https://github.com/tuanphuc/FlappyBirdLab/blob/master/gifs/recorded_play.gif)

This project also acts as an environment to test **evolutionary algorithm** on birds. By using genetic algorithm:

![learning_mode](https://github.com/tuanphuc/FlappyBirdLab/blob/master/gifs/recorded_learning.gif)

Birds can learn to flap perfectly:

![result](https://github.com/tuanphuc/FlappyBirdLab/blob/master/gifs/recorded_result.gif)

 The genetic algorithm is inspired by https://github.com/xviniette/FlappyLearning
 
# Install

  -  First install SFML (https://github.com/SFML/SFML)
  -  Then compile with cmake:
```
git clone https://github.com/tuanphuc/FlappyBirdLab.git
cd FlappyBirdLab
mkdir build
cd build
cmake ..
make
make install
```
# Todo
  -  Add more evolutionary strategies
