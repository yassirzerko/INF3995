FROM ubuntu:18.04

# Install common dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    dpkg \ 
    git \
    pkg-config \
    python \
    python-dev \
    python-numpy \
    sudo \
    software-properties-common \
    python3-pip \
    usbutils \
    python3-venv \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install --no-cache-dir --upgrade pip 

RUN mkdir -p /usr/src/Server
WORKDIR /usr/src/Server

# Install crazyflie-lib-clients from source 
RUN cd /root/ &&\
    git clone https://github.com/bitcraze/crazyflie-lib-python.git &&\
    cd crazyflie-lib-python &&\
    git checkout 68b27f1772f906ac76cb941ef8834ed4adb2c1a9


RUN python3 -m venv venv

RUN . venv/bin/activate &&\
    pip3 install -e /root/crazyflie-lib-python

RUN . venv/bin/activate &&\
    pip3 install -r /root/crazyflie-lib-python/requirements.txt 

COPY requirements.txt .

RUN . venv/bin/activate &&\
    pip3 install -U -r requirements.txt

EXPOSE 5000


COPY app.py .
COPY src/ src/


CMD . venv/bin/activate && exec python3 app.py
