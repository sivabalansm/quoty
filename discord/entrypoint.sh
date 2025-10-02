#!/bin/bash
echo "Compiling bot..."
g++ ./src/bot.cpp ./src/QuoteRepo.cpp -o bot -ldpp
echo "Running compiled binary"
./bot
