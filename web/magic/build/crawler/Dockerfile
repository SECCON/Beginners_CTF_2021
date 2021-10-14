FROM node:16-buster

RUN apt-get update \
    && apt-get install -y wget gnupg \
    && wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | apt-key add - \
    && sh -c 'echo "deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main" >> /etc/apt/sources.list.d/google.list' \
    && apt-get update \
    && apt-get install -y google-chrome-stable fonts-ipafont-gothic fonts-wqy-zenhei fonts-thai-tlwg fonts-kacst fonts-freefont-ttf libxss1 \
      --no-install-recommends \
    && rm -rf /var/lib/apt/lists/*

ENV PUPPETEER_SKIP_CHROMIUM_DOWNLOAD=true \
    PUPPETEER_EXECUTABLE_PATH=/usr/bin/google-chrome

COPY ./dumb-init_1.2.5_x86_64 /usr/local/bin/dumb-init
RUN chmod +x /usr/local/bin/dumb-init

WORKDIR /app

RUN addgroup appgroup \
    && useradd appuser -G appgroup \
    && mkdir -p /home/appuser/Downloads \
    && chown -R appuser:appgroup /home/appuser \
    && chown -R appuser:appgroup /app

COPY package.json ./
COPY yarn.lock ./

RUN yarn

COPY . .

USER appuser

ENTRYPOINT ["dumb-init", "--"]
CMD ["node", "index.js"]
