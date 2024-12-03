# C++-Programmentwurf: KITTI Reaction Game
Matrikel Nr. 2222449
<br>
Matrikel Nr. 6684592

## Description
**Spielmechanik:**
- **Datensatz:**
  - Nutzung der „Left color images of tracking data set“ und „Training labels of tracking data set“ des KITTI-Datensatzes.
  - Ignorieren von Bounding Boxes des Typs „DontCare“.
  - Überspringen von Bildern ohne passende Bounding Boxes.

- Benutzeroberfläche (GUI):**
  - Konsolenmenü zur Eingabe des Spielernamens, Anzahl der zu spielenden Bilder, Sequenz und Spielmodus.
  - Anzeige der Bilder und Bounding Boxes in einem Fenster.

- Spielmodi:**
  - Mode 1 - Direct Click Reaction: Eine zufällig ausgewählte Bounding Box wird rot markiert, der Spieler muss diese so schnell wie möglich anklicken.
  - Mode 2 - Color Change Reaction: Alle Bounding Boxes werden zunächst blau dargestellt, nach einer zufälligen Zeit wird eine Box rot und der Spieler muss diese anklicken und mit der Leertaste bestätigen.

- **Feedback und Ergebnisse:**
  - Speicherung der Reaktionszeiten.
  - Anzeige der Ergebnisse am Spielende, inklusive durchschnittlicher Reaktionszeit und der besten drei Ergebnisse.
 
  - 
## How to use
### Prerequisites
1. **CMake**: Install the latest version of CMake.
2. **Compiler**: Ensure an appropriate compiler is installed:
   - **Windows**: 
     - **Visual Studio 22 (MSVC)** 
     - **MinGW** (not tested, should work aswell*)
   - **Linux**:
     - **GCC** (not tested, should work aswell*)
<br>*compiler selections will be automatic
1. **Git Bash**

### Installing OpenCV from [GitHub](https://github.com/opencv/opencv)
1. **Set up build directory**:
   1. Choose a destination for OpenCV
   2. Create a new directory
   3. Copy "installOCV.sh" from "/setup_opencv/" into the directory
<br>**It could look something like this:**
    ```
    └── KITTI_Reaction_Game_workspace (example)
        └── 📁KittiReactionGame_Projekt
            └── 📁CPP_KITTI_Reaction_Game
                └── ...
        └── 📁opencv
            └── installOCV.sh
            └── ...
    ```
2. **Install OpenCV**
    Open your chosen directory with Git Bash and run
    ```
    ./installOCV.sh
    ```
    The installation may take a while.
3. **Adjust environment variables**
- **CMakeLists.txt:**
    ```
    # Adjust OpenCV_DIR environment variable
    set(OpenCV_DIR "path/to/build_opencv")
    ```
- **System Path variable:**
    **MSVC-Compiler:** Add ```path\to\install\opencv\x64\vc17\bin```
    **MinGW-Compiler:** Add ```path\to\install\opencv\x64\mingw\bin```

### Adjust path to KITTI data source
1. **Open** ```src/kitti_dataset.cpp```
2. **Find the ```PATH_TO_DATA_SOURCE```-definition at the top and enter the path to your KITTI data location**

```
// Quelle für KITTI-Daten
#ifndef PATH_TO_DATA_SOURCE
#define PATH_TO_DATA_SOURCE "C:/Git/KittiReactionGame_Projekt/CPP_KITTI_Reaction_Game/"
#endif // PATH_TO_DATA_SOURCE
```

### Build KittiReactionGame
Open a command terminal in ```CPP_KITTI_Reaction_Game``` and run
```
cmake -S . -B build`
```

```
cmake --build build
```

### Launch KittiReactionGame
Open a terminal in ```build/Debug``` and run

```
KITTIReactionGame.exe
```

### (Optional) Build and launch with Debugging Mode
(and recommended, because it's much more interesting to see whats going on)<br>
Open a command terminal in ```CPP_KITTI_Reaction_Game``` and run
```
cmake -S . -B build_debug -DENABLE_DEBUG=ON
```
```
cmake --build build_debug
```
Run

```
 .\build_debug\debug\KITTIReactionGame.exe --debug
```

## Full Workspace Structure
**After setting everything up, your workspace should look something like this:**

```
└── 📁KittiReactionGame_Projekt
    └── 📁opencv
        └── 📁build_opencv
        └── ...
    └── 📁CPP_KITTI_Reaction_Game
        └── .gitignore
        └── CMakeLists.txt
        └── 📁helpers
            └── 📁debug
                └── debug.cpp
                └── debug.hpp
                └── debug.tpp
            └── kitti_random.cpp
            └── kitti_random.hpp
            └── member_util.hpp
            └── serialize.hpp
            └── time.cpp
            └── time.hpp
        └── 📁include
            └── bounding_box.hpp
            └── 📁game_mode
                └── game_mode.hpp
                └── mode_1_direct_click.hpp
                └── mode_2_color_change.hpp
            └── gui.hpp
            └── image.hpp
            └── kitti_dataset.hpp
            └── player.hpp
        └── main.cpp
        └── README.md
        └── 📁setup_opencv
            └── installOCV.sh
        └── 📁src
            └── bounding_box.cpp
            └── 📁game_mode
                └── game_mode.cpp
                └── mode_1_direct_click.cpp
                └── mode_2_color_change.cpp
            └── gui.cpp
            └── image.cpp
            └── kitti_dataset.cpp
            └── player.cpp
        └── workspace structure.md
        └── 📁data
            └── 📁data_tracking_image_2
                └── 📁testing
                    └── 📁image_02
                        └── 📁0000
                            └── 000000.png
                            └── 000001.png
                            └── ...
                        └── 📁0001
                            └── 000000.png
                            └── 000001.png
                            └── ...
                        └── 📁...
            └── 📁data_tracking_label_2
                └── 📁training
                    └── 📁label_02
                        └── 0000.txt
                        └── 0001.txt
                        └── ...

```
