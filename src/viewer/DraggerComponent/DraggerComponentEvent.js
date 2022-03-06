import { Subject } from "rxjs";

export class DraggerComponentEvent {
  constructor() {
    this.changeInitialization = new Subject();
    this.change3dMode = new Subject();
    this.changeEnable = new Subject();
    this.changeSupportViewPoint = new Subject();

    this.onClearViewPoint = new Subject();
    this.onActivateDraggerByName = new Subject();
    this.onSaveViewPoint = new Subject();
  }
}
