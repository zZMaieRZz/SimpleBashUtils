FROM --platform=linux/amd64 ubuntu:latest
LABEL author="Aleksey Kadnikov aka manhunte <manhunte@student.21-school.ru>"
ENV TZ=Europe/Moscow
RUN apt-get update && apt-get upgrade && apt-get install -y pkg-config build-essential libudev-dev \
    make \
    gcc \
    glibc-source \
    git \
    git-lfs \
    curl \
    jq \
    bash \
    python3 \
    valgrind \
    cppcheck \
    clang-format
WORKDIR "/project"

COPY . /project

ENTRYPOINT ["/bin/bash", "scripts/test.sh"]

