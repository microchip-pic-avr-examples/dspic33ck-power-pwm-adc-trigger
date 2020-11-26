# dspic33ck-power-pwm-adc-trigger, release v1.0.0
### Release Highlights
<b><u> This is the initial release demonstrating  the basic cofiguration of ADC  triggered by High Resolution PWM Generator in dsPIC33C family of devices. It also highlights the Early Interrupt Generation, Alternate Working register with Compiler attributes and Sampling Time adjustment optimization feature to adjust the trigger response time.



### Features Added\Updated
In this intial version the on-board LED of the dsPIC33CK Digital Power Plug-In Module is toggled with a interval üperiod of 300 ms, when the controller is running at maximum speed of 100 MIPS.After starts up, PWM1H triggers the Dedicated ADC Core 0. After around 277ns trigger response delay, the ADC Core O ISR test pin indicator TP55 toggles. The trigger response delay is optimized since the Early Interrupt Generator of ADC Core 0 is enabled.  By pressing the on-board push button *USER* on the Digital Power Development Board, the PWM2H triggers the Dedicated ADC Core 1. After around 265ns trigger response delay, the ADC Core 1 ISR test pin indicator TP53 toggles. The trigger response delay is further reduced because aside from the Early Interrupt Generator is enabled, the ADC Core 1 ISR used the context attribute of the compiler to associate the ISR with alternate register set.  By pressing the on-board push button *USER* again, the PWM3H triggers the Shared ADC Core 6. After around 335ns the ADC Core 6  ISR test pin indicator TP50 toggles. The configuration of Shared ADC is the same with the Dedicated ADC Core 1 except the Shared ADC Sampling Time is set to 8 TADCORE. Unlike the previous Dedicated ADC Cores, Shared ADC Core 6 does not have dedicated analog pin. This required extending the sampling time to ensure that the ADC connects to analog pin and properly sample the input signal before the conversion. However, this sample time adds trigger response delay.



