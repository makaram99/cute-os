/******************************************************************************
 * @file    BIT_MATH.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Common bit manipulation operations
 * @version 1.0.0
 * @date    2021-07-31
 ******************************************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

/******************************************************************************
 * @brief Read state of a specific bit
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be read
 * @return state of the bit: 1 or 0
 * @par For example:
 *      GET_BIT(PORT_A, PIN0) will return 1 if bit 0 of PORT_A is HIGH or 0 if it is LOW
 ******************************************************************************/
#define GET_BIT(REGISTER, BIT)      ( 1 & ( (REGISTER) >> (BIT) ) )

/******************************************************************************
 * @brief Set state of a specific bit (set to 1)
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be set
 * @par For example:
 *      SET_BIT(PORT_A, PIN0) will set bit 0 of PORT_A to HIGH (1)
 ******************************************************************************/
#define SET_BIT(REGISTER, BIT)      ( (REGISTER) |= (1 << (BIT)) )

/******************************************************************************
 * @brief Clear state of a specific bit (set to 0)
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be cleared
 * @par For example:
 *      CLEAR_BIT(PORT_A, PIN0) will set bit 0 of PORT_A to LOW (0)
 ******************************************************************************/
#define CLR_BIT(REGISTER, BIT)      ( (REGISTER) &= ~(1 << (BIT)) )

/******************************************************************************
 * @brief Toggle state of a specific bit (set to 0)
 * @param[in] REGISTER: is the register includes the bit
 * @param[in] BIT: the required bit number to be toggled
 * @par For example:
 *      TOG_BIT(PORT_A, PIN0) will toggle bit 0 of PORT_A. So if it was HIGH, it will be LOW, and if it was LOW, it will be HIGH.
 ******************************************************************************/
#define TOG_BIT(REGISTER, BIT)      ( (REGISTER) ^= (1 << (BIT)) )

/******************************************************************************
 * @brief Check if state of a specific bit is set (state = 1)
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be set
 * @return 1 or 0: 1 if the bit is set, 0 if the bit is cleared
 * @par For example:
 *      BIT_IS_SET(PORT_A, PIN0) will return 1 if bit 0 of PORT_A is HIGH or 0 if it is LOW
 ******************************************************************************/
#define BIT_IS_SET(REGISTER,Bit) 	( (REGISTER) & (1 << (Bit)) )


/******************************************************************************
 * @brief Check if state of a specific bit is Cleared (state =  0)
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be set
 * @return 1 or 0: 1 if the bit is cleared, 0 if the bit is set
 * @par For example:
 *      BIT_IS_CLEAR(PORT_A, PIN0) will return 1 if bit 0 of PORT_A is LOW or 0 if it is HIGH
 ******************************************************************************/
#define BIT_IS_CLEAR(REGISTER,Bit)	( !( (REGISTER) & (1 << (Bit)) ) )

#define CONCAT_8BITS(b7, b6, b5, b4, b3, b2, b1, b0)  (0b##b7##b6##b5##b4##b3##b2##b1##b0)
#define CONCAT_7BITS(b6, b5, b4, b3, b2, b1, b0)      (0b##b6##b5##b4##b3##b2##b1##b0)
#define CONCAT_6BITS(b5, b4, b3, b2, b1, b0)          (0b##b5##b4##b3##b2##b1##b0)
#define CONCAT_5BITS(b4, b3, b2, b1, b0)              (0b##b4##b3##b2##b1##b0)
#define CONCAT_4BITS(b3, b2, b1, b0)                  (0b##b3##b2##b1##b0)
#define CONCAT_3BITS(b2, b1, b0)                      (0b##b2##b1##b0)
#define CONCAT_2BITS(b1, b0)                          (0b##b1##b0)

#endif			/* BIT_MATH_H	*/
