#!/bin/bash -e
myRepo=$(pwd)
CMAKE_GENERATOR_OPTIONS=(-G"Visual Studio 17 2022" -A x64)
if [ ! -d "$myRepo/opencv" ]; then
 echo "cloning opencv"
 git clone https://github.com/opencv/opencv.git
else
 cd opencv
 git pull --rebase
 cd ..
fi
if [ ! -d "$myRepo/opencv_contrib" ]; then
 echo "cloning opencv_contrib"
 git clone https://github.com/opencv/opencv_contrib.git
else
 cd opencv_contrib
 git pull --rebase
 cd ..
fi
RepoSource=opencv
mkdir -p build_opencv
pushd build_opencv
CMAKE_OPTIONS=(-DBUILD_PERF_TESTS:BOOL=OFF -DBUILD_TESTS:BOOL=OFF -DBUILD_DOCS:BOOL=OFF -DWITH_CUDA:BOOL=OFF -DBUILD_EXAMPLES:BOOL=OFF -DINSTALL_CREATE_DISTRIB=ON)
set -x
cmake "${CMAKE_GENERATOR_OPTIONS[@]}" "${CMAKE_OPTIONS[@]}" -DOPENCV_EXTRA_MODULES_PATH="$myRepo"/opencv_contrib/modules -DCMAKE_INSTALL_PREFIX="$myRepo/install/$RepoSource" "$myRepo/$RepoSource"
echo "************************* $Source_DIR -->debug"
cmake --build . --config debug
echo "************************* $Source_DIR -->release"
cmake --build . --config release
cmake --build . --target install --config release
cmake --build . --target install --config debug
popd
