/***********************************************************************************
 *  @file     STD_TYPES.h
 *	@brief    Standard data types For AVR Microcontrollers
 *	@author   Mahmoud Karam (ma.karam272@gmail.com)
 *	@date	  2022-03-20
 *	@version  1.0.0
 ***********************************************************************************/
#ifndef STD_TYPES_H				
#define STD_TYPES_H

/* Signed integers	*/
typedef     signed long int   	        s32;		
typedef     signed short int 	        s16;		
typedef     signed char                 s8;
  
/* Unsigned integers	*/
typedef 	unsigned long int	        u32;
typedef 	unsigned short int          u16;
typedef 	unsigned char 		        u8;

/* Float numbers	*/        
typedef 	float 				        f32;
typedef 	double 				        f64;

/* Special types	*/        
 #undef __SIZE_TYPE__      /*!< This is a macro defined in the C standard library <stddef.h> for the size_t type */   
typedef 	u16   size_t;   /*!< size_t is an unsigned integer type of the result of the sizeof operator */

#undef HIGH
#undef LOW
typedef enum{
  LOW,
  HIGH,
  NORMAL,             /* Used for any normal state */
}STATE_t;

typedef enum{
    ACTIVE_LOW,       /*!< Active low means that the pin is pulled low when the pin is set to high */
    ACTIVE_HIGH,      /*!< Active high means that the pin is pulled high when the pin is set to low */
}ACTIVATION_STATUS_t;

/* Boolean type	*/
typedef enum{
    FALSE,
    TRUE
}BOOL_t;

typedef enum{
    ERROR_NO                = 0,            /*!< No error occured */
    ERROR_YES               = 0x1,          /*!< Error occured */
    ERROR_TIMEOUT           = 0x2,          /*!< Timeout occured */
    ERROR_NULL_POINTER      = 0x4,          /*!< Null pointer occured */
    ERROR_BUSY              = 0x8,          /*!< Busy state occured */
    ERROR_NOT_INITIALIZED   = 0x10,         /*!< Not initialized state occured */
    ERROR_ILLEGAL_PARAM     = 0x20,         /*!< Invalid input state occured */   
    ERROR_OUT_OF_RANGE      = 0x40,         /*!< Out of range state occured */ 
}ERROR_t;

/* Pointers	*/
#undef NULL 
#define NULL ((void *)0)  /*!< NULL pointer */

#undef NULL_BYTE
#define NULL_BYTE  ('\0')
 
 #endif	  /* STD_TYPES_H */
