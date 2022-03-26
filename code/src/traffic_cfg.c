/***************************************************************************
 * @file    traffic_cfg.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Configurations of Traffic Light System.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "Main.h"
#include "traffic.h"
#include "traffic_cfg.h"


/*-------------------------------------------------------------------------*/
/*                YOU CAN CHANGE THE FOLLOWING PARAMETERS				   */
/*-------------------------------------------------------------------------*/
/***************************************************************************
 * @brief   Traffic Light System pins connections.
 ***************************************************************************/

TRAFFIC_CONFIGS_t TRAFFIC_Configs = {
    TRAFFIC_DURATION_RED,
    TRAFFIC_DURATION_AMBER,
    TRAFFIC_DURATION_GREEN,
    TRAFFIC_DURATION_RED_AMBER,
};
