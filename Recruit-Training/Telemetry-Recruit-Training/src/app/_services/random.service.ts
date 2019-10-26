import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class RandomService {

  constructor() { }

  randomNumber() {
    return (Math.random() * 100);
  }
  randomBool() {
    return (Math.random() >= 0.5);
  }
}
