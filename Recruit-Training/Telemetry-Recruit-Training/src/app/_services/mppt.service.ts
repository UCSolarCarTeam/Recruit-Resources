import { Injectable, EventEmitter } from '@angular/core';
import { Mppt } from '../_objects/mppt';
import { RandomService } from './random.service';

@Injectable({
  providedIn: 'root'
})
export class MpptService {
  private mppt0: Mppt;
  private mppt1: Mppt;
  private mppt2: Mppt;
  private mppt3: Mppt;

  constructor(private rs: RandomService) {
    this.mppt0 = new Mppt;
    this.mppt1 = new Mppt;
    this.mppt2 = new Mppt;
    this.mppt3 = new Mppt;

    this.updateMppt(0);
    this.updateMppt(1);
    this.updateMppt(2);
    this.updateMppt(3);
  }

  getData(num: number): Mppt {
    return this[`mppt${num}`];
  }

  private updateMppt(num: number): void {
    this[`mppt${num}`].alive = this.rs.randomBool();
    this[`mppt${num}`].arrayCurrent = this.rs.randomNumber();
    this[`mppt${num}`].arrayVoltage = this.rs.randomNumber();
    this[`mppt${num}`].batteryVoltage = this.rs.randomNumber();
    this[`mppt${num}`].temperature = this.rs.randomNumber();
  }
}
