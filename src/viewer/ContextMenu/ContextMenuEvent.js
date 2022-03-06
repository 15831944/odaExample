import { Subject } from "rxjs";

export class ContextMenuEvent {
  constructor() {
    this.onUnselect = new Subject();
    this.onIsolateSelectedObjects = new Subject();
    this.onHideSelectedObjects = new Subject();
    this.onShowAll = new Subject();
    this.onExplode = new Subject();
    this.onCollect = new Subject();
    this.onRegeneration = new Subject();
    this.onCreatePreview = new Subject();
  }
}
