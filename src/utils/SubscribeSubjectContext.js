export class SubscribeSubjectContext {
  constructor() {
    this._observables = [];
  }

  subscribe(subject, observableNextFn) {
    this._observables.push(subject.subscribe({ next: observableNextFn }));
  }

  unsubscribe() {
    for (const observable of this._observables) {
      observable.unsubscribe();
    }
  }
}
