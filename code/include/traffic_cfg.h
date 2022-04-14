/***************************************************************************
 * @file    traffic_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Traffic Light System interfaces header file. See \ref traffic.c for more details.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef TRAFFIC_CFG_H
#define TRAFFIC_CFG_H

/*-------------------------------------------------------------------------*/
/*                YOU CAN CHANGE THE FOLLOWING PARAMETERS				   */
/*-------------------------------------------------------------------------*/
typedef enum {
    TRAFFIC_DURATION_RED = 4,          /*!< Red light duration in seconds */
    TRAFFIC_DURATION_RED_AMBER = 2,     /*!< Red-Amber light duration in seconds */
    TRAFFIC_DURATION_GREEN = 4,        /*!< Green light duration in seconds */
    TRAFFIC_DURATION_AMBER = 2,         /*!< Amber light duration in seconds */
}TRAFFIC_SEQUENCE_DURATION_t;





/*-------------------------------------------------------------------------*/
/*                YOU MUST <<<NOT>>> CHANGE THE FOLLOWING PARAMETERS	   */
/*-------------------------------------------------------------------------*/
typedef struct {
    TRAFFIC_SEQUENCE_DURATION_t red_duration;
    TRAFFIC_SEQUENCE_DURATION_t red_amber_duration;
    TRAFFIC_SEQUENCE_DURATION_t green_duration;
    TRAFFIC_SEQUENCE_DURATION_t amber_duration;
}TRAFFIC_CONFIGS_t;

extern TRAFFIC_CONFIGS_t TRAFFIC_Configs;

#endif /* TRAFFIC_CFG_H */