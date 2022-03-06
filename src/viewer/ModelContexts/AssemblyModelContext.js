import ClientFactory from "../../ClientFactory";

export class AssemblyModelContext {
  constructor(assemblyId) {
    this._assemblyId = assemblyId;
  }

  async initialize() {
    this._assembly = await ClientFactory.get().getAssemblyById(this._assemblyId);
  }

  getHaveProperties() {
    return true;
  }

  getModels() {
    return this._assembly.getModels();
  }

  getPropertiesByHandle(handle) {
    return this._assembly.getProperty(handle);
  }

  getExtension() {
    return "";
  }

  get() {
    return this._assembly;
  }

  isSupportViewPoint() {
    return false;
  }

  isSupportTransform() {
    return true;
  }
}
