import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { BatteryComponent } from './tabs/Battery/battery.component';

const routes: Routes = [
    { path: 'battery', component: BatteryComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
