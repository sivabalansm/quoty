#!/bin/bash

docker run -it -v $(pwd)/entrypoint.sh:/app/entrypoint.sh -v $(pwd)/src/quote.md:/app/quote.md -v $(pwd)/src:/app/src -e BOT_TOKEN="$BOT_TOKEN" quoty:latest
