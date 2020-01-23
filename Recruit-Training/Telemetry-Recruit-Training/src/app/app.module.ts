import { BrowserModule } from '@angular/platform-browser';
import { MatTabsModule } from '@angular/material';
import { NgModule } from '@angular/core';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { BatteryComponent } from './tabs/battery/battery.component';
import { MpptComponent } from './tabs/mppt/mppt.component';

@NgModule({
  declarations: [
    AppComponent,
    BatteryComponent,
    MpptComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    MatTabsModule,
    HttpClientModule,
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
