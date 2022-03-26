/*************************************************************************************
 * @file    main.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Project Header for \ref main.c
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ************************************************************************************/
#ifndef MAIN_H
#define MAIN_H

/*--------------------------------------------------------------*/
/* WILL NEED TO EDIT THIS SECTION FOR EVERY PROJECT             */
/*--------------------------------------------------------------*/
/* Oscillator / resonator frequency (in Hz) e.g. (11059200UL)   */
#define OSC_FREQ        (12000000UL)

/***************************************************************
 * @brief Number of oscillations per instruction (12, etc)
 * @details Options:
 *              - 12: Original 8051 / 8052 and numerous modern versions
 *              - 6 : Various Infineon and Philips devices, etc.
 *              - 4 : Dallas 320, 520 etc.
 *              - 1 : Dallas 420, etc.
 ***************************************************************/
#define OSC_PER_INST        (12)





/*-------------------------------------------------------------*/
/* SHOULD NOT NEED TO EDIT THE SECTIONS BELOW                  */
/*-------------------------------------------------------------*/
/* Interrupts number of Timers overflow from the vector table of the 8051 */
#define INTERRUPT_Timer_0_Overflow          1
#define INTERRUPT_Timer_1_Overflow          3
#define INTERRUPT_Timer_2_Overflow          5


#endif  /* MAIN_H */
