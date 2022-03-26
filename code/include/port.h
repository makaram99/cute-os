/**********************************************************************
 * @file    port.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Port Header file for the milk pasteurization example
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 *********************************************************************/
#ifndef PORT_H
#define PORT_H

/**********************************************************************
 * In file traffic.C 
 *********************************************************************/
sbit redPin     = P1^0;   /* Port 1 pin 0 */
sbit amberPin   = P1^1;   /* Port 1 pin 1 */
sbit greenPin   = P1^2;   /* Port 1 pin 2 */

/**********************************************************************
 * In file main.C 
 *********************************************************************/
sbit led1Pin = P1^3;
sbit led2Pin = P1^4;
sbit led3Pin = P1^5;
sbit motorPin = P1^6;
sbit buzzerPin = P1^7;

#endif  /* _PORT_H */