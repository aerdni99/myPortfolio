# MDP Project for AI

Python (Fall 2022)

### Problem Description 
MDP is a sequential decision problem for a fully observable, stochastic environment with a Markovian transition model and additive rewards. In this project, you will implement policy evaluation and value iteration for an MDP in a grid-world.

### Files

case0.csv - a Policy for what direction an agent attempts to move in the world. 1=up;-1=down;2=right;-2=left;
expectimax.csv - output file for part2.py. creates a policy to give max utility based on transition probabilities.
part1.py - given a policy like case0.csv and a reward for non-terminal spaces, calculates the expected utility of the policy at timestep 20.
part2.py - given a transition probability and a reward for non-terminal spaces, determines the optimal policy for max utility for timestep 20.
