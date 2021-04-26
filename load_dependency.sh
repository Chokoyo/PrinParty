currentDir="`pwd`"
fileName="main"
cd ncurses
chmod 700 configure
./configure --prefix=$currentDir --enable-widec --with-pthread
make -j
make -j install
echo "Dependencies successfully loaded!"
cd ..
g++ -I $currentDir/include -I $currentDir/include/ncursestw -L $currentDir/lib -o $fileName  $fileName.cpp -lncursestw -ldl -pthread
g++ -I $currentDir/include -I $currentDir/include/ncursestw -L $currentDir/lib -o area  area.cpp cursor.cpp -lncursestw -ldl -pthread
g++ -I $currentDir/include -I $currentDir/include/ncursestw -L $currentDir/lib -o pong  pong.cpp cursor.cpp -lncursestw -ldl -pthread
g++ -I $currentDir/include -I $currentDir/include/ncursestw -L $currentDir/lib -o candy  candy.cpp cursor.cpp -lncursestw -ldl -pthread
g++ -I $currentDir/include -I $currentDir/include/ncursestw -L $currentDir/lib -o maze  maze.cpp cursor.cpp -lncursestw -ldl -pthread
chmod 700 $fileName
clear
./$fileName
