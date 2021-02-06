import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
})

export class AppComponent {

  public input: any;
  title = 'Telemetry Recruit Training';
  weather = 50;
  speed = NaN;
  battery = NaN;
  range = 0;
  batteryError = 0;
  speedError = 0;
  showRange = 0;

  clearSpeedMessage(){
    this.speedError = 0;
  }

  clearBatteryMessage(){
    this.batteryError = 0;
  }

  onMouseWeather(event: MouseEvent) {
    this.weather = parseInt((event.target as HTMLInputElement).value);
  }

  onKeySpeed(event: KeyboardEvent) {
    this.speed = parseInt((event.target as HTMLInputElement).value);
    if(isNaN(this.speed)){
      this.showRange = 0;
      this.speedError = 1;
    } 
    else if(this.speed < 0 || 90 < this.speed){
      this.showRange = 0;
      this.speedError = 2;
    }
    else {
      this.speedError = 0;
    }
  }

  onKeyBattery(event: KeyboardEvent) {
    this.battery = parseInt((event.target as HTMLInputElement).value);
    if(isNaN(this.battery)){
      this.showRange = 0;
      this.batteryError = 1;
    } 
    else if(this.battery < 0 || 100 < this.battery){
      this.showRange = 0;
      this.batteryError = 2;
    }
    else {
      this.batteryError = 0;
    }
  }

  calculateRange(event: MouseEvent) {
    if((this.batteryError + this.speedError) == 0){
      this.range = -(this.speed * this.speed * this.battery / 2500) + (4 * this.battery) + this.weather;
      this.showRange = 1;
    }
  }
}
