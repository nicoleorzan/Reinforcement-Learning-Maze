# Learning to solve a maze using Reinforcement Learning


### Overview
---

This repository contains a C++ implementation of different Reinforceent Learning algorthms which allow to solve the maze problem. The goal is reaching a specified state in a gridworld scenario, starting from any random position.

### Algorithms
--- 

Four algorithms have been implemented to solve the maze problem:
* SARSA
* Q-learning
* Double Q-learning
* QV($\lambda$) learning

Both the epsilon-greedy and Boltzmann exploration strategies are available.

### Basic Usage
---

Clone this repository:

```
$ git clone https://github.com/nicoleorzan/RL-maze-solver
```

Compile the code using the Makefile:

```
$ make
```

Run the main code, which executes the four learning algorithms on an example maze

When finished, clean up:

```
$ make clean
```

### Personalized Usage
---

You can define the maze you want to solve in the maze_definition file. He you should insert:
* the maze size N, an integer number
* the non-visitable states, defined as integer numbers between 0 adn N-1

### References
---

* Richard S. Sutton and Andrew G. Barto. 1998. Introduction to Reinforcement Learning (1st. ed.). MIT Press, Cambridge, MA, USA.

* Wiering, Marco. (2005). QV(lambda)-learning: A New On-policy Reinforcement Learning Algrithm. 
