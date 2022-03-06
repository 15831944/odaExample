import ClientFactory from "./../../ClientFactory";

export class AssembliesListService {
  getPage(page, pageSize, name) {
    return ClientFactory.get().getAssemblies((page - 1) * pageSize, pageSize, name, null, true);
  }

  removeById(id) {
    return ClientFactory.get().deleteAssembly(id);
  }
}
