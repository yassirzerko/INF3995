FROM node:14.15.5-alpine3.11

RUN mkdir -p /usr/src/Client
WORKDIR  /usr/src/Client

COPY ./package.json /usr/src/Client/
COPY public/ public/

RUN npm cache verify && npm install 

COPY src/ src/


EXPOSE 3000

CMD ["npm","start"]


