/**********************************************************************
 * @file    cuteOS.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Main file for Cute Embedded Operating System (cuteOS) for 8051.
 * @details cuteOS schedules the tasks in a cooperative manner.
 *          It invokes te scheduler (\ref cuteOS_ISR()) periodically by Timer 
 *          overflow. So, the timing of the tasks is determined by the 
 * 			frequency of Timer overflow defined by the variable \ref cuteOS_TICK_TIME.
 * @note    cuteOS uses the timer2 for scheduling.
 * @version 1.1.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 * @details Application usage:
 *          - At main.c:
 *              1. Initialize the Cute OS.
 *                  @code cuteOS_Init();    @endcode
 *              2. Initialize the tasks.
 *                  @code cuteOS_TaskCreate(task1, 1000); // task1 will run every 1 second  @endcode
 *                  @code cuteOS_TaskCreate(task2, 2000); // task2 will run every 2 seconds @endcode
 *              3. Start the Cute OS scheduler.
 *                  @code cuteOS_Start();   @endcode
 *********************************************************************/
#include <reg52.h>
#include "STD_TYPES.h"
#include "main.H"
#include "cuteOS.h"

/*--------------------------------------------------------------------*/
/* PRIVATE FUNCTIONS DECLARATION                                      */
/*--------------------------------------------------------------------*/
static ERROR_t cuteOS_SetTickTime(const u8_t TICK_TIME_MS);
static ERROR_t cuteOS_GCD(u32_t *gcd);
static ERROR_t cuteOS_UpdateTicks(void);
static void cuteOS_Sleep(void);
static void cuteOS_ISR();


/*--------------------------------------------------------------------*/
/*                          PRIVATE DATA                              */
/*--------------------------------------------------------------------*/
/**********************************************************************
 * @brief   Maximum tick time in milliseconds.
 * @details This variable is used to set the maximum tick time in milliseconds.
 *          The maximum tick time is used to set the maximum time of the tasks.
 *          It has a maximum value of 65 ms because:
 *          1. The maximum value of the timer 2 is 65535 (16-bit timer).
 *          2. The 8051 microcontroller has 1 MIPS (1 million instructions per second),
 *             with 12MHz clock, and 12 clock cycles per instruction.
 *          So, the maximum tick time = (65535 * 12) / 12000000 = 65 ms. 
 *********************************************************************/
#define MAX_TICK_TIME_MS  65         

/*!< Tick time in ms (must be less than MAX_TICK_TIME_MS). */
static u8_t cuteOS_tick_time_ms = 0; 

/*!< Number of ticks, which is incremented by 1 at each Timer 2 overflow. */
static u16_t cuteOS_tick_count = 0;

#define MAX_TASKS_NUM   8

/*!< Number of tasks created by the user. */
static u8_t cuteOS_task_counter = 0;         /*!< Counter for the number of tasks created */

/*!< Task Information Structure. */
typedef struct {
    ERROR_t (*callback)(void);    /*!< Pointer to the task function */
    u32_t delay_ms;                    /*!< Delay in ms */
    u16_t ticks;    /*!< Number of ticks after which the task will run */
    u8_t  id;       /*!< Task ID */    
}cuteOS_TASK_t;

/*!< Tasks array containing tasks information. */
cuteOS_TASK_t tasks[MAX_TASKS_NUM] = {0};







/*--------------------------------------------------------------------*/
/*                          PUBLIC FUNCTIONS                          */
/*--------------------------------------------------------------------*/
/**********************************************************************
 * @details This function does the following:
 *          - Increment the task counter.
 *          - Set the task ID.
 *          - Set the pointer to the task function.
 *          - Set the number of schedular ticks after which the task will run.
 *********************************************************************/
ERROR_t cuteOS_TaskCreate(ERROR_t (* const callback)(void), const u16_t TICK_TIME_MS) {
    ERROR_t error = ERROR_NO;

    if(cuteOS_task_counter < MAX_TASKS_NUM) {
        ++cuteOS_task_counter;
        tasks[cuteOS_task_counter - 1].id = cuteOS_task_counter - 1;
        tasks[cuteOS_task_counter - 1].delay_ms = TICK_TIME_MS;
        tasks[cuteOS_task_counter - 1].callback = callback;

        // error |= cuteOS_UpdateTicks();
    } else {
        error |= ERROR_OUT_OF_RANGE;
    }

    return error;
}

/**********************************************************************
 * @details This function does the following:
 *          - Search for the task in the tasks array.
 *          - If found, remove the task from the tasks array.
 *          - Rearrange the tasks array.
 *          - Decrement the task counter.
 *          - If the task is not available, an error is returned.
 * @param[in] callback: Pointer to the task function.
 * @return  \c ERROR_t: Check the options in the global enum \ref ERROR_t.
 *********************************************************************/
ERROR_t cuteOS_TaskRemove(ERROR_t (* const callback)(void)) {
    ERROR_t error = ERROR_YES;
    u8_t i;

    /*!< Find the task in the task array */
    for(i = 0; i < cuteOS_task_counter; ++i) {
        if(tasks[i].callback == callback) {
            error |= ERROR_NO;   /*!< Task found */

            /*!< Rearrange the tasks array */
            for(; i < cuteOS_task_counter - 1; ++i) {
                tasks[i] = tasks[i + 1];
            }

            --cuteOS_task_counter;
            tasks[cuteOS_task_counter].callback = NULL;            

            error |= cuteOS_UpdateTicks();

            break;
        }
    }

    return error;
}

/**********************************************************************
 * @details Go to idle mode for some time = tickTimeInMs by disabling
 *          all interrupts and setting the sleep mode to Idle.
 * @note    The next clock tick will return the processor to the normal operating state.
 *********************************************************************/
void cuteOS_Start(void) {
    cuteOS_UpdateTicks();
	while(1) {
        PCON |= 0x01;   /*!< Enter idle mode to save power */
	}
}

ERROR_t cuteOS_GetTickTime(u8_t * const ptr_tick_time_ms){
    ERROR_t error = ERROR_NO;

    if(ptr_tick_time_ms != NULL) {
        if(0 == cuteOS_tick_time_ms) {
            cuteOS_tick_time_ms = MAX_TICK_TIME_MS;
        }

        *ptr_tick_time_ms = cuteOS_tick_time_ms;
    } else {
        error |= ERROR_NULL_POINTER;
    }

    return error;
}

/**********************************************************************
 * @details Initialize the Cute OS using Timer 2 overflow:
 *          - Timer mode
 *          - Tick time
 *          - Interrupt enable
 *          - Auto-reload mode
 *********************************************************************/
ERROR_t cuteOS_Init(void) {
    ERROR_t error = ERROR_NO;
    u16_t increments, reload_16;
    u8_t tick_time_ms;

    TR2 = 0;                                 /*!< Disable Timer 2 */

    /******************************************************************
     * Enable Timer 2 (16-bit timer) and configure it as a timer and automatically 
     * reloaded its value at overflow and 
     ******************************************************************/
    T2CON = 0x04;   /*!< Load Timer 2 control register  */

    /*!< Number of timer increments required (max 65536)    */
    /*!< increments = (Number of mSec) * (Number of Instructions per mSec)       */
    /*!< Number of mSec = tick_time_ms                                */
    /*!< Number of Instructions per mSec = (Number of Oscillations per mSec) * (Number of Instructions per Oscillation) */  
    /*!< Number of Oscillations per mSec = OSC_FREQ(MHz) / 1000 */   
    /*!< Number of Instructions per Oscillation = 1 / OSC_PER_INST */
    error |= cuteOS_GetTickTime(&tick_time_ms);
    increments = (u16_t) ( ((u32_t)tick_time_ms * (OSC_FREQ/1000)) / (u32_t)OSC_PER_INST );

    reload_16 = (u16_t)(65536UL - increments);
    RCAP2H = TH2 = (u8_t)(reload_16 / 256);   /*!< Load T2 and reload capt. reg. high bytes   */
    RCAP2L = TL2 = (u8_t)(reload_16 % 256);   /*!< Load T2 and reload capt. reg. low bytes    */

    ET2 = 1;                                /*!< Enable Timer 2 interrupt    */
    TR2 = 1;                                /*!< Start Timer 2    */
    EA = 1;                                 /*!< Globally enable interrupts   */

    return error;
}




/*--------------------------------------------------------------------*/
/*  PRIVATE FUNCTIONS DEFINITIONS                                     */
/*--------------------------------------------------------------------*/
/**********************************************************************
 * @brief   cuteOS_ISR() is invoked periodically by Timer 2 overflow
 * @note    See cuteOS_Init() for timing details.
 *********************************************************************/
static void cuteOS_ISR() interrupt INTERRUPT_Timer_2_Overflow {
    u8_t i;

    /*!< Must manually reset the timer 2 interrupt flag    */
    TF2 = 0;       

    /*!< Increment the tick time counter */
    ++cuteOS_tick_count;

    /*!< Check if the tick time counter has reached the required tick time */
    for(i = 0; i < cuteOS_task_counter; ++i) {
        if( (cuteOS_tick_count % tasks[i].ticks) == 0) {
            if(tasks[i].callback != NULL) {
                tasks[i].callback();
            }
        }
    }
        
    /*!< Reset the tick time counter */
    // cuteOS_tick_count = 0;
}

static ERROR_t cuteOS_UpdateTicks(void) {
    ERROR_t error = ERROR_NO;
    u32_t gcd_delay_ms;
    u8_t i;

    /*!< Find the maximum tick time among all the tasks */
    error |= cuteOS_GCD(&gcd_delay_ms);

    error |= cuteOS_SetTickTime(gcd_delay_ms);

    /*!< Update the number of ticks for each task */
    for(i = 0; i < cuteOS_task_counter; ++i) {
        tasks[i].ticks = tasks[i].delay_ms / gcd_delay_ms;
    }

    return error;
}

static ERROR_t cuteOS_GCD(u32_t *gcd) {
    ERROR_t error = ERROR_NO;
    u32_t remainder;
    u32_t y;
    u8_t i;

    *gcd = tasks[0].delay_ms;
    for(i = 1; i < cuteOS_task_counter; ++i) {
        y = tasks[i].delay_ms;
        while(y != 0) {
            remainder = *gcd % y;
            *gcd = y;
            y = remainder;
        }
    }

    /*!< Check if the tick time is greater than the maximum tick time */
    i = 2;
    while(*gcd > MAX_TICK_TIME_MS) {
        while( (*gcd % i) != 0) {
            ++i;
        }
        *gcd /= i;
    }

    return error;
}

/**********************************************************************
 * @details Set the value of the tick time in milliseconds. So, the
 *          timing of the tasks is determined by the frequency of Timer 2
 *          overflow. Overflow occurs every tickTimeInMs milliseconds.
 *********************************************************************/
static ERROR_t cuteOS_SetTickTime(const u8_t TICK_TIME_MS){
    ERROR_t error = ERROR_NO;
    
    if(TICK_TIME_MS <= MAX_TICK_TIME_MS) {
		if(TICK_TIME_MS <= 1) {
			cuteOS_tick_time_ms = 1;
		} else {
			cuteOS_tick_time_ms = TICK_TIME_MS;
		}
        error |= cuteOS_Init();
    } else {
        error |= ERROR_OUT_OF_RANGE;
    }

    return error;
}
