/*
 * led.h
 *
 * Created: 04/10/2022 08:21:43 م
 *  Author: M7med
 */ 


#ifndef LED_H_
#define LED_H_

void seven_seg_init(unsigned char portname);
void cathode_7seg_write(unsigned char portname, unsigned char portvalue);


#endif /* LED_H_ */