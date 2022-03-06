import ClientFactory from "./../../ClientFactory";

export class FileListService {
  getPage(page, pageSize, name, ext) {
    return ClientFactory.get().getFileList((page - 1) * pageSize, pageSize, name, ext, null, true);
  }

  removeById(id) {
    return ClientFactory.get().deleteFile(id);
  }

  async uploadFiles(drawingFile, references) {
    const file = drawingFile;
    const supportFormats = ClientFactory.getConfig().supportFormats;

    const extRegex = /^.*\.([\w\d]+)$/;
    const match = extRegex.exec(file.name);
    const postJob =
      match && match[1] && supportFormats.find((format) => format.toLowerCase() === match[1].toLowerCase());

    const refFileInfoList = [];

    for (let refFileData of references) {
      const response = await ClientFactory.get().uploadFile(refFileData, {
        geometry: false,
        properties: false,
      });
      refFileInfoList.push(response);
    }

    const result = await ClientFactory.get().uploadFile(file, {
      geometry: false,
      properties: false,
    });

    const refInfo = {
      references: [],
    };

    for (let refFile of refFileInfoList) {
      refInfo.references.push({ name: refFile.name, id: refFile.id });
    }

    await result.createReferences(refInfo);

    if (postJob) {
      await result.extractGeometry();
      await result.extractProperties();
    }

    return result;
  }

  downloadOriginalFile(file) {
    return file
      .downloadResource(`${file.id}${file.type}`)
      .then((arrayBuffer) => new Blob([arrayBuffer]))
      .then((blob) => window["download"](blob, file.name))
      .catch((err) => console.log(err));
  }

  downloadFile(file, fileName) {
    return file
      .downloadResource(`${fileName}`)
      .then((arrayBuffer) => new Blob([arrayBuffer]))
      .then((blob) => window["download"](blob, fileName))
      .catch((err) => console.log(err));
  }
}
