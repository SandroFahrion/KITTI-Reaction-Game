# CPP_Projekt_Klos_Fahrion
# How to run this program
## 1. Open a terminal in the project directory (where the main.cpp is located) and run:

```cmake -S . -B build```

```cmake --build build```

To launch

```cd build/Debug```

```KITTIReactionGame.exe```

Launch with debugging

```cmake -S . -B build_debug -DENABLE_DEBUG=ON```
```cmake --build build_debug```
```cd build_debug/Debug```
```KITTIReactionGame.exe --debug```

```
└── 📁CPP_Projekt_Klos_Fahrion
    └── .gitignore
    └── CMakeLists.txt
    └── 📁data
        └── 📁data_tracking_image_2
        └── 📁data_tracking_label_2
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
        └── reaction_game.hpp
    └── main.cpp
    └── README.md
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
        └── reaction_game.cpp
    └── 📁test
        └── CMakeLists.txt
└── 📁opencv
    └── ...
```