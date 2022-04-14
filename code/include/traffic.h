/***************************************************************************
 * @file    traffic.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Traffic Light System interfaces header file. See \ref traffic.c for more details.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef TRAFFIC_H
#define TRAFFIC_H

/*--------------------------------------------------------------------*/
/*                          TYPE DEFINITIONS                          */
/*--------------------------------------------------------------------*/
typedef enum {
    RED,
    RED_AMBER,
    GREEN,
    AMBER
}TRAFFIC_SEQUENCE_t;




/*--------------------------------------------------------------------*/
/*                          API FUNCTIONS                             */
/*--------------------------------------------------------------------*/

/***************************************************************************
 * @brief   Initialize the traffic light system to RED state.
 * @return \c ERROR_t: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t TRAFFIC_Init(void);

/***************************************************************************
 * @brief  De Initialize the traffic light system by turning off all the lights.
 * @return \c ERROR_t: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t TRAFFIC_DeInit(void);

ERROR_t TRAFFIC_Update(void);

/***************************************************************************
 * @brief   Set the traffic light color sequence to the given color sequence.
 * @param[in] color sequence: The color sequence to set:
 *          - \ref RED
 *          - \ref RED_AMBER
 *          - \ref GREEN
 *          - \ref AMBER
 *          Those colors are members of the global enumeration \ref TRAFFIC_SEQUENCE_t.
 * @return \c ERROR_t: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t TRAFFIC_SetColor(const TRAFFIC_SEQUENCE_t Copy_color);

/***************************************************************************
 * @brief   Get the traffic light color sequence.
 * @param[out] Copy_color: pointer to the variable to store the color sequence.
 *          Expected values:
 *          - \ref RED
 *          - \ref RED_AMBER
 *          - \ref GREEN
 *          - \ref AMBER
 *          Those colors are members of the global enumeration \ref TRAFFIC_SEQUENCE_t.
 * @return \c ERROR_t: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t TRAFFIC_GetColor(TRAFFIC_SEQUENCE_t * const Copy_color);


#endif          /* TRAFFIC_H */