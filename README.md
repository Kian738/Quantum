# QuantumEngine

## Overview

Welcome to the QuantumEngine repository! This repository contains the whole source of the Engine, Editor and Runtime.
This document will provide a list of current issues and ongoing features.

## Current issues and ongoing features

### Setup

- [ ] Take care of the **assimp cmake mess**

### General

- [ ] Rewrite GEngine constructor using **dependency injection**
- [ ] Look at the **TODO comments** in the code

### Scene

- [ ] Create a **scene system** using EnTT
- [ ] Write a **serializer** for the scene system
- [ ] Write a **scene renderer and camera class**

### Camera

- [ ] Editor camera movement **rotates the camera** in a **weird** way
- [ ] Improve the **speed changeing system** for the camera

### ImGui and Viewport

- [ ] **ImGui layout** is not correct
- [ ] **Many panels** are **not implemented** yet
- [ ] **Colors** are **darker in** a **secondary viewport**
- [ ] Properly **resize** the viewport when the window is resized
- [ ] Make **viewport fit** into the whole viewport panel without cutting pixels off
- [ ] Add **gizmos** to the viewport

### Input

- [ ] KeyPressed events are spammed even when the key is up
- [ ] Implement proper **input** and mouse **locking**
- [ ] Implement **input mapping** and events

### UI

- [ ] Implement **UI** using RmlUI
- [ ] Write a **UI maker** for the editor

### Model and Texture loading

- [ ] **Models** are not **loaded** correctly (like the tires or the text in the test scene)
- [ ] **Textures** are **not mapped correctly**

### Rendering

- [ ] Fix **emissive textures** having wrong **colors**
- [ ] Implement **double buffering**
- [ ] Implement **anti-aliasing**
- [ ] Implement **shadow mapping**
- [ ] Implement **post-processing**
- [ ] Implement **shader-caching**
- [ ] Implement a proper **material system**
- [ ] Implement a proper **lighting system**
- [ ] Implement a **skybox system**

### Config

- [ ] Look into generating **default config files**
- [ ] Make a config file for **keybindings**
- [ ] Make a config file for **graphics settings**

### Physics

- [ ] Implement a **physics engine** using PhysX

### Audio

- [ ] Implement an **audio engine** using FMOD or something else

### Scripting

- [ ] Implement a **javascript scripting** engine using quickjs
- [ ] Implement a **C# scripting engine** using mono

### Packaging

- [ ] Implement a **packaging system** using lz4
- [ ] Implement a proper **asset system**
