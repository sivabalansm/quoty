FROM ubuntu:latest

RUN apt update && apt upgrade -y

# Installation of required packages
RUN apt install -y wget g++ libopus0
RUN wget -O dpp.deb https://dl.dpp.dev/
RUN dpkg -i dpp.deb

WORKDIR /app

ENTRYPOINT ["bash", "./entrypoint.sh"]
