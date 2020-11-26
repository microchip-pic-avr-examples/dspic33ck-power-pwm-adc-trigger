
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
 * File: adc.c 
 * Author: A14426
 * Comments:  source file of adc.h header file
 * Revision history: 0
 * 
 */



#include <xc.h>
#include "adc.h"
#include "common/p33c_adc.h"
#include "config/hal.h"


// added another struct to configure individual adc channel
typedef struct {
     volatile HSADC_ADCANCFG_t adc0;
     volatile HSADC_ADCANCFG_t adc1;
     volatile HSADC_ADCANCFG_t adc6;
}HSADC_INPUT_SETTING_t;

volatile uint16_t dataAN0;
volatile uint16_t dataAN1;
volatile uint16_t dataAN6;

 /* *****************************************************************************************************
 * Summary:
 * Initializes the ADC Module with default settings for maximum performance
 *
 * Parameters: 
 *  (none)
 *
 * Description:
 * 
 * The ADC initialization covers basic configurations like data format, clock sources and dividers
 * as well as specific configurations for ADC cores. These settings are general, basic settings
 * and not related to specific analog inputs. The standard configuration set here sets up the 
 * ADC module and ADC cores for maximum performance.
 * 
 * The basic configuration of the ADC module is initialized here while the individual ADC inputs 
 * are set by function ADC_Input_Initialize().
 * 
 * *****************************************************************************************************/

volatile uint16_t ADC_Initialize(void) {

    volatile uint16_t fres = 1;
    volatile HSADC_ADMODCFG_t admod_cfg;
    
    // Initialize ADC Converter
    // ========================
    // Load ADC configuration
    admod_cfg.config.adon = ADCON1_ADON_DISABLED;
    admod_cfg.config.adsidl = ADCON1_ADSIDL_RUN;
    admod_cfg.config.form = ADCON1_FORM_INTEGER;
    admod_cfg.config.ptgen = ADCON2_PTGEN_DISABLED;
    admod_cfg.config.eien = ADCON2_EIEN_ENABLED;
    admod_cfg.config.warmtime = ADCON5H_WARMTIME_CLK_32768;
    
    admod_cfg.refcfg.refsel = ADCON3_REFSEL_AVDD_AVSS;
    admod_cfg.refcfg.refcie = ADCON2_REFCIE_DISABLED;
    admod_cfg.refcfg.refercie = ADCON2_REFERCIE_DISABLED;
    
    admod_cfg.swtrig.cnvchsel = ADCON3_CNVCHSEL_AN0;
    admod_cfg.swtrig.suspcie = ADCON3_SUSPCIE_DISABLED;
    admod_cfg.swtrig.suspend = ADCON3_SUSPEND_RUN;

    admod_cfg.cores.clksel = ADCON3_CLKSEL_AFVCODIV;
    admod_cfg.cores.clkdiv = ADCON3_CLKDIV_1;

    admod_cfg.cores.shared_core.adcs = ADCORE_ADCS_DEFAULT;
    admod_cfg.cores.shared_core.eisel = ADCORE_EISEL_8TAD;
    admod_cfg.cores.shared_core.res = ADCORE_RES_12BIT;
    admod_cfg.cores.shared_core.samc = ADCORE_SAMC_0009;
    
#if defined (__MA330048_dsPIC33CK_DPPIM__)
    admod_cfg.cores.core0.adcs = ADCORE_ADCS_DEFAULT;
    admod_cfg.cores.core0.eisel = ADCORE_EISEL_8TAD;
    admod_cfg.cores.core0.res = ADCORE_RES_12BIT;
    admod_cfg.cores.core0.samc = ADCORE_SAMC_0002;
    admod_cfg.cores.core0.samc_en = ADCON4_SAMCxEN_DISABLED;
    

    admod_cfg.cores.core1.adcs = ADCORE_ADCS_DEFAULT;
    admod_cfg.cores.core1.eisel = ADCORE_EISEL_8TAD;
    admod_cfg.cores.core1.res = ADCORE_RES_12BIT;
    admod_cfg.cores.core1.samc = ADCORE_SAMC_0002;
    admod_cfg.cores.core1.samc_en = ADCON4_SAMCxEN_DISABLED;
#endif

    // Initialize ADC module base registers
    fres &= ADC_Module_Initialize(admod_cfg);  // Write ADC module configuration to registers

    ADC_Input_Initialize();
    
    ADC_Enable();   
    return(fres);
}

/*!ADC_Input_Initialize()
 * *****************************************************************************************************
 * Summary:
 * Initializes the analog inputs for the required input signals
 *
 * Parameters: 
 *  
 *
 * Description:
 * The ADC_Input_Initialize covers the initialization of ADC core 0, ADC core 1, ADC core 6 input setting.
 * ADC core 0 is triggered by PG1, ADC core 1 is triggered by PG2, and ADC core 6 is triggered by PG3
 * 
 * *****************************************************************************************************/
 
volatile uint16_t ADC_Input_Initialize() {
    
   volatile uint16_t fres = 1;
   
   volatile HSADC_INPUT_SETTING_t ad0_input_setting;
   volatile HSADC_INPUT_SETTING_t ad1_input_setting;
   volatile HSADC_INPUT_SETTING_t ad6_input_setting;
   
    
   // AN 0 Input Configuration
   ad0_input_setting.adc0.config.early_interrupt_enable = ADEIE_ANx_ENABLED;
   ad0_input_setting.adc0.config.interrupt_enable = ADIE_ANx_ENABLED;
   ad0_input_setting.adc0.config.trigger_mode = ADLVLTRG_ANx_EDGE;
   ad0_input_setting.adc0.config.trigger_source = ADTRIGx_TRGSRC_PWM1_TRIG1;
   ad0_input_setting.adc0.config.data_mode = ANx_DATA_UNSIGNED;
   ad0_input_setting.adc0.config.input_mode = ANx_SINGLE_ENDED;
   ad0_input_setting.adc0.ad_input = ADC_AN0_INPUT;
   ad0_input_setting.adc0.config.core_index = ADC_CORE_ANA0;
   ad0_input_setting.adc0.config.core_assigmnment = ANx_CORE_ASSIGNMENT_DEDICATED;
   
   // AN 1 Input Configuration
   ad1_input_setting.adc1.config.early_interrupt_enable = ADEIE_ANx_ENABLED;
   ad1_input_setting.adc1.config.interrupt_enable = ADIE_ANx_ENABLED;
   ad1_input_setting.adc1.config.trigger_mode = ADLVLTRG_ANx_EDGE;
   ad1_input_setting.adc1.config.trigger_source = ADTRIGx_TRGSRC_PWM2_TRIG1;
   ad1_input_setting.adc1.config.data_mode = ANx_DATA_UNSIGNED;
   ad1_input_setting.adc1.config.input_mode = ANx_SINGLE_ENDED;
   ad1_input_setting.adc1.ad_input = ADC_AN1_INPUT;
   ad1_input_setting.adc1.config.core_index = ADC_CORE_ANA1;
   ad1_input_setting.adc1.config.core_assigmnment = ANx_CORE_ASSIGNMENT_DEDICATED;
    
   
   // AN 6 Input configuration
   ad6_input_setting.adc6.config.early_interrupt_enable = ADEIE_ANx_ENABLED;
   ad6_input_setting.adc6.config.interrupt_enable = ADIE_ANx_ENABLED;
   ad6_input_setting.adc6.config.trigger_mode = ADLVLTRG_ANx_EDGE;
   ad6_input_setting.adc6.config.trigger_source = ADTRIGx_TRGSRC_PWM3_TRIG1;
   ad6_input_setting.adc6.config.data_mode = ANx_DATA_UNSIGNED;
   ad6_input_setting.adc6.config.input_mode = ANx_SINGLE_ENDED;
   ad6_input_setting.adc6.ad_input = ADC_AN6_INPUT;
   ad6_input_setting.adc6.config.core_index = ADC_CORE_AN6;
   ad6_input_setting.adc6.config.core_assigmnment = ANx_CORE_ASSIGNMENT_SHARED;
   
  

    fres &= ADC_ADInput_Initialize(ad0_input_setting.adc0);
    fres &= ADC_ADInput_Initialize(ad1_input_setting.adc1);
    fres &= ADC_ADInput_Initialize(ad6_input_setting.adc6);
    // Return Success/Failure
    return(fres);
}

/*ADC_enable()
 * *****************************************************************************************************
 * Summary:
 * Enables the ADC module, starts the ADC cores analog inputs for the four required input signals
 *
 * Parameters: 
 *  (none)
 *
 * Description:
 * This function enables the ADC module, powers-up and enables the ADC cores used and waits 
 * until all functions are acknowledged by the respective READY bits.
 * 
 * *****************************************************************************************************/

volatile uint16_t ADC_Enable(void) {
    
    volatile uint16_t fres = 1;
    
    //Set ADC Channel Interrupt and Interrupt Priority
    
    _ADCAN0IP = ADC_AN0_INT_PRIORITY;    // Interrupt Priority Level 5
    _ADCAN0IF = ADC_AN0_INT_FLAG_CLEAR;  // Reset Interrupt Flag Bit
    _ADCAN0IE = ADC_AN0_INT_ENABLE;      // Enable ADCAN0 Interrupt
   
    _ADCAN1IP = ADC_AN1_INT_PRIORITY;    // Interrupt Priority Level 5
    _ADCAN1IF = ADC_AN1_INT_FLAG_CLEAR;  // Reset Interrupt Flag Bit
    _ADCAN1IE = ADC_AN1_INT_ENABLE;      // Enable ADCAN1 Interrupt
   
    
   _ADCAN6IP = ADC_AN6_INT_PRIORITY;    // Interrupt Priority Level 5
   _ADCAN6IF = ADC_AN6_INT_FLAG_CLEAR;  // Reset Interrupt Flag Bit
   _ADCAN6IE = ADC_AN6_INT_ENABLE;     // Enable ADCAN6 Interrupt

    fres &= ADC_Module_Enable();
    fres &= ADC_Core_CheckReady();
    
    return(fres);
}

/* ADC AN0 ISR */
void __attribute__((interrupt,no_auto_psv)) _ADCAN0Interrupt(void)    
{
 TP55_Set();
 
dataAN0 = ADCBUF0; // read conversion result 
_ADCAN0IF = 0;     // clear interrupt flag

TP55_Clear();
}

/* ADC AN1 ISR */
void __attribute__((interrupt,context,no_auto_psv)) _ADCAN1Interrupt(void) // The context attribute associates ISR with alternate register set
{
 TP53_Set();
 
dataAN1 = ADCBUF1; // read conversion result
_ADCAN1IF = 0;     // clear interrupt flag

 TP53_Clear();
}

void __attribute__((interrupt,context, no_auto_psv)) _ADCAN6Interrupt(void)
{
TP50_Set();

dataAN6 = ADCBUF6; // read conversion result

_ADCAN6IF = 0; // clear interrupt flag

TP50_Clear();
}
