import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
})

export class AppComponent implements OnInit {

  public input: any;
  title = 'Telemetry Recruit Training';
  weather = 50;
  speed:number = -1;
  battery:number = -1;
  range:number = 0;
  displayText:string = "";
  speedInput:FormControl;
  batteryInput:FormControl;
  rangeForm:FormGroup;
  speedError:boolean = false;
  batteryError:boolean = false;

  ngOnInit(): void {
    this.speedInput = new FormControl('', [ Validators.required,
                                            Validators.min(0),
                                            Validators.max(90)]);
    this.batteryInput = new FormControl('', [ Validators.required,
                                              Validators.min(0),
                                              Validators.max(100)]);

    this.rangeForm = new FormGroup( {
      'speedInput': this.speedInput,
      'batteryInput': this.batteryInput
    });
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
    if(this.speed == -1) {
      this.speedError = true;
      if(this.battery == -1) {
        this.batteryError = true;
        return;
      }
      return;
    }
    this.range = -(this.speed * this.speed * this.battery / 2500) + (4 * this.battery) + this.weather;
    this.displayText = "The predicted range of the Eylsia is " + this.range + " km.";
  }
}
