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
 *    a. Data type
 *    b. Module masks
 *    c. Structure access macro
 * 3. Register access macros
 *    a. Whole register access macro
 *    b. Bitfields access macro
 * 
 * 
 * 
 */