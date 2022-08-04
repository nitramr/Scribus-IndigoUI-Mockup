#/bin/bash
thirdPartyFolder="./app/thirdparty/"

echo "######################################"
echo "# Download external Repositories     #"
echo "######################################"

# Advanced Dock Widgets
repDockWidgets="https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System.git"
repDockFolder="Qt-Advanced-Docking-System"
git clone "$repDockWidgets" "$thirdPartyFolder$repDockFolder"

echo "######################################"
echo "# Compile Advanced Dock Wigets       #"
echo "######################################"

cd $thirdPartyFolder$repDockFolder
mkdir build
cd ./build
cmake ../
make DESTDIR=./ install

#cmake -G Ninja -DKDDockWidgets_EXAMPLES=false ../
#cmake --build .
#cmake --build . --target install
