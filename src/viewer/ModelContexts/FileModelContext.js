import ClientFactory from "../../ClientFactory";

export class FileModelContext {
  constructor(fileId) {
    this._fileId = fileId;
  }

  async initialize() {
    this._file = await ClientFactory.get().getFile(this._fileId);
  }

  getHaveProperties() {
    return this._file.propertiesStatus === "done";
  }

  getModels() {
    return this._file.getModels();
  }

  getPropertiesByHandle(handle) {
    return this._file.getProperty(handle);
  }

  getExtension() {
    return this._file.type;
  }

  get() {
    return this._file;
  }

  isSupportViewPoint() {
    return true;
  }

  isSupportTransform() {
    return false;
  }
}
