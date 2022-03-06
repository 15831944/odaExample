import ClientFactory from "./../../ClientFactory";

export class JobsService {
  async getPage(page, pageSize, filters) {
    const { allSize, result } = await ClientFactory.get().getJobs(
      (filters || []).join("|"),
      pageSize,
      (page - 1) * pageSize,
      true
    );

    const fileIds = [];
    const assemblyIds = [];

    const resNameIdMap = new Map();

    for (let job of result) {
      job.fileId ? fileIds.push(job.fileId) : assemblyIds.push(job.assemblyId);
    }

    const files = await ClientFactory.get().getFileList(0, allSize, null, null, fileIds);
    const assemblies = await ClientFactory.get().getAssemblies(0, allSize, null, assemblyIds);

    for (let file of files.list) {
      resNameIdMap.set(file.id, file.name);
    }

    for (let assembly of assemblies.list) {
      resNameIdMap.set(assembly.id, assembly.name);
    }

    for (let job of result) {
      job.fileId
        ? (job.fileName = resNameIdMap.get(job.fileId))
        : (job.assemblyName = resNameIdMap.get(job.assemblyId));
    }

    return { allSize, result };
  }
}
