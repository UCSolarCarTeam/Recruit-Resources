import { Component, OnInit } from '@angular/core';
import { MpptService } from '../../_services/mppt.service';
import { Mppt } from '../../_objects/mppt';

@Component({
  selector: 'app-mppt',
  templateUrl: './mppt.component.html',
  styleUrls: ['./mppt.component.css']
})
export class MpptComponent implements OnInit {

  private mppt0: Mppt;
  private mppt1: Mppt;
  private mppt2: Mppt;
  private mppt3: Mppt;

  constructor(private ms: MpptService) {}

  ngOnInit() {
    this.mppt0 = this.ms.getData(0);
    this.mppt1 = this.ms.getData(1);
    this.mppt2 = this.ms.getData(2);
    this.mppt3 = this.ms.getData(3);
    console.log(this.mppt0);
  }

}
