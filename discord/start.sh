#!/bin/bash

docker run -it -v $(pwd)/bot.cpp:/app/bot.cpp -e BOT_TOKEN="$BOT_TOKEN" quoty:latest
