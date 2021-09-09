# Répertoire Crazyflie
 
Ce répertoire contient le code source du drone.

# 1. Version de l'application pour le déploiement

## Lancement de l'application

Suivez les étapes suivantes :

1. `docker build -t crazyflie -f Dockerfile.production .`
2. Brancher le Crazyradio PA
3. En utilisant la commande `lsusb`, déterminer sur quel port le Crazyradio est branché (dans mon cas `003`) pour l'utiliser dans l'étape suivante
4. ```docker run -it --device /dev/bus/usb/003 crazyflie```


# 2. Version de l'application pour le dévelopement

## Lancement de l'application

Suivez les étapes suivantes :

1. ```docker build -t crazyflie:latest .```
2. Brancher le Crazyradio PA
3. En utilisant la commande `lsusb`, déterminer sur quel port le Crazyradio est branché (dans mon cas `003`) pour l'utiliser dans l'étape suivante
4. ```docker run -it --mount type=bind,source="$(pwd)"/Application,target=/root/Application --device /dev/bus/usb/003 crazyflie```

## Compilation du code embarqué

Suivez les instructions suivantes :

1. Exécuter : ```cd /root/Application```
2. Exécuter : ```make clean && make all```
3. Allumer le drône en mode bootloader
4. Exécuter : ```make cload```

# 3. Configuration des adresses des drones

* Notre application supporte jusqu'à un total de 5 drones.
* S'assurer que les CrazyFlie écoutent sur la channel 56, et que leur adresses vont de : E7E7E7E701 à E7E7E7E705
* Dans le cas où moins de 5 drones vont être utilisés, il faut utiliser les plus petites adresses. Tel que pour n drones choisis, il faut avoir des adresses
comprises entre E7E7E7E701 et E7E7E7E70n
* Par exemple, pour l'utilisation de 3 drones, il faut utiliser les adresses suivantes : E7E7E7E701 E7E7E7E702 E7E7E7E703

# Source 
Nous avons importé et/ou modifié certains fichiers du répertoire GitHub open source suivant : 
* https://github.com/tudelft/SGBA_CF2_App_layer
