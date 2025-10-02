#!/bin/bash

docker run -it -v $(pwd)/test/bot.cpp:/app/bot.cpp -e BOT_TOKEN="$BOT_TOKEN" quoty:latest
