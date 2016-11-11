/*
 * CMP.h
 *
 *  Created on: Nov 9, 2016
 *      Author: bzachmann
 */

#ifndef CMP_H_
#define CMP_H_

#include <Arduino.h>
#include "CMPPort.h"

#define ID_TESTMSG	0x1234



extern void cmp_update();
extern void cmp_initialize();

#endif /* CMP_H_ */
