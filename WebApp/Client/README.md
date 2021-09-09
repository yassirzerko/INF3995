## Lancer le client sans image Docker (node et npm requis): 

Suivez les étapes suivantes :

1. `npm install`
2. `npm start`

Ouvrir [http://localhost:3000](http://localhost:3000)

## Lancer le client à partir d'une image docker

Suivez les étapes suivantes :

1. `sudo docker build -t client .`
2. `sudo docker run -it  -p XXXX:3000 client`

Remplacer 'XXXX' par le port sur lequel vous désirez avoir l'application

Ouvrir [http://localhost:XXXX](http://localhost:XXXX)

## Test unitaires avec Jest & Enzyme

Suivez les étapes suivantes :

1. `npm install`
2. `npm test`

