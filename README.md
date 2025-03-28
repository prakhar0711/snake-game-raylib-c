# 🐍 Snake Game

A simple **Snake Game** built using **C** and **Raylib** for graphics rendering. This game features classic snake mechanics, including food collection, self-collision detection, and wrap-around movement.

## 🎮 Game Features
- Classic **snake movement** with arrow keys.
- **Food spawning** and score tracking.
- **Wrap-around** mechanics (snake teleports to the opposite side of the screen).
- **Dynamic growth** upon consuming food.
- **Game over** on self-collision.

## 🛠️ Dependencies
Ensure you have the following installed:
- **Raylib** (for graphics rendering)
- **GCC** (or any C compiler)
- **Linux** (or Windows with MinGW)

### Install Raylib on Linux (Arch, Debian, Ubuntu, etc.)
```sh
sudo pacman -S raylib   # Arch-based
sudo apt install libraylib-dev  # Debian-based
```

## 🚀 How to Build and Run
Clone the repository and build the project using the provided Makefile:

```sh
git clone https://github.com/yourusername/snake-game.git
cd snake-game
make   # Compile the game
./main  # Run the game
make run   # Run the program
```

## 📝 Controls
- **Arrow Keys** → Move the snake
- **Enter** → Restart after game over

## 🏗️ Code Structure
```
📂 snake-game
├── 📄 main.c        # Game logic and rendering
├── 📄 Makefile      # Compilation instructions
├── 📄 README.md     # Project documentation
```

## 🧹 Clean Build
To remove the compiled binary, run:
```sh
make clean
```

## ⚡ Future Improvements
- Add **sound effects** and background music.
- Implement **difficulty levels**.
- Enhance **UI and animations**.

## 🤝 Contributions
Feel free to fork the repo, submit issues, or create pull requests! 🎉

