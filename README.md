# DeviceDrivers

Question i have chosen from my set
5. Write a C program to capture the key strokes of capital letters.

Folder CED17I008_ENDSEM_DEVICEDRIVERS:
1. keyC.c - main code file 
2. Makefile 

Folder - EndSem_output
-Contains the output 

Steps:
$ make
$ sudo insmod keyC.ko
$ dmesg | tail -40
$ sudo rmmod keyC.ko
