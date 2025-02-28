# Snake Together - A Multiplayer Snake Game in C with SDL2

## 📌 Description
**Snake Together** is a local multiplayer Snake game written in **C**, using **SDL2** (along with **SDL2_image** and **SDL2_ttf**). It offers a modern take on the classic Snake experience, featuring various bonuses, bombs, multiple skins, and dynamic animations. With smooth rendering and a fun arcade feel, **Snake Together** is perfect for a quick local match between two players.

---

## 🎮 Features

- 🐍 **Local Multiplayer**: Two players can compete in real time on the same machine.
- 🍏 **Item Generation**: Apples to increase your length and special bonus items for unique power-ups.
- 💣 **Bombs and Obstacles**: Watch out for bombs and randomly generated obstacles that can instantly end your run!
- 🚀 **Speed and Slow Effects**: Collect speed apples to boost your snake or slow down your opponent.
- ⭐ **Invincibility (STAR)**: Become temporarily immune to collisions and negative effects.
- 🔁 **Rollback Mechanics**: Some collisions cause a “BONK” state, rolling your snake back to avoid an instant game over.
- 🏆 **Score Animations**: Dynamic floating score pop-ups for eaten apples, bonuses, or kills.
- 🎨 **Multiple Skins/Colors**: Choose your snake’s color in the menu before the game starts.
- ❌ **Error Handling**: Clean handling of errors and graceful exits when needed.

---

## 🛠 Compilation and Execution

### 🔧 Compilation
Make sure **SDL2**, **SDL2_image**, and **SDL2_ttf** are installed on your system. Then, simply run:
```sh
make
```
If everything goes well, the Snake executable (or similarly named binary) will be generated.

## ▶️ Execution

Run the game with:
```sh
./Snake_Together
```
You will be presented with a main menu to set up your snake skins and bonus availability. Once both players are ready, the game will start.

## Makefile Commands

**Clean Object Files**:
```sh
make clean
```

**Full Clean (Objects, Executable, and libft Directory)**:

```sh
make fclean
```

**Rebuild the Project**:
```sh
make re
```
**Force Recompile libft**:
```sh
make relibft
```
**Run the Game**:
```sh
make run
```

## ⌨️ Controls

	Note: These are the default controls. Check or adjust the key mappings in the input functions if needed.

| Player | Keys                | Action                                        |
|--------|---------------------|-----------------------------------------------|
| **P1** | **A / D**           | Select snake color in the menu                |
| **P1** | **W / A / S / D**   | Move up, left, down, right                    |
| **P1** | **E**               | Use bonus from inventory                      |
| **P1** | **Q**               | Activate speed boost                          |
| **P2** | **← / →**           | Select snake color in the menu                |
| **P2** | **↑ / ← / ↓ / →**   | Move up, left, down, right                    |
| **P2** | **Right Click**     | Use bonus from inventory                      |
| **P2** | **Left Click**      | Activate speed boost                          |
| **Both** | **1, 2, 3, 4**     | Select bonus in the menu                      |
| **Both** | **Esc**            | Quit the application                          |

## 📂 Project Structure

```
Snake/
├── asset/                     # Image assets (png sprites, icons, etc.)
├── include/                   # Header files
│   ├── app.h
│   ├── asset.h
│   ├── def.h
│   ├── game_logic.h
│   ├── game.h
│   ├── gametick.h
│   ├── grid.h
│   ├── input.h
│   ├── menu.h
│   ├── player.h
│   ├── render.h
│   ├── score_anim.h
│   ├── seed.h
│   ├── snake_together.h       # Main header linking everything
│   ├── snake.h
│   ├── struct.h
│   └── utils.h
├── src/
│   ├── app/                   # SDL initialization, cleanup, and core application logic
│   │   ├── app.c
│   │   └── seed.c
│   ├── common/                # Shared utilities and helpers
│   │   ├── utils.c
│   ├── core/                  # Core gameplay and rendering
│   │   ├── asset.c
│   │   ├── end_game.c
│   │   ├── game.c
│   │   ├── gametick.c
│   │   ├── grid.c
│   │   ├── player.c
│   │   ├── render.c
│   │   └── score_anim.c
│   │   ├── snake.c
│   ├── game_logic/            # Collision, bonuses, inventory, snake state
│   │   ├── actions.c
│   │   ├── collision.c
│   │   ├── rollback.c
│   ├── input/                 # Input handling for players and menu
│   │   ├── input.c
│   ├── menu/                  # Menu logic
│   │   ├── menu.c
│   ├── main.c                 # Entry point: launches the menu and game window
├── .gitignore
├── Makefile                   # Compilation rules
├── pi_10000.txt               # File containing the first 10000 decimals of π (used for seed)
├── README.md                  # Project documentation (this file)
```

## 📜 Author
	•	vbonnard (vbonnard@student.42.fr)
	•	ezeppa 	 (ezeppa@student.42.fr)

## 📌 Note

This project was developed as a personal project in parallel with 42 School and uses the SDL2 libraries.
If you encounter a bug or have suggestions, feel free to contribute! 🚀

