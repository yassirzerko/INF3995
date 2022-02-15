# INF3995-H21-3

Ceci est le répertoire pour le Projet Intégrateur III INF3995 - Projet de conception d'un système informatique de l'équipe 103 composée des membres :
* Mohamed Yassir El Aoufir
* Paul Clas
* Mazigh Ouanes
* Tarik Agday
* Nabil Dabouz

# 1. Configuration des adresses des drones

* Notre application supporte jusqu'à un total de 5 drones.
* S'assurer que les CrazyFlie écoutent sur la channel 56, et que leur adresses vont de : E7E7E7E701 à E7E7E7E705
* Dans le cas où moins de 5 drones vont être utilisés, il faut utiliser les plus petites adresses. Tel que pour n drones choisis, il faut avoir des adresses
comprises entre E7E7E7E701 et E7E7E7E70n
* Par exemple, pour l'utilisation de 3 drones, il faut utiliser les adresses suivantes : E7E7E7E701 E7E7E7E702 E7E7E7E703

# 2. Lancement de l'application web

Cloner le répertoire en exécutant les commandes suivantes : 
1. `git clone https://gitlab.com/polytechnique-montr-al/inf3995/20211/equipe-103/inf3995-h21-3.git`
2. `git checkout RR`

## 1. Avec une seule ligne de commande : 

### Dépendances
1. Python3 
2. Docker-compose 1.25.0 **(IMPORTANT)**
3. xhost

### Lancement de l'application : 
1. Brancher le Crazyradio PA

Dans le repertoire courant (`/inf3995-H21-3`): 

2. `python3 launch.py`

## 2. Autrement :

### Dépendances
1. Docker-compose 1.25.0 **(IMPORTANT)**
2. xhost

### Lancement de l'application : 
Dans le repertoire courant (`/inf3995-H21-3`): 
1. Brancher le Crazyradio PA
2. En utilisant la commande `lsusb`, déterminer sur quel bus {ID} le Crazyradio est branché pour l'utiliser à l'étape 5
3. `xhost +`
4. `sudo docker-compose build`
5. `BUS_ID={ID} sudo docker-compose up`

Le client React écoute sur [http://localhost:3000](http://localhost:3000)

Le serveur principal écoute sur [http://localhost:5000](http://localhost:5000)

Le serveur de la simulation écoute sur [http://localhost:2000](http://localhost:2000)

Le serveur de l'application crazyflie écoute sur [http://localhost:4000](http://localhost:4000)


# 3. Assurance Qualité: Test de regression (pipline ci/cd)

Voici le status du du pipeline:

https://gitlab.com/polytechnique-montr-al/inf3995/20211/equipe-103/inf3995-h21-3/-/commits/master

# 4. Respect des requis

| Requis  | Respect du requis | Commentaire                                                                                                                                                                                                                                                             |
|---------|-------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| R.F.1   | V                 |                                                                                                                                                                                                                                                                         |
| R.F.2   | V                 | Notre application peut fonction avec un total de 5 drones.                                                                                                                                                                                                               |
| R.F.3   | V                 |                                                                                                                                                                                                                                                                         |
| R.F.4   | V                 |Démonstration vidéo de tous l'embarqué à l'exception de "software update" : https://www.youtube.com/watch?v=5XKBV-7i9_0&t=3s&ab_channel=PaulClas , démonstration vidéo de "software update" : https://drive.google.com/file/d/1z_gAMiVYu2nIm-q2EUU3EfdZLuDHF5Cg/view?usp=sharing .                                                                                                                                                                                                                             |
| R.F.4.1 | V                 |                                                                                                                                                                                                                                                                         |
| R.F.4.2 | V                 |                                                                                                                                                                                                                                                                         |
| R.F.4.3 | V                 | Les drones peuvent pas décoller avec un niveau de batterie inférieur à 30%. Le retour à la base est déclenché lorsque le niveau de batterie des drones est inférieure à 30%. L'atterrissage est déclenché lorsque le niveau de batterie des drones est inférieur à 10%. |
| R.F.5   | V                 | Nous avons en plus, un état pour l'essaim qui nous permet de gérer les permissions.                                                                                                                                                                                     |
| R.F.6   | V                 |                                                                                                                                                                                                                                                                         |
| R.F.7   | V                 |                                                                                                                                                                                                                                                                         |
| R.M.1   | V                 |                                                                                                                                                                                                                                                                         |
| R.M.2   | V                 |                                                                                                                                                                                                                                                                         |
| R.M.3   | V                 |                                                                                                                                                                                                                                                                         |
| R.M.4   | V                 |                                                                                                                                                                                                                                                                         |
| R.C.1   | V                 |Démonstration vidéo du fonctionenment de l'application Argos : https://www.youtube.com/watch?v=sV4BOLxrwaU&ab_channel=PaulClas .                                                                                                                                                                                                                                                                         |
| R.C.2   | ?                 | Le client et le serveur possèdent des tests.                                                                                                                                                                                                                            |
| R.C.3   | V                 | Voir gitlab-ci.yml‎ .                                                                                                                                                                                                                                                      |
| R.C.4   | V                 | Nous pouvons lancer tout le projet, avec une seule ligne de commande. Démonstration vidéo : https://drive.google.com/file/d/1WvAY13BFrgcXFEfXDXkxnbEdSmDmpY6I/view?usp=sharing .                                                                                                                                                                                                  |
| R.C.5   | V                 |                                                                                                                                                                                                                                                                         |
| R.C.6   |                   |                                                                                                                                                                                                                                                                         |
| R.L.1   | V                 |                                                                                                                                                                                                                                                                         |
| R.L.2   | V                 |                                                                                                                                                                                                                                                                         |
| R.L.3   | ?                 | La fonctionnalité est implémentée mais n'est pas utilisée .                                                                                                                                                                                                                |
| R.L.4   | X                 | L'application est responsive, mais non visualisable par réseau sur un autre appareil.                                                                                                                                                                                   |
| R.L.5   | V                 | Nous avons une console dans le client qui permet d'afficher les logs en temps réel. Nous avons deux routes dans le client (à partir de la page d'accueil) qui permettent de visualiser les logs  des explorations (utilisation d'un base de donnée). Nous avons également un système de logs dans la console de ARGoS.                  |
| R.L.6   | V                 |                                                                                                                                                                                                                                                                         |
| R.Q.1   | ?                 |                                                                                                                                                                                                                                                                         |
| R.Q.2   | ?                 |                                                                                                                                                                                                                                                                         |
| R.Q.3   | ?                 |                                                                                                                                                                                                                                                                         |
| R.Q.4   | ?                 |                                                                                                                                                                                                                                                                         |
| Requis supplémentaire  | ?                | Nous avons réalisé un guide d'utilisation contenant des vidéos qui montrent le fonctionnement de l'application.                                                                                                                                                                                                                                                                         |
