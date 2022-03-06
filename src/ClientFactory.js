import ODA from "open-cloud-client";

class ClientFactory {
  async initialize(serverUrl) {
    this._client = await ODA.createClient({ serverUrl });
  }

  get() {
    return this._client;
  }

  getConfig() {
    return this._config;
  }

  setConfig(config) {
    this._config = config;
  }
}

export default new ClientFactory();
