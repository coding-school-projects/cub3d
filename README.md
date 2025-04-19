<h1 align="center">
  <img src="https://github.com/senthilpoo10/badges/blob/main/badges/cub3dm.png" width="200"/>
</h1>

<p align="center">
  <b><i>My first RayCaster with miniLibX</i></b><br>
  <i>"Relive the birth of first-person shooters"</i>
</p>

<p align="center">
  <img alt="score" src="https://img.shields.io/badge/score-125%2F100-brightgreen" />
  <img alt="team" src="https://img.shields.io/badge/team-2%20members-yellow" />
  <img alt="time spent" src="https://img.shields.io/badge/time%20spent-120%20hours-blue" />
  <img alt="XP earned" src="https://img.shields.io/badge/XP%20earned-2016-orange" />
<p align="center">
  <img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/coding-school-projects/cub3d?color=lightblue" />
  <img alt="GitHub top language" src="https://img.shields.io/github/languages/top/coding-school-projects/cub3d?color=blue" />
  <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/coding-school-projects/cub3d?color=green" />
</p>

## 📚 About The Project

cub3D is a 42 School project that recreates a Wolfenstein 3D-style raycasting engine using C and the miniLibX library. This project explores fundamental 3D rendering techniques while implementing game mechanics like texture mapping, player movement, and collision detection.

**Key Features:**
- Raycasting engine with textured walls
- Customizable maps via `.cub` configuration files
- Smooth player movement (WASD keys) and camera rotation (arrow keys)
- Different wall textures for each cardinal direction
- Configurable floor and ceiling colors
- Bonus: Minimap, mouse rotation, animated sprites, and door mechanics

## 🏁 Getting Started

### 🛠️ Installation & Compilation

1. Clone the repository:
```bash
git clone https://github.com/your-username/cub3d.git
cd cub3d
```

2. Compile the project:
```bash
make
```

3. Run with a map file:
```bash
./cub3d maps/level1.cub
```

### 🎮 Controls
| Key | Action |
|-----|--------|
| W | Move forward |
| A | Move left |
| S | Move backward |
| D | Move right |
| ← | Rotate left |
| → | Rotate right |
| ESC | Quit game |
| Mouse move | Rotate view (bonus) |

### 📝 Map File Format
Example `level1.cub`:
```
NO textures/north_wall.xpm
SO textures/south_wall.xpm
WE textures/west_wall.xpm
EA textures/east_wall.xpm
F 220,100,0  # Floor color (RGB)
C 225,30,0   # Ceiling color (RGB)

111111111
100010001
10N010001
100010001
111111111
```

## 🧠 Technical Implementation

### Core Architecture
| Component | Implementation Details |
|-----------|------------------------|
| **Raycasting** | DDA algorithm for efficient wall detection |
| **Texturing** | MiniLibX image buffers with XPM textures |
| **Movement** | Collision detection with map boundaries |
| **Event Handling** | Keyboard and mouse hooks via miniLibX |
| **Map Parsing** | Strict validation of `.cub` files |

### Bonus Features
| Feature | Implementation |
|---------|---------------|
| Minimap | Scaled-down map view in corner |
| Mouse Rotation | X11 mouse motion events |
| Animated Sprites | Frame-based texture switching |
| Doors | Spacebar-activated map changes |

## 🧪 Testing Protocol

1. Basic validation:
```bash
./cub3d maps/valid_map.cub
```

2. Error handling test:
```bash
./cub3d maps/invalid_map.cub
```

3. Performance test:
```bash
./cub3d maps/large_map.cub
```

4. Bonus features:
```bash
./cub3d maps/bonus_map.cub
```

## 📝 Evaluation Criteria

1. **Correctness**: Proper rendering and movement mechanics
2. **Performance**: Smooth rendering (60+ FPS)
3. **Error Handling**: Graceful exit on invalid maps
4. **Code Quality**: No leaks, norm compliant
5. **Bonus**: Additional features implementation

### 🧑‍💻 Peer Evaluations (3/3)

> **Peer 1**: "Thank you Poonkodi and Ola for showing your cub3d for me. Everything seems to workd as it is supposed to and could not find any leaks or make the program to crash. Rendering is smooth. First time seeing someone using actually minilib and also having the walking through walls feature in the mandatory part. Mandatory and bonus in general well splitted. Error handling well done. In the bonus there is much more speed in the movement which I would have added to the mandatory as well but thats not any issue. In general good job. Keep up the good work!"

> **Peer 2**: "Ola and Poonkodi made great job. The project look amazing, mini map is cool. But we had a small discussion about confusing the side of the walls. When we look to north we should see the south texture of the wall., that was their small issue. All parsing was good made, all cases were thought through. They were able to explain all their code So great job, girls! Good luck with next projects."

> **Peer 3**: "Thank you so much for showing your game! Map validation seems really solid and game worked really smoothly. We tried playing many maps and modified some setting. The wall textures implementation might be different from others but for me that is a personal preference and all good for me. I strongly believe that this should not be a reason that you lose some point. The folders structure are also clean and impressive. Overall, great game!! Great work and good luck with your other projects!"


