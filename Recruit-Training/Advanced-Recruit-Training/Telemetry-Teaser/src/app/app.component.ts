import { Component, OnInit } from '@angular/core'
import {
    FormsModule,
    FormGroup,
    FormControl
} from '@angular/forms';

class Calculate {
  constructor(public speed: number = 0,
			  public battery: number = 0,
              public range: number = 0,
			  public weather: number = 50,
              public result: string = '') { }
}

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
})

export class AppComponent {
	model: Calculate = new Calculate();
	
	speed = new FormControl('', [ Validators.required,
                                            Validators.min(0),
                                            Validators.max(90)]);

 public input: any;
  title = 'Telemetry Recruit Training';
  weather = 50;
  speed = 0;
  battery = 0;
  range = 0;
  result = '';

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
	this.range = -(this.speed * this.speed * this.battery / 2500)  +  (4 * this.battery) + this.weather;
	this.result = "The predicted range of the Eylsia is " + this.range + " km.";
  }
}
