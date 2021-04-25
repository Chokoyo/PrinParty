#!/bin/bash

currentDir="`pwd`"
fileName="main"
cd ncurses
chmod 700 configure
./configure --prefix=$currentDir --enable-widec --with-pthread --silent
make -j --silent
make -j --silent install
echo "Dependencies successfully loaded!"
g++ -I ./include -I ./include/ncursestw -L ./lib -o $fileName  $fileName.cpp -lncursestw -ldl -pthread
chmod 700 $fileName
clear
./$fileName
