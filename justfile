# basic scripts

default:
    @just --list

build:
    docker build --platform=linux/amd64 -t arianna-server .

start:
    docker run -p 8080:13000 arianna-server

test:
    python tcp/client.py

clean:
    docker rm $(docker ps -a -q --filter "ancestor=arianna-server")
    docker image rm arianna-server

stop:
    docker stop $(docker ps -q --filter "ancestor=arianna-server")
