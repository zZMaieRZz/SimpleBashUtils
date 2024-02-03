#!/bin/bash

docker rmi -f manhunte/valgrind:v1
docker build . -t manhunte/valgrind:v1 -f Dockerfile
docker run --name valgrind --rm -it --rm manhunte/valgrind:v1
