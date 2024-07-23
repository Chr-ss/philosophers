# Project Description: Philosophers Problem

## Overview

The "Philosophers Problem" is a classic synchronization problem in computer science, designed to illustrate the challenges of allocating resources among concurrent processes without causing deadlock. This project involves simulating a group of philosophers sitting at a round table, alternating between eating, thinking, and sleeping. Each philosopher requires two forks to eat, and there are as many forks as there are philosophers, placed between them.

## Objectives

- **Concurrency and Threading**: Learn the basics of creating and managing threads in a program.
- **Synchronization**: Implement mutexes to prevent data races and ensure safe access to shared resources.
- **Simulation**: Create a realistic simulation where each philosopher alternates between different states (eating, thinking, sleeping) while ensuring they do not starve.

## Key Concepts

- **Threads**: Each philosopher is represented as a thread, allowing them to operate concurrently.
- **Mutexes**: Forks are protected by mutexes to prevent more than one philosopher from using the same fork simultaneously.
- **State Management**: Track and log the state of each philosopher (eating, thinking, sleeping) with precise timing to ensure the simulation is accurate.

## Rules and Constraints

1. **Philosopher Actions**: Philosophers can only eat if they have both their left and right forks. They alternate between eating, thinking, and sleeping.
2. **Fork Management**: There is one fork between each pair of philosophers. Philosophers pick up the fork on their left and right to eat, and release them after eating.
3. **Synchronization**: Use mutexes to prevent deadlock and ensure that philosophers can safely pick up and put down forks.
4. **Logging**: Each state change of a philosopher (taking a fork, eating, sleeping, thinking, dying) must be logged with a timestamp.
5. **Program Termination**: The simulation stops when a philosopher dies of starvation or if all philosophers have eaten a specified number of times.

## Program Requirements

- **Languages and Libraries**: The project must be written in C using standard libraries such as `pthread` for threading and `pthread_mutex` for mutexes.
- **Makefile**: Provide a Makefile with targets for building, cleaning, and rebuilding the project.
- **Git Repository**: Submit the project via a git repository, adhering to the specified directory structure and file naming conventions.

By completing this project, you will gain a deeper understanding of concurrency, synchronization, and resource allocation in multi-threaded applications.
