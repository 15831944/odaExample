import { Subject } from "rxjs";

export class ViewActionComponentEvent {
  constructor() {
    this.changeEnable = new Subject();
    this.changeDefaultVisualStyle = new Subject();
    this.changeEnableHelp = new Subject();

    this.onChangeVisualStyle = new Subject();
    this.onChangeViewType = new Subject();
    this.onChangeViewToDefaultValue = new Subject();
    this.onUnselect = new Subject();
    this.onIsolateSelectedObjects = new Subject();
    this.onHideSelectedObjects = new Subject();
    this.onShowAll = new Subject();
    this.onExplode = new Subject();
    this.onCollect = new Subject();
    this.onRegeneration = new Subject();
    this.onCreatePreview = new Subject();
    this.onHelp = new Subject();
  }
}
