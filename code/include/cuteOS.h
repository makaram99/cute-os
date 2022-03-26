/***************************************************************************
 * @file    cuteOS.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Simple EOS interfaces header file. See \ref cuteOS.c for more details.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef CUTE_OS_H
#define CUTE_OS_H

/***************************************************************************
 * @brief Set callback function for Simple EOS
 * @param taskPtr: pointer to the task function
 * @return ERROR Status: Check the options in the global enum \ref ERROR_t.
 * @note This function is called by the user to set the callback function
 *       for the Simple EOS
 * @par Example
 *      @code 
 *      // Set the callback function for the Simple EOS to the function LED_Toggle()
 *      cuteOS_setCallback(LED_Toggle);  // LED_Toggle() is a function that toggles the LED
 *      @endcode
 * 
 ***************************************************************************/
ERROR_t cuteOS_SetCallback( ERROR_t (* const taskPtr)(void) );

/***************************************************************************
 * @brief   Sets up Timer 2 to drive the simple EOS.
 ***************************************************************************/
ERROR_t cuteOS_Init(void);

/**********************************************************************
 * @brief Create a task with the given task function and the given tick time.
 * @param[in] taskPtr: Pointer to the task function.
 * @param[in] TICK_MS: the frequency of task execution in milliseconds.
 * @return  ERROR Status: Check the options in the global enum \ref ERROR_t.
 * @par Example
 *      @code cuteOS_TaskCreate(task1, 1000); // task1 will run every 1 second @endcode
 *      @code cuteOS_TaskCreate(task2, 2000); // task2 will run every 2 seconds @endcode
 *          
 *********************************************************************/
ERROR_t cuteOS_TaskCreate(ERROR_t (* const taskPtr)(void), const u16 TICK_MS);

/**********************************************************************
 * @brief Remove a task from the tasks array.
 * @param[in] taskPtr: Pointer to the task function.
 * @return  ERROR Status: Check the options in the global enum \ref ERROR_t.
 * @par Example
 *      @code cuteOS_TaskRemove(task1);       // remove task1 @endcode
 *      @code cuteOS_TaskRemove(task2);       // remove task2 @endcode
 *********************************************************************/
ERROR_t cuteOS_TaskRemove(ERROR_t (* const taskPtr)(void));


/***************************************************************************
 * @brief   The OS enters 'idle mode' between clock ticks to save power. 
 * @note    The next clock tick will return the processor to the normal operating state.
 ***************************************************************************/
void cuteOS_Start(void);

/***************************************************************************
 * @brief Set the tick time in milliseconds
 * 
 * @param TICK_MS: tick time in milliseconds
 * @return ERROR Status: Check the options in the global enum \ref ERROR_t.
 * @par Example
 *      @code  
 *      cuteOS_SetTickTime(1000);     // Set the tick time to 1 second
 *      @endcode
 ***************************************************************************/
ERROR_t cuteOS_SetTickTime(const u8 TICK_MS);

/***************************************************************************
 * @brief Get the tick time in milliseconds
 * 
 * @param TICK_MS: pointer to the tick time in milliseconds
 * @return ERROR Status: Check the options in the global enum \ref ERROR_t.
 * @par Example
 *      @code  
 *      u8 tickTimeInMs;
 *      // Get the tick time in milliseconds and store it in tickTimeInMs
 *      cuteOS_GetTickTime(&tickTimeInMs);    
 *      @endcode
 ***************************************************************************/
ERROR_t cuteOS_GetTickTime(u8 * const TICK_MS);

#endif /* SIMPLE_EOS_H */