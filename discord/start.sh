#!/bin/bash

docker run -v $(pwd)/test/bot.cpp:/app/bot.cpp -e BOT_TOKEN="$BOT_TOKEN" quoty:latest
