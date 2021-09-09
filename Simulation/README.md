# Simulation du comportements des drônes sur Argos

Ce répertoire contient le code source ainsi que l'environement sur lequel on simule notre application

# 1. Version de l'application pour le déploiement

## Lancement de l'application 

Suivez les étapes suivantes :

1. `docker build -t argos-simulation -f Dockerfile.production .`
2. `xhost +`
3. `docker run -it --net=host --privileged --name argos -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:rw --cap-add=SYS_PTRACE --security-opt seccomp=unconfined argos-simulation`

# 2. Version de l'application pour le dévelopement

## Lancement de l'application

Suivez les étapes suivantes :

1. `docker build -t argos-simulation .`
2. `xhost +`
3. `docker run -it --net=host --privileged --name argos -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:rw --mount type=bind,source="$(pwd)"/Application,target=/root/Application --cap-add=SYS_PTRACE --security-opt seccomp=unconfined argos-simulation`

## Compilation du code C++

Exécutez la commande suivante: `cd /root/Application && mkdir -p build && cd build && cmake .. && make && cd ..`

## Génération des murs aléatoires

Exécutez les commandes suivante:s 
1. `cd walls-generator && make && make run`
2. `sed -i '/<!--Random Walls-->/r bin/generated_argos_elements.txt' ../experiments/crazyflie_controlling.argos`
3. `make clean`

## Lancement du serveur test qui communique avec ARGoS (Optionnel)

1. `cd /root/Application`
2. `sudo apt-get update`
3. `sudo apt-get install python3-venv`
4. `python3 -m venv venv`
5. `. venv/bin/activate`
6. `pip3 install -U -r requirements.txt`
7. `pyhton3 test.py`

## Lancement de la simulation

Exécutez la commande suivante: `argos3 -c experiments/crazyflie_controlling.argos`
