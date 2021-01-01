import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
})

export class AppComponent {

  public input: any;
  title = 'Telemetry Recruit Training';
  weather = 50;
  speed = 0;
  battery = 0;
  Sinput = new FormControl(0, [Validators.required, Validators.min(0), Validators.max(90)]);
  Binput = new FormControl(0, [Validators.required, Validators.min(0), Validators.max(100)]);

  onMouseWeather(event: MouseEvent) {
    this.weather = parseInt((event.target as HTMLInputElement).value);
  }

  onKeySpeed(event: KeyboardEvent) {
    this.speed = parseInt((event.target as HTMLInputElement).value);
  }

  onKeyBattery(event: KeyboardEvent) {
    this.battery = parseInt((event.target as HTMLInputElement).value);
  }


  calculateRange() {
    this.speed = this.Sinput.value
    this.battery = this.Binput.value
    this.weather = parseInt((document.getElementById("weather") as HTMLInputElement).value);
    var range = -1 * (this.speed * this.speed * this.battery / 2500) + (4 * this.battery) + this.weather;
    document.getElementById("Range").innerHTML = "The predicted range of the Elysisa is " + String(range) + " km.";
  }
}
