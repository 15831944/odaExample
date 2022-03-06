FROM node:16-alpine

RUN apk update && apk add dumb-init
RUN mkdir /web-viewer
RUN chown node:node /web-viewer
WORKDIR /web-viewer

USER node
COPY --chown=node:node config ./config
COPY --chown=node:node public ./public
COPY --chown=node:node scripts ./scripts
COPY --chown=node:node src ./src
COPY --chown=node:node package.json ./

RUN echo "{\
  \"registration_host\": \"http://localhost:9000\",\
  \"api_host\": \"http://localhost:8080\",\
  \"visualizejs_url\": \"https://opencloud.azureedge.net/libs/visualizejs/22.2/Visualize.js\",\
  \"plugins_url\": \"https://opencloud.azureedge.net/libs/visualizejs/plugins/22.2\",\
  \"pageSize\": 16,\
  \"refreshFilesTimeout\": 5000,\
  \"chunkLoadingTime\": 12000,\
  \"cda\": true,\
  \"supportFormats\": [ \"DWG\", \"DGN\", \"DWF\", \"DXF\", \"OBJ\", \"PDF\", \"RCS\", \"RFA\", \"RVT\", \"IFC\", \"NWC\", \"NWD\", \"VSF\" ]\
}" > public/config.json

RUN npm install && npm run build
CMD dumb-init node scripts/start.js
