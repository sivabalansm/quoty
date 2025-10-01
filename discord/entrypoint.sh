#!/bin/bash
echo "Compiling bot..."
g++ bot.cpp -o bot -ldpp
echo "Running compiled binary"
./bot
