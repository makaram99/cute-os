/********************************************************************************
 * @file    main.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Testing cute OS.
 * @details	Traffic light system (Chapter 8 - Embedded C by Professor j. Pont). 			
 * 			See \ref traffic.c for the implementation and sequence of the system.
 * @version 1.0.0
 * @date    2022-03-24
 * @copyright Copyright (c) 2022
 * 
 * @details	Application usage:
 * 			- Run the application.
 * 			- The application will run the traffic light system.
 * 			- The system will run in a loop:
 * 				1. Red for some seconds, then
 * 				2. Red-Amber for some seconds, then
 * 				3. Green for some seconds, then
 * 				4. Amberfor some seconds, then
 * 				5. Repeat from step 1.
 * 			The duration of each state is defined in the enum 
 * 			\ref TRAFFIC_SEQUENCE_DURATION_t in \ref traffic_cfg.h file.	
 * 			
 * 			Code explanation:
 * 			1. Initialize the Cute OS.
 *              @code cuteOS_Init();    @endcode
 *          2. Initialize the tasks.
 * 				@code TRAFFIC_Init();	@endcode
 * 				See \ref TRAFFIC_Init() for more details.
 * 			3. Create the tasks.
 *              @code cuteOS_TaskCreate(task1, 1000); // task1 will run every 1 second  @endcode
 *              @code cuteOS_TaskCreate(task2, 2000); // task2 will run every 2 seconds @endcode
 *          4. Start the Cute OS scheduler.
 *              @code cuteOS_Start();   @endcode
 ********************************************************************************/
#include <reg52.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Main.h"
#include "Port.h"
#include "cuteOS.h"
#include "traffic.h"

/*------------------------------------------------------------------------------*/
/*	THE FOLLOWING ARE ONLY FOR TESTING THE SIMPLE OS.				  			*/
/*	DO NOT USE THEM IN YOUR APPLICATION.							  			*/
/*------------------------------------------------------------------------------*/
void led1_toggle(void){
	led1Pin = !led1Pin;
}

void led2_toggle(void){
	led2Pin = !led2Pin;
}

void led3_toggle(void){
	led3Pin = !led3Pin;
}

void motor_toggle(void){
	motorPin = !motorPin;
}

void buzzer_toggle(void){
	buzzerPin = !buzzerPin;
}

void Init_Others(void) {
	led1Pin = 1;
	led2Pin = 0;
	led3Pin = 0;
	motorPin = 1;
	buzzerPin = 0;
}






/*------------------------------------------------------------------------------*/
/*					APPLICATION MAIN FUNCTION						  			*/
/*------------------------------------------------------------------------------*/
void main(void) {
	/* Initialize the system */
	cuteOS_Init();					/*!< Initialize Cute OS 					*/
	TRAFFIC_Init();					/*!< Initialize the traffic light system	*/
	Init_Others();					/*!< Initialize other peripherals			*/

	/*!< Create the tasks */
	cuteOS_TaskCreate(TRAFFIC_Update, 1000);	/*!< Create a task to run the traffic light system */
	cuteOS_TaskCreate(led1_toggle	, 1000);	/*!< Create a task to toggle the first LED */
	cuteOS_TaskCreate(led2_toggle	, 2000);	/*!< Create a task to toggle the second LED */
	cuteOS_TaskCreate(led3_toggle	, 4000);	/*!< Create a task to toggle the third LED */
	cuteOS_TaskCreate(buzzer_toggle	, 2000);	/*!< Create a task to toggle the buzzer */
	cuteOS_TaskCreate(motor_toggle	, 5000);	/*!< Create a task to toggle the motor */
	
	cuteOS_TaskRemove(buzzer_toggle);	/*!< Remove the task to toggle the buzzer */

	cuteOS_Start();
}
