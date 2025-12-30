# SFML Maze Generator

Visualizes recursive backtracking (DFS) maze generation using SFML 2.6.1.

Solver coming soon.

## Demo
https://github.com/user-attachments/assets/e9b34d42-8460-4665-9da1-b5faaa438c7d

## Project Structure
```
maze-gen/
├─ CMakeLists.txt
├─ README.md
├─ include/          # headers
├─ src/              # SFML app and maze generation code
└─ build/            # CMake build output (generated)
```

## Features
- Recursive backtracking (DFS) maze generation
- Real-time SFML visualization
- Configurable grid size and draw speed (if applicable)

## How It Works
A recursive backtracking (DFS) algorithm carves passages between cells. When no unvisited neighbors remain (to avoid loops or borders), it backtracks to the last branch and continues. SFML renders the grid and carving steps.

## Getting Started
### Prerequisites
- C++ compiler with C++11 support
- CMake ≥ 3.16
- SFML 2.6.1 (dev packages installed or built from source)

### Building
```bash
cmake -B build
cmake --build build
```

### Running
```bash
./build/bin/main
```

## Configuration
- (Document CLI args or constants to change maze size/speed/colors)

## Troubleshooting
- SFML link errors: ensure SFML 2.6.1 libs and headers are on your compiler/linker paths.

## Roadmap
- Add solver visualization
- Additional generation algorithms (e.g., Prim’s, Kruskal’s)
- UI controls for size/speed

## Resources
- https://www.youtube.com/watch?v=uctN47p_KVk
- https://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking.html
- https://en.wikipedia.org/wiki/Maze_generation_algorithm
- https://www.sfml-dev.org/documentation/2.6.1/

## License
MIT

