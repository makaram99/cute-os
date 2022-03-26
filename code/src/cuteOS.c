/**********************************************************************
 * @file    cuteOS.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Main file for Cute Embedded Operating System (cuteOS) for 8051.
 * @details cuteOS schedules the tasks in a cooperative manner.
 *          It invokes te scheduler (\ref cuteOS_ISR()) periodically by Timer 
 *          overflow. So, the timing of the tasks is determined by the 
 * 			frequency of Timer overflow defined by the variable \ref cuteOS_TICK_TIME.
 * @note    cuteOS uses the timer2 for scheduling.
 * @version 1.0.0
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
static u8 cuteOS_TickTimeMs = 50; 

/*!< Number of ticks, which is incremented by 1 at each Timer 2 overflow. */
static u16 cuteOS_TickCount = 0;

/**********************************************************************
 * @brief   Maximum number of tasks the OS can handle.
 *********************************************************************/
#define MAX_TASKS_NUM   10   

/*!< Number of tasks created by the user. */
static u8 cuteOS_TaskCounter = 0;         /*!< Counter for the number of tasks created */

/*!< Task Information Structure. */
typedef struct {
    ERROR_t (*callback)(void);    /*!< Pointer to the task function */
    u16 ticks;    /*!< Number of ticks after which the task will run */
    u8  id;       /*!< Task ID */    
}cuteOS_TASK_t;

/*!< Tasks array containing tasks information. */
cuteOS_TASK_t tasks[MAX_TASKS_NUM] = {0};







/*--------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS                         */
/*--------------------------------------------------------------------*/
/**********************************************************************
 * @brief   cuteOS_ISR() is invoked periodically by Timer 2 overflow
 * @note    See cuteOS_Init() for timing details.
 *********************************************************************/
static void cuteOS_ISR() interrupt INTERRUPT_Timer_2_Overflow {
    u8 i = 0;

    /*!< Must manually reset the timer 2 interrupt flag    */
    TF2 = 0;       

    /*!< Increment the tick time counter */
    ++cuteOS_TickCount;

    /*!< Check if the tick time counter has reached the required tick time */
    for(i = 0; i < cuteOS_TaskCounter; ++i) {
        if( (cuteOS_TickCount % tasks[i].ticks) == 0) {
            /*!< Reset the tick time counter */
            // cuteOS_TickCount = 0;

            /*!< Call the Cute OS callback function */
            if(tasks[i].callback != NULL) {
                tasks[i].callback();
            }
        }
    }
}

/**********************************************************************
 * @brief   The OS enters 'idle mode' between clock ticks to save power.
 * @details Go to idle mode for some time = tickTimeInMs by disabling
 *          all interrupts and setting the sleep mode to Idle.
 * @note    The next clock tick will return the processor to the normal operating state.
 *********************************************************************/
static void cuteOS_Sleep(void) {
    /*!< Enter idle mode to save power */
    PCON |= 0x01;
}


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
ERROR_t cuteOS_TaskCreate(ERROR_t (* const callback)(void), const u16 TICK_MS) {
    ERROR_t error = ERROR_NO;

    ++cuteOS_TaskCounter;

    if(cuteOS_TaskCounter > MAX_TASKS_NUM) {
        error = ERROR_OUT_OF_RANGE;
    } else {
        tasks[cuteOS_TaskCounter - 1].id = cuteOS_TaskCounter - 1;
        tasks[cuteOS_TaskCounter - 1].ticks = TICK_MS / cuteOS_TickTimeMs;
        tasks[cuteOS_TaskCounter - 1].callback = callback;
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
 * @return  ERROR Status: Check the options in the global enum \ref ERROR_t.
 *********************************************************************/
ERROR_t cuteOS_TaskRemove(ERROR_t (* const callback)(void)) {
    ERROR_t error = ERROR_YES;
    u8 i = 0;

    /*!< Find the task in the task array */
    for(i = 0; i < cuteOS_TaskCounter; ++i) {
        if(tasks[i].callback == callback) {
            error = ERROR_NO;   /*!< Task found */

            for(; i < cuteOS_TaskCounter - 1; ++i) {
                tasks[i] = tasks[i + 1];
            }
            /*!< Assign NULL pointer to the last task to avoid calling it */
            tasks[cuteOS_TaskCounter - 1].callback = NULL;
            
            /*!< Decrement the number of tasks */
            --cuteOS_TaskCounter;
            break;
        }
    }

    return error;
}

/**********************************************************************
 * @brief   Start the Cute Embedded Operating System (cuteOS)
 *********************************************************************/
void cuteOS_Start(void) {
	/*!< Super loop */
	while(1) {
		cuteOS_Sleep();			/*!< Enter idle mode to save power */
	}
}

/**********************************************************************
 * @details Set the value of the tick time in milliseconds. So, the
 *          timing of the tasks is determined by the frequency of Timer 2
 *          overflow. Overflow occurs every tickTimeInMs milliseconds.
 *********************************************************************/
ERROR_t cuteOS_SetTickTime(const u8 TICK_MS){
    ERROR_t error = ERROR_NO;

    cuteOS_TickTimeMs = TICK_MS;
    
    if(cuteOS_TickTimeMs > MAX_TICK_TIME_MS) {
        error = ERROR_OUT_OF_RANGE;
    } else {
        /*!< Set the value of the tick time in ms */
        cuteOS_Init();
    }

    return ERROR_NO;
}

/**********************************************************************
 * @brief Get the value of the tick time in milliseconds.
 *********************************************************************/
ERROR_t cuteOS_GetTickTime(u8 * const tickTimeInMsPtr){
    ERROR_t error = ERROR_NO;

    if(tickTimeInMsPtr != NULL) {
        *tickTimeInMsPtr = cuteOS_TickTimeMs;
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
    u32 Inc;
    u16 Reload_16;
    u8 Reload_08H, Reload_08L;

    TR2 = 0;                                 /*!< Disable Timer 2 */

    /******************************************************************
     * Enable Timer 2 (16-bit timer) and configure it as a timer and automatically 
     * reloaded its value at overflow and 
     ******************************************************************/
    T2CON = 0x04;   /*!< Load Timer 2 control register  */

    /*!< Number of timer increments required (max 65536)    */
    /*!< Inc = (Number of mSec) * (Number of Instructions per mSec)       */
    /*!< Number of mSec = cuteOS_TickTimeMs                                */
    /*!< Number of Instructions per mSec = (Number of Oscillations per mSec) * (Number of Instructions per Oscillation) */  
    /*!< Number of Oscillations per mSec = OSC_FREQ(MHz) / 1000 */   
    /*!< Number of Instructions per Oscillation = 1 / OSC_PER_INST */    
    Inc = ((u32)cuteOS_TickTimeMs * (OSC_FREQ/1000)) / (u32)OSC_PER_INST;

    /*!< 16-bit reload value    */
    Reload_16 = (u16) (65536UL - Inc);

    /*!< 8-bit reload values (High & Low)   */
    Reload_08H = (u8)(Reload_16 / 256);  /*!< High byte    */
    Reload_08L = (u8)(Reload_16 % 256);  /*!< Low byte     */

    // Used for manually checking timing (in simulator)
    //P2 = Reload_08H;
    //P3 = Reload_08L;
    RCAP2H = TH2 = Reload_08H;              /*!< Load T2 and reload capt. reg. high bytes   */
    RCAP2L = TL2 = Reload_08L;              /*!< Load T2 and reload capt. reg. low bytes    */

    ET2 = 1;                                /*!< Enable Timer 2 interrupt    */
    TR2 = 1;                                /*!< Start Timer 2    */
    EA = 1;                                 /*!< Globally enable interrupts   */

    return error;
}

