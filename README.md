# FlappyBirdLab

Another clone of FlappyBird game written in C++11 using SFML. This game is heavily inspired by the book SFML Game Development
by Jan Haller, Henrik Vogelius Hansson, Artur Moreira. The codes for the book are in [this repo](https://github.com/SFML/SFML-Game-Development-Book). 

The game has two modes:  
  -  **Play mode**: where you can play flappy bird as normal:

![play_mode](https://github.com/tuanphuc/FlappyBirdLab/blob/master/gifs/recorded_play.gif)

  -  **Learning mode**: where you can enjoy the evolution of generations of birds trying to survive. The evolution is powered by genetic algrithm (inspired from https://github.com/xviniette/FlappyLearning):

![learning_mode](https://github.com/tuanphuc/FlappyBirdLab/blob/master/gifs/recorded_learning.gif)

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
