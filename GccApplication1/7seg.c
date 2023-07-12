/*
 * led.c
 *
 * Created: 04/10/2022 08:20:35 م
 *  Author: M7med
 */ 

#include "DIO.h"

void seven_seg_init(unsigned char portname)
{
	DIO_vset_port_direction(portname, 0xff);
}

void cathode_7seg_write(unsigned char portname, unsigned char portvalue)
{
	unsigned char arr[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x47, 0x7f, 0x6f, 0x77, 0x7f, 0x39, 0x3f, 0x79, 0x71};
	DIO_vwrite_port(portname, arr[portvalue]);	
}


