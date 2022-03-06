import { Subject } from "rxjs";

export class ViewpointListEvent {
  constructor() {
    this.changeViewpoints = new Subject();
    this.addViewpoint = new Subject();
    this.modifyViewpoint = new Subject();

    this.onSelectViewpoint = new Subject();
    this.onRemoveViewpoint = new Subject();
    this.onClose = new Subject();
  }
}
