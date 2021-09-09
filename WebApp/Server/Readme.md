# Serveur principal

Ce répertoire contient le code source du serveur principal.

# 1. Version de l'application pour le déploiement

## Lancement de l'application 

Suivez les instructions suivantes :

1. `docker build -t server .`
2. Brancher le Crazyradio PA
3. En utilisant la commande `lsusb`, déterminer sur quel port le Crazyradio est branché (dans mon cas `003`) pour l'utiliser dans l'étape suivante
4. `docker run -it --device /dev/bus/usb/003 -p XXXX:5000 server`

Remplacer 'XXXX' par le port sur lequel vous désirez avoir l'application

Ouvrir [http://localhost:XXXX](http://localhost:XXXX)

# 2. Tests unitaires avec flask unittest 

Exécutez la commande `python3 api_test.py`
