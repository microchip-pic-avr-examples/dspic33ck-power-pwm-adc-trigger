/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.167.0
        Device            :  dsPIC33CK256MP506
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.4
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <xc.h>
#include "mcc_generated_files/system.h"
#include "main.h"

/* ********************************************************************* *
 * PWM based ADC Trigger Configuration Example
 * 
 * Description:
 * 
 *   This code example shows the basic configuration of PWM Generators triggering the   
 *   ADC input channels. It also demonstrates the Sampling Time Adjustment,Early Interrupt Generation  
 *   and Alternate working register with compiler optimization features to adjust the trigger response. 
 *     
 *   After the device has been programmed and the MCU starts up, PWM1H triggers  
 *   the Dedicated ADC Core 0. After around 277ns trigger response delay, the 
 *   ADC Core O ISR test pin indicator TP55 toggles.The trigger response delay is optimized 
 *   since the Early Interrupt Generator of ADC Core 0 is enabled.
 * 
 *   By pressing the on-board push button *USER* on the Digital Power
 *   Development Board, the PWM2H triggers the Dedicated ADC Core 1. After
 *   around 265ns trigger response delay, the ADC Core 1 ISR test pin indicator
 *   TP53 toggles see screen capture below. The trigger response delay is
 *   further reduced because aside from the Early Interrupt Generator is 
 *   enabled, the ADC Core 1 ISR used the context attribute of the compiler to
 *   associate the ISR with alternate register set.
 * 
 *   By pressing the on-board push button *USER* again, the PWM3H triggers the
 *   Shared ADC Core 6. After around 335ns the ADC Core 6  ISR test pin 
 *   indicator TP50 toggles see screen capture below. The configuration of
 *   Shared ADC is the same with the Dedicated ADC Core 1 except the Shared ADC
 *   Sampling Time is set to 8 TADCORE. Unlike the previous Dedicated ADC Cores,
 *   Shared ADC Core 6 does not have dedicated analog pin. This required 
 *   extending the sampling time to ensure that the ADC connects to analog pin 
 *   and properly sample the input signal before the conversion. However, this
 *   sample time adds trigger response delay.
 * 
 *   By pressing the on-board push button *USER* again, PWM2H and PWM3H will be disabled and 
 *   PWM1H will remain enabled triggering Dedicated ADC Core 0;
 * 
 * Please note:
 *   This code example can be run on dsPIC33CK as well as on dsPIC33CH
 *   devices. The PWM outputs of each device may be routed to different 
 *   test points. Please refer to the table below to quickly find the 
 *   right signal outputs. 
 * 
 * Recommended Use of this example:
 *   In this example Microchip Code Configurator (MCC) is used to set 
 *   up the device main and auxiliary clock as well as Timer1 used
 *   to create a deterministic execution of code within the main() 
 *   loop.The project folder 'common' contains generic PWM module 
 *   driver files,which are independent from MCC to better demonstrate 
 *   the PWM generator register configuration in more detail. 
 *   These driver files are providing an abstraction layer of the 
 *   user code, allowing quick migration of code across different 
 *   device peripherals and device families.
 * 
 *   To better understand these mechanisms please open file 'pwm.h' on
 *   code line 49 and change the following PWM generator index number to
 *   configure another PWM generator than #1,#2 and #3.
 *
 *     #define MOTHER_PWM_GENERATOR     1 
 *     #define CHILD_ONE_PWM_GENERATOR  2
 *     #define CHILD_TWO_PWM_GENERATOR  3
 * 
 *   Valid numbers are 1-8 for PG1 through PG8 on dsPIC33CK and 
 *   1-4 for PG1 through PG4 on dsPIC33CH. Due to hardware limitations
 *   not all PWM generator outputs may be accessible. Please refer to 
 *   the Test Pin table below to review if the selected PWM generator 
 *   outputs are available and accessible.
 * 
 * Hardware:
 *  - Digital Power Development Board (DM330029) 
 *  - dsPIC33CK Digital Power Plug-In Module (MA330048)
 *
 * Software:
 *  - MPLAB X IDE, v5.40
 *  - Microchip Code Configuration (MCC), v4.0.1
 *  - XC16 C-Compiler, v1.50
 *  - dsPIC33CK-MP Device File Pack v1.4.102
 * 
 * ********************************************************************* */  

/* ********************************************************************* *
 * Digital Power Development Board (DM330029) Test Pin Assignment:
 * *********************************************************************
 * 
 * Board Overview:
 * 
 *         ------------------------------------
 *        |        DIGITAL TEST POINTS         |
 *        |------------------------------------|
 *        |           __________           ----|
 *        |          |__________|         | USB|
 *        |         DP PIM SOCKET          ----|
 *        |                               -----|
 *        |                   RESET O    | ICSP|
 *        |      _   _                    -----|
 *        |   P2|O| |O|P1      USER O          |
 *         ------------------------------------ 
 * 
 * Signal     | Test-Pin              | Comment
 *            | dsPIC33CK | dsPIC33CH | 
 * ---------------------------------------------------------------------
 * PWM1H      | TP45      | TP35      | PWM Generator #1 output HIGH
 * PWM1L      | TP47      | TP38      | PWM Generator #1 output LOW
 *            |           |           | 
 * PWM2H      | TP42      | TP25      | PWM Generator #2 output HIGH
 * PWM2L      | TP40      | TP27  (2) | PWM Generator #2 output LOW
 *            |           |           | 
 * PWM3H      | TP37      | TP36      | PWM Generator #3 output HIGH
 * PWM3L      | TP41      | TP34      | PWM Generator #3 output LOW
 *            |           |           | 
 * PWM4H      | TP43      | TP46      | PWM Generator #4 output HIGH
 * PWM4L      | TP44      | TP48      | PWM Generator #4 output LOW
 *            |           |           | 
 * PWM5H      | TP35      | (n/a) (3) | PWM Generator #5 output HIGH
 * PWM5L      | TP38      | (n/a) (3) | PWM Generator #5 output LOW
 *            |           |           | 
 * PWM6H      | TP31      | (n/a) (3) | PWM Generator #6 output HIGH
 * PWM6L      | TP33      | (n/a) (3) | PWM Generator #6 output LOW
 *            |           |           | 
 * PWM7H      | TP25      | (n/a) (3) | PWM Generator #7 output HIGH
 * PWM7L      | TP27 (1)  | (n/a) (3) | PWM Generator #7 output LOW
 *            |           |           | 
 * PWM8H      | TP46      | (n/a) (3) | PWM Generator #8 output HIGH
 * PWM8L      | TP48      | (n/a) (3) | PWM Generator #8 output LOW
 * ---------------------------------------------------------------------
 *
 * (1): not available on dsPIC33CK DP PIM; Shared with on-board push button SW1
 * (2): not available on dsPIC33CH DP PIM Master Core; Shared with on-board push button SW1
 * (3): not available on dsPIC33CH DP PIM Master Core
 * 
 * ********************************************************************* */

// Digital Power Plug-In Module On-Board LED control
#define LED_INTERVAL    3000
#define PRESSED_INTERVAL 10

volatile uint16_t dbgled_cnt = 0;
volatile uint16_t press_cnt =  0;
volatile uint16_t debounce = 0;


/*
                         Main application
 */
int main(void)
{
    
    // Initialize the device
    SYSTEM_Initialize();
    
    // User PWM Initialization
    PWM_Initialize();
    // User ADC Initialization
    ADC_Initialize();
   
    // Initialize DP PIM and DP DevBoard function pins
    
     
    TP12_INIT_ANALOG;      //Set AN0 -  ADC Core 0 pin as input analog pin   
    TP11_INIT_ANALOG;      //Set AN1 -  ADC Core 1 pin as input analog pin
    TP20_INIT_ANALOG;      //Set AN6 -  ADC Core 6 pin as input analog pin
   
    TP55_InitAsOutput();   //Set ADC Core 0 Interrupt Indicator as output pin
    TP53_InitAsOutput();   //Set ADC Core 1 Interrupt Indicator as output pin
    TP50_InitAsOutput();   //Set ADC Core 6 Interrupt Indicator as output pin
    DBGPIN_InitAsOutput();
    DBGLED_InitAsOutput();
    SW_InitAsInput();
    
    
    _T1IF = 0; //Clear TMR1 flag
    
    
    
    /* main loop */
    while (1)
    {
        while(!_T1IF);  // Wait for Timer1 to expire
        _T1IF = 0;      // Reset interrupt flag bit
        DBGPIN_Clear(); // Clear device debug pin
        
        // Count main-loop execution cycles until on-board LED needs to be toggled
        if(++dbgled_cnt > LED_INTERVAL)
        {
            dbgled_cnt = 0;     // Reset LED toggle counter
            DBGLED_Toggle();    // Toggle on-board LED
        }
        
        // Check if on-board push button has been pressed
        if (SW_Read() == SW_PRESSED)
        {
            if (++debounce == PRESSED_INTERVAL)
            {    
                debounce  = 0;
                if (SW_Read() == SW_PRESSED) // Check again if on-board push button has been pressed
                {    
                    // Wait until switch is released
                    while(SW_Read() == SW_PRESSED); 
                    ++press_cnt;
            
                    if(press_cnt == 1)   
                    {
                         p33c_PwmGenerator_Enable(my_pg2);   // Enable PG2
                         p33c_PwmGenerator_Resume(my_pg2); 
               
                    }
                    if (press_cnt == 2 )
                    {
                         p33c_PwmGenerator_Enable(my_pg3);   // Enable PG3
                         p33c_PwmGenerator_Resume(my_pg3);
                         
              
                    }
                    if (press_cnt > 3)
                    {
                         p33c_PwmGenerator_Disable(my_pg2);  // Disable PG2
                         p33c_PwmGenerator_Disable(my_pg3);  // Disable PG3
                         press_cnt = 0; // Return count to 0
                        
                    }    
                }     
            }

            
            DBGPIN_Set(); // Set debug pin as oscilloscope trigger
          
        }
        
    }
   
    return(1);  // If this line is ever reached, something really bad happened....
}
/**
 End of File
*/

