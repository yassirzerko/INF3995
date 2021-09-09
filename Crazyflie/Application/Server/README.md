# Serveur utilisé pour lancer le conteneur Crazyflie

# Lancer le serveur à partir du repos (python3 et pip3 requis): 
`python3 -m venv venv` (si vous ne possedez pas deja le répetoire venv)

`. venv/bin/activate`

`pip3 install -U -r requirements.txt`

`python3 app.py`

Le serveur écoute sur [http://localhost:2000](http://localhost:2000)


# Avant de commit des changements : 
`. venv/bin/activate`

`pip3 freeze > requirements.txt`