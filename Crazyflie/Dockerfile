FROM ubuntu:18.04
LABEL crazyflie.version="1.0"

# Install common dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    dpkg \ 
    git \
    pkg-config \
    python3.7 \
    python-dev \
    python-numpy \
    sudo \
    software-properties-common \
    python3-pip \
    usbutils \
    python3-venv \
    && rm -rf /var/lib/apt/lists/*

# Install crazyflie-firmware from source
RUN cd /root/ &&\
    add-apt-repository ppa:team-gcc-arm-embedded/ppa &&\
    apt-get update &&\
    apt install gcc-arm-embedded -y &&\
    git clone --recursive https://github.com/bitcraze/crazyflie-firmware.git &&\
    cd crazyflie-firmware &&\
    make PLATFORM=cf2

# Install crazyflie-lib-clients from source 
RUN cd /root/ &&\
    git clone https://github.com/bitcraze/crazyflie-lib-python.git &&\
    cd crazyflie-lib-python &&\
    git checkout 68b27f1772f906ac76cb941ef8834ed4adb2c1a9 &&\
    pip3 install -e . &&\
    pip3 install -r requirements.txt

# Install crazyflie-clients-python from source     
RUN cd /root/ &&\
    git clone https://github.com/bitcraze/crazyflie-clients-python &&\
    cd crazyflie-clients-python &&\
    pip3 install --upgrade pip &&\
    python3 -m pip install --user -e .
    