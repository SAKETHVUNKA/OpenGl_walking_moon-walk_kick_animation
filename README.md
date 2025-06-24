# 🕴️ OpenGL Skeletal Animation System

This OpenGL project simulates a human-like skeletal system capable of performing various animated motions such as walking, kicking, and moonwalking. The animations are controlled in real-time using keyboard inputs and enhanced with background music for an immersive experience.

---

## 🎮 Controls

| Key | Action             |
|-----|--------------------|
| W   | Walk animation     |
| K   | Kick animation     |
| M   | Moonwalk + Music   |

---

## 🎬 Demo

Watch the skeletal system in action:  
👉 [View Demo Video](https://github.com/SAKETHVUNKA/openGl_walking_moon-walk_kick_animation/assets/106236218/5b46015e-e759-4f6e-bddc-50b520ea6fab)

---

## ⚙️ Setup & Usage

1. Ensure required libraries are installed.
2. Clone this repository:
   ```bash
   git clone https://github.com/SAKETHVUNKA/openGl_walking_moon-walk_kick_animation.git
   cd openGl_walking_moon-walk_kick_animation
   ```
3. Compile the code using a compatible compiler:
   ```bash
   g++ legend.cpp -lGL -lGLU -lglut -o skeletal_animation
   ./skeletal_animation
   ```
4. Press the following keys to interact:
   - `W` – Walk
   - `K` – Kick
   - `M` – Moonwalk with music

---

## 🔧 Dependencies

- OpenGL (GL, GLU, GLUT/freeGLUT)
- Windows API (`<Windows.h>`)
- Standard C++ headers (`iostream`, `fstream`, `sstream`, etc.)
- `thread` and `chrono` libraries for sleep timing
  > ⚠️ This project is currently Windows-specific due to the use of `<Windows.h>`. Cross-platform support may require modification or abstraction of system calls and dependencies.


---

## 📂 Additional Files

- **Python CSV Generator Files**: Generate required CSV input for animation data.
- **Music File**: `dangerous.wav` is used during the moonwalk animation.

---

## 🧰 Technologies Used

- OpenGL
- C++
- GLUT / FreeGLUT
- Python (for preprocessing CSV data)
- WAV audio integration

---

## 👥 Contributors

- [Naga Saketh V](https://github.com/SAKETHVUNKA)
- [Hitesh Yadav](https://github.com/HiteshYadav007)
- [Darshan](https://github.com/DARSHANv17)

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).
