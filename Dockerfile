FROM ubuntu:18.04

ENV TZ=Europe/Minsk
ENV DEBIAN_FRONTEND=noninteractive
ENV LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

RUN apt-get update && apt-get install -y \
    autoconf \
    build-essential \
    cmake \
    wget \
    git \
    libtool \
    pkg-config \
    xz-utils \
    # install arb dependencies
    libgmp-dev \
    libmpfr-dev \
    libflint-dev \
    libflint-arb-dev libflint-arb-doc libflint-arb2 \
    # install image libraries
    libpng-dev libjpeg-dev \
    && rm -rf /var/lib/apt/lists/*

ADD ./2.17.0.tar.gz /tmp

# install arb
RUN cd /tmp/arb-2.17.0 \
	# && ./.build_dependencies \
	&& ./configure \
	&& make \
	&& make install \
	&& rm -rf /arb-2.17.0

RUN groupadd --gid 1000 developer \
    && useradd --uid 1000 --gid developer --shell /bin/bash --create-home develop

COPY . /usr/src/app

WORKDIR /usr/src/app

RUN cmake . && make

CMD ["./mandelbrot-test"]

