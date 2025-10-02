#!/bin/bash

docker run -it -v $(pwd)/entrypoint.sh:/app/entrypoint.sh -v $(pwd)/src:/app/src -e BOT_TOKEN="$BOT_TOKEN" quoty:latest
