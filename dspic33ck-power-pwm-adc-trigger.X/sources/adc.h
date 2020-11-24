/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   adc.h
 * Author: A14426
 * Comments: Header file of the user-configuration source file adc.c
 * Revision history: 0
 * 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "common/p33c_adc.h"
/* ADC MODULE BASE REGISTERS */

//ADC Core 0 
#define ADC_AN0_INPUT 0   // AN input pin number
#define ADC_AN0_INT_PRIORITY 5 // AN Interrupt Priority
#define ADC_AN0_INT_FLAG_CLEAR 0 // Clear Interrupt flag
#define ADC_AN0_INT_ENABLE 1     // Enable Interrupt


//ADC Core 1
#define ADC_AN1_INPUT 1   // AN input pin number
#define ADC_AN1_INT_PRIORITY 5 // AN Interrupt Priority
#define ADC_AN1_INT_FLAG_CLEAR 0 // Clear Interrupt flag
#define ADC_AN1_INT_ENABLE 1     // Enable Interrupt

//ADC Shared 6
#define ADC_AN6_INPUT 6   // AN input pin number
#define ADC_AN6_INT_PRIORITY 5 // AN Interrupt Priority
#define ADC_AN6_INT_FLAG_CLEAR 0 // Clear Interrupt flag
#define ADC_AN6_INT_ENABLE 1     // Enable Interrupt



extern volatile uint16_t ADC_Initialize(void);
extern volatile uint16_t ADC_Input_Initialize();
extern volatile uint16_t ADC_Enable(void);

extern volatile uint16_t dataAN0;
extern volatile uint16_t dataAN1;
extern volatile uint16_t dataAN6;

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_ADC_TRIAL_H */

