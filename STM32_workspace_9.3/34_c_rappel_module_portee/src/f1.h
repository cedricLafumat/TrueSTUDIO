/*
 * f1.h
 *
 *  Created on: 2 avr. 2020
 *      Author: cedric
 */

#ifndef F1_H_
#define F1_H_

void f11(void) ;
void f12(void) ;

extern int f1_glob ; // DÉCLARATION : (plusieurs fois possible via le .h)
					 // Variable GLOBAL, C'est une DÉCLARATION (déclaration == on dit que
					 // ca existe, mais la mémoire n'est pas réservée à cet endroit là)

#endif /* F1_H_ */
