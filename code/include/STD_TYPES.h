/***********************************************************************************
 *  @file     STD_TYPES.h
 *	@brief    Standard data types For 8051 Microcontrollers
 *	@author   Mahmoud Karam (ma.karam272@gmail.com)
 *	@date	  2022-03-20
 *	@version  1.0.0
 ***********************************************************************************/
#ifndef STD_TYPES_H				
#define STD_TYPES_H

/* Signed integers	*/
typedef     signed long int   	        s32_t;		
typedef     signed short int 	        s16_t;		
typedef     signed char                 s8_t;
  
/* Unsigned integers	*/
typedef 	unsigned long int	        u32_t;
typedef 	unsigned short int          u16_t;
typedef 	unsigned char 		        u8_t;

/* Float numbers	*/        
typedef 	float 				        f32;
typedef 	double 				        f64;

/* Special types	*/        
 #undef __SIZE_TYPE__       /*!< This macro is defined in <stddef.h> for the size_t type */   
typedef 	u16_t   size_t;  

#undef HIGH
#undef LOW
typedef     u8_t      STATE_t;
#define     LOW         ((STATE_t)0)
#define     HIGH        ((STATE_t)1)
#define     NORMAL      ((STATE_t)2)                /*!< Used for any normal state */

typedef     u8_t      ACTIVATION_STATUS_t;
#define     ACTIVE_LOW              ((ACTIVATION_STATUS_t)0)    /*!< The pin is high when it is pulled low  */
#define     ACTIVE_HIGH             ((ACTIVATION_STATUS_t)1)    /*!< The pin is low when it is pulled high  */

/* Boolean type	*/
typedef     u8_t      BOOL_t;
#define     FALSE       ((BOOL_t)0)
#define     TRUE        ((BOOL_t)1)

typedef     u8_t      ERROR_t;
#define     ERROR_NO                ( (ERROR_t)0     )       /*!< No error occured */
#define     ERROR_YES               ( (ERROR_t)0x1   )       /*!< Error occured */
#define     ERROR_TIMEOUT           ( (ERROR_t)0x2   )       /*!< Timeout occured */
#define     ERROR_NULL_POINTER      ( (ERROR_t)0x4   )       /*!< Null pointer occured */
#define     ERROR_BUSY              ( (ERROR_t)0x8   )       /*!< Busy state occured */
#define     ERROR_NOT_INITIALIZED   ( (ERROR_t)0x10  )       /*!< Not initialized state occured */
#define     ERROR_ILLEGAL_PARAM     ( (ERROR_t)0x20  )       /*!< Invalid input state occured */   
#define     ERROR_OUT_OF_RANGE      ( (ERROR_t)0x40  )       /*!< Out of range state occured */ 

/* Pointers	*/
#undef NULL 
#define NULL ((void *)0)  /*!< NULL pointer */

#undef NULL_BYTE
#define NULL_BYTE  ('\0')
 
 #endif	  /* STD_TYPES_H */
