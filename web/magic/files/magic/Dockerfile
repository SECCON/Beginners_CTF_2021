FROM node:14

WORKDIR /app

COPY package.json ./
COPY yarn.lock ./

RUN yarn

COPY . .

RUN chmod +x ./bin/wait

CMD ./bin/wait && yarn start
