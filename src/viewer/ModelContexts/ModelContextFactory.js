import { AssemblyModelContext } from "./AssemblyModelContext";
import { FileModelContext } from "./FileModelContext";

export class ModelContextFactory {
  create(match) {
    if (match.params.fileId) {
      return new FileModelContext(match.params.fileId);
    } else if (match.params.assemblyId) {
      return new AssemblyModelContext(match.params.assemblyId);
    }
    throw new Error("Not found fileId or assemblyId");
  }
}
