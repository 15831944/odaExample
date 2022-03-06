import { Subject } from "rxjs";

export class PropertiesEvent {
  constructor() {
    this.loadingProperties = new Subject();
    this.errorLoadProperties = new Subject();
    this.completeLoadProperties = new Subject();

    this.onClose = new Subject();
  }
}
