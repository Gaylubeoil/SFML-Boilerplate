# SFML Boilerplate Code

This repository contains a boilerplate codebase for creating 2D games using the Simple and Fast Multimedia Library (SFML). It provides a foundation for game development, with several essential classes and components to help you get started quickly.

## Table of Contents

1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
3. [Getting Started](#getting-started)
4. [Code Structure](#code-structure)

## Introduction

Welcome to the SFML Boilerplate Code project! If you're a game developer looking to kickstart your 2D game development using SFML, you've come to the right place. This boilerplate code is designed to save you time and effort by providing a set of well-structured classes and components to build upon.

The goal of this project is to simplify the early stages of game development. We've included a range of essential features such as animation management, resource handling, user input handling, command queuing, entity management, and scene composition. By using this boilerplate, you can focus on the unique aspects of your game without reinventing the wheel.

### Prerequisites

Before you begin, ensure that you have the following prerequisites installed on your development machine:

- [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)
- [CMake](https://cmake.org/) (for building the project)
- [C++ Compiler](e.g., [GCC](https://gcc.gnu.org/))

### Installation

1. Clone this repository to your local machine:

   ```shell
   git clone https://github.com/Gaylubeoil/SFML-Boilerplate.git
   ```

2. Build the project using CMake:

   ```shell
   cd SFML-Boilerplate
   cmake .
   ```

3. Compile the project:

   ```shell
   make
   ```

## Code Structure

- **`Animation`**: Manages in-game animations.
- **`ResourceHolder`**: Loads and manages game resources.
- **`Player`**: Handles user input and events.
- **`CommandQueue`**: Implements a command system for game actions.
- **`Entity`**: Represents in-game entities.
- **`StateStack`**: Manages different game states.
- **`World`**: Defines the game world and interactions.
- **`SceneNode`**: Creates a hierarchy of entities for scene composition. Everything that's meant to be in the game is supposed to inherit either from this class directly, or from the Entity class.
