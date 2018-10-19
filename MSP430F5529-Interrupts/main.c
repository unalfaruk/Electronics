#include "io430.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  TA0CCTL0 = CCIE; // CCR0 interrupt enabled
  TA0CTL = TASSEL_1 + MC_1 + ID_3; // ACLK/8, upmode
  TA0CCR0 =  4096; // 1Hz
  
  TA1CCTL0 = CCIE; // CCR0 interrupt enabled
  TA1CTL = TASSEL_1 + MC_1 + ID_3; // ACLK/8, upmode
  TA1CCR0 =  2048; // 2Hz 
  
  P4OUT &= 0x00; // Shut down everything
  P4DIR &= 0x00;       
  P4DIR |= BIT7;
  
  P1OUT &= 0x00; // Shut down everything
  P1DIR &= 0x00;               
  P1DIR |= BIT0 + BIT4; // P1.0 and P1.4 pins output the rest are input 
  
  P1REN |= BIT1; // Enable internal pull-up/down resistors
  P1OUT |= BIT1; //Select pull-up mode for P1.1
  P1IE |= BIT1; // P1.1 interrupt enabled
  P1IES |= BIT1; // P1.1 Hi/lo edge
  P1IFG &= ~BIT1; // P1.1 IFG cleared
  
  __bis_SR_register(CPUOFF + GIE); // Enter LPM0 w/ interrupt
  
  while(1) //Loop forever, we work with interrupts!
  {}
}

// Timer T0A0 interrupt service routine 
#pragma vector=TIMER0_A0_VECTOR 
__interrupt void Timer_A (void) 
{   
   P1OUT ^= BIT0; // Toggle P1.0 
}

// Timer T1A0 interrupt service routine 
#pragma vector=TIMER1_A0_VECTOR 
__interrupt void Timer_B (void) 
{   
   P4OUT ^= BIT7; // Toggle P4.7
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{    
   P1OUT ^= BIT4; // Toggle P1.5
   P1IFG &= ~BIT1; // P1.1 IFG cleared 
}
