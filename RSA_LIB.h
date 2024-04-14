/**
 * \file RSA_LIB.h 
 * \brief Hardware library for ESP32-C6 RSA accelerator
 * \details ...
 * \author      MAVERICK_ST
 * \version     0.0.1
 * \date        26/03/2024
 * \copyright   MIT license
 * 
 * 
 * This header file declarates the data types, constants, macros, and the module structure
 * for controlling the memory mapped register for the RSA accelerator. The defined data 
 * structures follow a standard naming notation.
 * 
 * The naming notation is as follows:
 * 
 * MODULE STRUCTURE                 ==>   s + MODULEname + [MODULEnumber]
 * MMIO REGISTER                    ==>   r + MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * REGISTER BITFIELD or BIT         ==>   b + MODULEname + [MODULEnumber] + _ + BITFIELDname
 * BITFIELD CONTANT VALUEs          ==>   k + MODULEname + _ + BITFIELDname + _ + CONSTANTname
 * MODULE MASKs                     ==>   m + MODULEname + _ + MASKname
 * REGISTER TYPE                    ==>   __ + MODULEname + _ + REGISTERname + _t
 * STRUCTURE TYPE                   ==>   __ + MODULEname + _ + _t
 * 
 * Note: 
 * 
 * The structure of this file is as follows:
 * 
 * 1. Register structure definition
 *    a. Data type using bit union and structure
 *    b. Register masks to each bit and bitfield in the register
 *    c. Bitifield constant values masks
 * 2. Module structure definition
 *    a. Module data type using a structure
 *    c. Structure access macro to each module of the type selected
 * 3. Register access macros definition
 *    a. Whole register access macro
 *    b. Bitfields access macro
 * 
 * 
 */
#ifndef RSA_LIB_H_
#define RSA_LIB_H_

#include <stdint.h>

/*******************************************************************/
/****************Start Bits Fields Type Definition******************/
/*******************************************************************/

typedef union{ // Represents M’. (R/W)
	uint32_t WORD;
	struct{
		uint32_t MPRIME	:32;
	}BITS;
}__rsa_mprime_t; //  RSA_M_PRIME_REG (0x0800)

typedef union{ // Configures the RSA length. (R/W)
	uint32_t WORD;
	struct{
		uint32_t MODE	:7;
		uint32_t		:25;
	}BITS;
}__rsa_mode_t; // RSA_MODE_REG (0x0804)

typedef union{ // Configures whether or not to starts the modular exponentiation.
	uint32_t WORD;
	struct{
		uint32_t START_MODEXP	:1;
		uint32_t				:31;
	}BITS;
}__rsa_modexp_t; // RSA_SET_START_MODEXP_REG (0x080C)

// Constant definitions for the SET_START_MODEXP register
#define kRSA_START_MODEXP_OFF 0
#define kRSA_START_MODEXP_ON 1

typedef union{ // Configures whether or not to start the modular multiplication.
	uint32_t WORD;
	struct{
		uint32_t START_MODMULT	:1;
		uint32_t				:31;
	}BITS;
}__rsa_modmult_t; // RSA_SET_START_MODMULT_REG (0x0810)

// Constant definitions for the SET_START_MODMULT register
#define kRSA_START_MODMULT_OFF 0
#define kRSA_START_MODMULT_ON 1

typedef union{ // Configures whether or not to start the multiplication.
	uint32_t WORD;
	struct{
		uint32_t START_MULT	:1;
		uint32_t			:31;
	}BITS;
}__rsa_mult_t; // RSA_SET_START_MULT_REG (0x0814)

// Constant definitions for the SET_START_MULT register
#define kRSA_START_MULT_OFF 0
#define kRSA_START_MULT_ON 1

typedef union{ // Represents the RSA status.
	uint32_t WORD;
	struct{
		uint32_t Q_IDLE	:1;
		uint32_t		:31;
	}BITS;
}__rsa_status_t; // RSA_QUERY_IDLE_REG (0x0818)

typedef union{ // Configures the constant_time option.
	uint32_t WORD;
	struct{
		uint32_t kTIME	:1;
		uint32_t		:31;
	}BITS;
}__rsa_ktime_t; // RSA_CONSTANT_TIME_REG (0x0820)	

// Constant definitions for the CONSTANT_TIME register
#define kRSA_CONSTANT_TIME_ON 0		// Acceleration
#define kRSA_CONSTANT_TIME_OFF 1 	// No acceleration(default value)

typedef union{ // Configures the search option. This option should be used together with RSA_SEARCH_POS_REG. (R/W)
	uint32_t WORD;
	struct{
		uint32_t SEARCH_EN	:1;
		uint32_t			:31;
	}BITS;
}__rsa_searchen_t; // RSA_SEARCH_ENABLE_REG (0x0824)

// Constant definitions for the SEARCH_ENABLE register
#define kRSA_SEARCH_EN_OFF 0		// No acceleration (default value)
#define kRSA_SEARCH_EN_ON 1 		// Acceleration 

typedef union{ // Configures the starting address to start search
	uint32_t WORD;
	struct{
		uint32_t SEARCH_POS	:12;
		uint32_t			:20;
	}BITS;
}__rsa_searchpos_t; // RSA_SEARCH_POS_REG (0x0828)

typedef union{ // Represents whether or not the RSA memory completes initialization.
	uint32_t WORD;
	struct{
		uint32_t Q_CLEAN	:1;	
		uint32_t			:31;
	}BITS;
}__rsa_queryclean_t; // RSA_QUERY_CLEAN_REG (0x0808)	

typedef union{ // Write 1 to clear the RSA interrupt. (WT)
	uint32_t WORD;
	struct{
		uint32_t CLEAR_INT	:1;
		uint32_t			:31;
	}BITS;
}__rsa_intclr_t; // RSA_INT_CLR_REG (0x081C)

// Constant definitions for the INT_CLR register
#define kRSA_INT_CLR 1	// Clear interrupt

typedef union{ // Write 1 to enable the RSA interrupt. (R/W)
	uint32_t WORD;
	struct{
		uint32_t INT_EN	:1;
		uint32_t		:31;
	}BITS;
}__rsa_inten_t; // RSA_INT_ENA_REG (0x082C)

// Constant definitions for the INT_ENA register
#define kRSA_INT_EN 1		// Enable interrupt

typedef union{ // Write 1 to enable the RSA interrupt. (R/W)
	uint32_t WORD;
	struct{
		uint32_t DATE	:30;
		uint32_t		:2;
	}BITS;
}__rsa_date_t; // RSA_DATE_REG (0x0830)

/*******************************************************************/
/****************End Bits Fields Type Definition********************/
/*******************************************************************/


/*******************************************************************/
/****************Start Fields Structure Definition******************/
/*******************************************************************/

typedef struct{
	volatile __rsa_mprime_t			M_PRIME;			// Represents M’ 					0x0800 R/W
	volatile __rsa_mode_t 			MODE;				// Configures RSA length 			0x0804 R/W
	volatile __rsa_queryclean_t		QUERY_CLEAN;		// RSA initialization status 		0x0808 RO
	volatile __rsa_modexp_t			SET_START_MODEXP;	// Starts modular exponentiation 	0x080C WT
	volatile __rsa_modmult_t		SET_START_MODMULT;	// Starts modular multiplication 	0x0810 WT
	volatile __rsa_mult_t			SET_START_MULT;		// Starts multiplication 			0x0814 WT
	volatile __rsa_status_t			QUERY_IDLE;			// RSA status 						0x0818 RO
	volatile __rsa_intclr_t			INT_CLR;			// Clear RSA interrupt 				0x081C WT
	volatile __rsa_ktime_t			CONSTANT_TIME;		// Configures constant_time option 	0x0820 R/W
	volatile __rsa_searchen_t		SEARCH_ENABLE;		// Configures search option 		0x0824 R/W
	volatile __rsa_searchpos_t		SEARCH_POS;			// Configures the search position 	0x0828 R/W
	volatile __rsa_inten_t			INT_ENA;			// Enable RSA interrupt 			0x082C R/W
	volatile __rsa_date_t			DATE;				// Version control register 		0x0830 R/W
} __rsa__t;

// Masks to access RSA Accelerator Memory Blocks (0x6008_A000)
#define mRSA_M_MEM 0x6008A000 // From 0x6008A000 to 0x6008A17F (384kB) (R/W)
#define mRSA_Z_MEM 0x6008A200 // From 0x6008A200 to 0x6008A37F (384kB) (R/W)
#define mRSA_Y_MEM 0x6008A400 // From 0x6008A400 to 0x6008A57F (384kB) (R/W)
#define mRSA_X_MEM 0x6008A600 // From 0x6008A600 to 0x6008A77F (384kB) (R/W)

/*******************************************************************/
/****************End Fields Structure Definition********************/
/*******************************************************************/

/*******************************************************************/
/****************Start MACROs per Register**************************/
/*******************************************************************/

#define sRSA (*((__rsa__t *)0x6008A800))

// to RSA_M_PRIME_REG (0x0800)
#define rRSA_M_PRIME sRSA.M_PRIME.WORD

// to RSA_MODE_REG (0x0804)
#define rRSA_MODE sRSA.MODE.WORD
#define bRSA_MODE sRSA.MODE.BITS.MODE

// to RSA_QUERY_CLEAN_REG (0x0808)
#define rRSA_QUERY_CLEAN sRSA.QUERY_CLEAN.WORD
#define bRSA_QUERY_CLEAN sRSA.QUERY_CLEAN.BITS.Q_CLEAN

// to RSA_SET_START_MODEXP_REG (0x080C)
#define rRSA_SET_START_MODEXP sRSA.SET_START_MODEXP.WORD
#define bRSA_SET_START_MODEXP sRSA.SET_START_MODEXP.BITS.START_MODEXP

// to RSA_SET_START_MODMULT_REG (0x0810)
#define rRSA_SET_START_MODMULT sRSA.SET_START_MODMULT.WORD
#define bRSA_SET_START_MODMULT sRSA.SET_START_MODMULT.BITS.START_MODMULT

// to RSA_SET_START_MULT_REG (0x0814)
#define rRSA_SET_START_MULT sRSA.SET_START_MULT.WORD
#define bRSA_SET_START_MULT sRSA.SET_START_MULT.BITS.START_MULT

// to RSA_QUERY_IDLE_REG (0x0818)
#define rRSA_QUERY_IDLE sRSA.QUERY_IDLE.WORD
#define bRSA_QUERY_IDLE sRSA.QUERY_IDLE.BITS.Q_IDLE

// to RSA_INT_CLR_REG (0x081C)
#define rRSA_INT_CLR sRSA.INT_CLR.WORD
#define bRSA_INT_CLR sRSA.INT_CLR.BITS.CLEAR_INT

// to RSA_CONSTANT_TIME_REG (0x0820)
#define rRSA_CONSTANT_TIME sRSA.CONSTANT_TIME.WORD
#define bRSA_CONSTANT_TIME sRSA.CONSTANT_TIME.BITS.kTIME

// to RSA_SEARCH_ENABLE_REG (0x0824)
#define rRSA_SEARCH_ENABLE sRSA.SEARCH_ENABLE.WORD
#define bRSA_SEARCH_ENABLE sRSA.SEARCH_ENABLE.BITS.SEARCH_EN

// to RSA_SEARCH_POS_REG (0x0828)
#define rRSA_SEARCH_POS sRSA.SEARCH_POS.WORD
#define bRSA_SEARCH_POS sRSA.SEARCH_POS.BITS.SEARCH_POS

// to RSA_INT_ENA_REG (0x082C)
#define rRSA_INT_ENA sRSA.INT_ENA.WORD
#define bRSA_INT_ENA sRSA.INT_ENA.BITS.INT_EN

// to RSA_DATE_REG (0x0830)
#define rRSA_DATE sRSA.DATE.WORD
#define bRSA_DATE sRSA.DATE.BITS.DATE

/*******************************************************************/
/****************End MACROs per Register****************************/
/*******************************************************************/


#endif /* RSA_LIB_H_ */