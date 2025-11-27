# Pokemon Finder C++

![Build Status](https://github.com/antoniw111/PokemonFinder_CPP/actions/workflows/ci.yml/badge.svg)

A fast, modern desktop application built with **C++** and **Qt6** to search for Pokemon data using [PokéAPI](https://pokeapi.co/). This project demonstrates professional project structure, asynchronous network handling, and local caching.

<!-- Add a screenshot of your app here later by dragging it into the GitHub issue/readme editor -->

## 🚀 Features

* **Asynchronous Networking:** Non-blocking API calls using `QNetworkAccessManager`. The UI never freezes!
* **Smart Caching:** Pokemon images and data are cached locally to save bandwidth and speed up subsequent lookups.
* **Modern C++:** Written in C++17 using standard practices.
* **Robust Error Handling:** Handles network drops, 404 errors, and server issues gracefully.
* **Cross-Platform:** Runs on Linux and Windows.

---

## 📥 Installation & Usage

Go to the **[Releases](../../releases)** page to download the latest version.

### 🪟 Windows Users
1.  Download `PokemonFinder-Windows.zip`.
2.  Extract the archive.
3.  Run `PokemonFinder.exe`.
    * *Note: All necessary DLLs are included in the folder.*

### 🐧 Linux Users (Read Carefully!)

> ⚠️ **IMPORTANT: SYSTEM REQUIREMENTS**
>
> The Linux version is **dynamically linked**. This means the application file is small, but it relies on Qt6 libraries being installed on your operating system.

**Before running the app, you MUST install Qt6:**

* **Arch Linux / CachyOS / Manjaro:**
    ```bash
    sudo pacman -S qt6-base qt6-svg
    ```
* **Ubuntu (22.04+) / Debian:**
    ```bash
    sudo apt install libqt6widgets6 libqt6network6 libqt6svg6
    ```
* **Fedora:**
    ```bash
    sudo dnf install qt6-qtbase qt6-qtsvg
    ```

**To run:**
1.  Download `PokemonFinder-Linux.tar.gz`.
2.  Extract it: `tar -xvf PokemonFinder-Linux.tar.gz`.
3.  Make it executable (if needed): `chmod +x PokemonFinder`.
4.  Run the binary: `./PokemonFinder`.

---

## 🛠️ Building from Source

If you want to modify the code or compile it yourself, follow these steps.

### Prerequisites
* C++ Compiler (GCC, Clang, or MSVC) supporting C++17
* CMake (3.16+)
* Qt6 Development Libraries

### Build Instructions

```bash
# 1. Clone the repository
git clone [https://github.com/TWOJA_NAZWA_UZYTKOWNIKA/PokemonFinder.git](https://github.com/TWOJA_NAZWA_UZYTKOWNIKA/PokemonFinder.git)
cd PokemonFinder

# 2. Create a build directory
mkdir build && cd build

# 3. Configure (CMake will find your Qt installation)
cmake ..

# 4. Build
cmake --build .
