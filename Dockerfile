# TODO: configure the below to switch to a multi-stage build:
# https://docs.docker.com/develop/develop-images/multistage-build/
FROM debian:buster

# Default variables.
ARG GITLAB_CI_APT_REPOSITORY='deb http://download.opensuse.org/repositories/home:/librespace:/satnogs/Debian_10/ /'
ARG GITLAB_CI_APT_KEY_URL='https://download.opensuse.org/repositories/home:librespace:satnogs/Debian_10/Release.key'
ARG GITLAB_CI_OBS_PROJECT='home:librespace:satnogs'
ARG GITLAB_CI_OBS_PROJECT_UNSTABLE='home:librespace:satnogs-unstable'

# Silent and unobtrusive, see man 7 debconf.
ENV DEBIAN_FRONTEND=noninteractive

# Add the satnogs repository as a source.
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    gnupg \
    libcurl4 \
    git
RUN echo "$GITLAB_CI_APT_REPOSITORY" > /etc/apt/sources.list.d/${GITLAB_CI_OBS_PROJECT}.list
RUN apt-key adv --fetch-keys "$GITLAB_CI_APT_KEY_URL"

# Dependencies.
RUN apt-get update && apt-get install -y --no-install-recommends \
    devscripts \
    git-buildpackage \
    libcppunit-dev \
    cmake \
    pkg-config \
    libconfig++-dev \
    valgrind \
    doxygen \
    gnuradio-dev \
    libitpp-dev \
    swig \
    python \
    python-dev \
    python3 \
    python3-dev \
    build-essential
RUN apt-get update && apt-get install -y --no-install-recommends \
    libvorbis-dev \
    libpng-dev \
    zlib1g-dev \
    libpng++-dev \
    nlohmann-json3-dev

# SatNOGS module
RUN git clone https://gitlab.com/librespacefoundation/satnogs/gr-satnogs.git
WORKDIR /gr-satnogs
RUN mkdir -p build
WORKDIR /gr-satnogs/build
RUN cmake -DCMAKE_INSTALL_PREFIX=/usr ..
RUN make -j $(nproc --all)
RUN make install

WORKDIR /
ENTRYPOINT [""]