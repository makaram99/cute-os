/***************************************************************************
 * @file    cuteOS.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Simple EOS interfaces header file. See \ref cuteOS.c for more details.
 * @version 1.0.1
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef CUTE_OS_H
#define CUTE_OS_H

/***************************************************************************
 * @brief   Sets up Timer 2 to drive the simple EOS.
 ***************************************************************************/
ERROR_t cuteOS_Init(void);

/**********************************************************************
 * @brief Create a task with the given task function and the given tick time.
 * @param[in] \c task_ptr: Pointer to the task function.
 * @param[in] \c TICK_TIME_MS: the frequency of task execution in milliseconds.
 * @return  \c ERROR_t: Check the options in the global enum \ref ERROR_t.
 * @par Example
 *      @code cuteOS_TaskCreate(task1, 1000); // task1 will run every 1 second @endcode
 *      @code cuteOS_TaskCreate(task2, 2000); // task2 will run every 2 seconds @endcode
 *          
 *********************************************************************/
ERROR_t cuteOS_TaskCreate(ERROR_t (* const task_ptr)(void), const u16_t TICK_TIME_MS);

/**********************************************************************
 * @brief Remove a task from the tasks array.
 * @param[in] \c task_ptr: Pointer to the task function.
 * @return  \c ERROR_t: Check the options in the global enum \ref ERROR_t.
 * @par Example
 *      @code cuteOS_TaskRemove(task1);       // remove task1 @endcode
 *      @code cuteOS_TaskRemove(task2);       // remove task2 @endcode
 *********************************************************************/
ERROR_t cuteOS_TaskRemove(ERROR_t (* const task_ptr)(void));


/***************************************************************************
 * @brief   The OS enters 'idle mode' between clock ticks to save power. 
 * @note    The next clock tick will return the processor to the normal operating state.
 ***************************************************************************/
void cuteOS_Start(void);

/***************************************************************************
 * @brief   Get tick time in milliseconds.
 * @param[out] \c ptr_tick_time_ms: Pointer to the tick time in milliseconds.
 * @return  \c ERROR_t: Check the options in the global enum \ref ERROR_t.
ERROR_t cuteOS_GetTickTime(u8_t * const ptr_tick_time_ms);

#endif /* SIMPLE_EOS_H */