import { Component, OnInit } from '@angular/core';
import { BatteryService } from '../../_services/battery.service';
import { Battery } from '../../_objects/battery';

@Component({
  selector: 'app-battery',
  templateUrl: './battery.component.html',
  styleUrls: ['./battery.component.css']
})
export class BatteryComponent implements OnInit {

  private battery: Battery;

  constructor(private bs: BatteryService) {
  }

  ngOnInit() {
    this.battery = this.bs.getData();
    console.log(this.battery);
  }

}