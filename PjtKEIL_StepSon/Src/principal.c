
#include "DriverJeuLaser.h"
extern int PeriodeSonMicroSec;
extern void CallbackSon(void);

int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
	CLOCK_Configure();
	

		
  

	//============================================================================	
	PWM_Init_ff(TIM3, 3, 720);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	Timer_1234_Init_ff(TIM4, PeriodeSonMicroSec);
	Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);

 	while	(1)
	{
		
	}
}

//Pur le passe bas avec resistance de 1k : 79nF donc prendre 82nF

