# Installing Linux

The main reason why the software team uses Linux is to have a similar environment to the Raspberry Pi, which our solar car's dashboard systems run on. 
As such, most projects made for our solar car will predominantly compile and run on Debian based Linux systems.

We recommend two options if you do not have Linux already.

## Dual booting [Highly Recommended] 

### Background Knowledge 

Dual booting will keep 2 operating systems on your machine (only one operating system will be running on your machine at a time), so when you first start your computer, you can choose which operating system you want to run on.
We highly recommend dual booting since you can utilize 100% of your computer's hardware for only one operating system(using a Virtual Machine, shares the PC hardware between operating systems; see VM Section).

|===
Pros | Cons
|The computer's performance is maximized since it only needs to focus on the one operating system  
|Switching between operating systems requires you to reboot the computer

|
|**There is a possibility, if you're not careful, you can delete your main OS (eg. Windows, MacOS)**
|===

For both dual booting and installing Linux on a VM, get a Linux distribution of your choice.

**Recommended distros are**

   	* Linux Mint (Latest Version)
   	* Ubuntu (Latest Version)

### How to Dual Boot

Follow the instructions and/or watch the videos below.

**For Windows**
Written Instructions: https://itsfoss.com/install-ubuntu-1404-dual-boot-mode-windows-8-81-uefi/ 
Video: https://www.youtube.com/watch?v=MSVV_EoApdo

**For Macs**
Written Instructions: https://www.howtogeek.com/187410/how-to-install-and-dual-boot-linux-on-a-mac/
Video: https://www.youtube.com/watch?v=kRgKlcm1XPI


## Running Linux in a Virtual Machine 

### Background Knowledge 

A virtual machine allows two operating systems to run simultaneously (Sharing the computer's hardware).
Using a virtual machine separates the host OS and the simulated OS, so if you are running linux in the virtual machine and windows as your main OS, they will not affect each other.

|===
Pros | Cons
|You can switch between operating systems by simply minimizing/maximizing the virtual machine
|the performance of your machine will be reduced


|There is no chance of accidentally deleting your host OS
|
|Your host OS is isolated from your virtual machine OS, so if you get a virus on your virutal machine OS, your host OS will not be affected by the virus
|
|===

***If you have a powerful PC and want to take the risk of the performance reduction, feel free to use this option.**

### How to install Linux on a Virtual Machine 
Follow the instructions and/or watch the videos below.

**For Windows**

Written Instructions: https://www.makeuseof.com/tag/install-linux-windows-vmware-virtual-machine/
Video: https://www.youtube.com/watch?v=QbmRXJJKsvs

**For Macs**

Written Instructions: https://blog.macsales.com/40342-tech-tip-how-to-install-and-run-linux-on-a-mac/
Video: https://www.youtube.com/watch?v=4SbTXqPk_1Y