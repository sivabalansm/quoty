#!/bin/bash
echo "Compiling bot..."
g++ ./src/bot.cpp ./src/QuoteFactory.cpp -o bot -ldpp
echo "Running compiled binary"
./bot
