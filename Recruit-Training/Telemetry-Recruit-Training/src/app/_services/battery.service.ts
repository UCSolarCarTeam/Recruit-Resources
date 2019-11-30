import { Injectable, EventEmitter } from '@angular/core';

import { Battery } from '../_objects/battery';
import { RandomService } from './random.service';

@Injectable({
  providedIn: 'root'
})
export class BatteryService {

  private battery: Battery;

  constructor(private rs: RandomService) {
    this.battery = new Battery;
    this.updateBattery();
  }

  getData(): Battery {
    return this.battery;
  }

  private updateBattery(): void {
    this.battery.alive = this.rs.randomBool();
    this.battery.averageCellVoltage = this.rs.randomNumber();
    this.battery.averageTemperature = this.rs.randomNumber();
    this.battery.bmsRelayStatusFlags.alwaysOnSignalStatus = this.rs.randomBool();
    this.battery.bmsRelayStatusFlags.chargeRelayEnabled = this.rs.randomBool();
    this.battery.bmsRelayStatusFlags.chargerSafetyEnabled = this.rs.randomBool();
    this.battery.bmsRelayStatusFlags.dischargeRelayEnabled = this.rs.randomBool();
    this.battery.bmsRelayStatusFlags.isChargingSignalStatus = this.rs.randomBool();
    this.battery.bmsRelayStatusFlags.isReadySignalStatus = this.rs.randomBool();
    this.battery.bmsRelayStatusFlags.malfunctionIndicatorActive = this.rs.randomBool();
    this.battery.bmsRelayStatusFlags.multiPurposeInputSignalStatus = this.rs.randomBool();
    this.battery.fanSpeed = this.rs.randomNumber();
    this.battery.fanVoltage = this.rs.randomNumber();
    this.battery.highCellVoltage = this.rs.randomNumber();
    this.battery.highCellVoltageId = this.rs.randomNumber();
    this.battery.highTemperature = this.rs.randomNumber();
    this.battery.highThermistorId = this.rs.randomNumber();
    this.battery.internalTemperature = this.rs.randomNumber();
    this.battery.lowCellVoltage = this.rs.randomNumber();
    this.battery.lowCellVoltageId = this.rs.randomNumber();
    this.battery.lowTemperature = this.rs.randomNumber();
    this.battery.lowThermistorId = this.rs.randomNumber();
    this.battery.packAmphours = this.rs.randomNumber();
    this.battery.packCurrent = this.rs.randomNumber();
    this.battery.packDepthOfDischarge = this.rs.randomNumber();
    this.battery.packStateOfCharge = this.rs.randomNumber();
    this.battery.packVoltage = this.rs.randomNumber();
    this.battery.populatedCells = this.rs.randomNumber();
    this.battery.requestedFanSpeed = this.rs.randomNumber();
    this.battery.totalPackCapacity = 168;
    this.battery.twelvevinputVoltage = this.rs.randomNumber();
    this.battery.averageCellVoltage = this.rs.randomNumber();
    this.battery.lowCellVoltage = this.rs.randomNumber();
    this.battery.highCellVoltage = this.rs.randomNumber();
  }
}
