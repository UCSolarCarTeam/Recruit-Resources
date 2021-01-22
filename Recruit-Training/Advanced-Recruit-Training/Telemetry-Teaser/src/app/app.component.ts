import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from "@angular/forms";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
})

export class AppComponent implements OnInit {
	
  public input: any;
  title = 'Telemetry Recruit Training';
  simulatorForm: FormGroup;
  inputSpeed: FormControl;
  inputBattery: FormControl;
  speed = 0;
  battery = 0;
  range = 0;
  result = "";
  weather = 50;
  
  createFormControls() {
    this.inputSpeed = new FormControl("", [Validators.required, Validators.min(0), Validators.max(90)]);
    this.inputBattery = new FormControl("", [Validators.required, Validators.min(0), Validators.max(100)]);
  }

  createForm() {
    this.simulatorForm = new FormGroup({
      inputSpeed: this.inputSpeed,
      inputBattery: this.inputBattery
    });
  }
  
  ngOnInit(): void {
    this.createFormControls();
    this.createForm();
  }
  
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
