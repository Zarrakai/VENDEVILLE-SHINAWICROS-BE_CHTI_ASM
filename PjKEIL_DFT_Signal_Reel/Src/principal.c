

#include "DriverJeuLaser.h"
#include "DFT.h"
#include <stdlib.h>
#include <stdio.h>

extern int PeriodeSonMicroSec;
extern void CallbackSon(void);
extern void StartSon(void);

extern int decalageSon;
extern int LongueurSon;


extern short TabCos[64];
extern short TabSin[64];
extern short LeSignal[64];
void callback_systick();
short dma_buf[64] = {0};
int tabDFT[64] = {0};


int main(void)
{
// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();
	
	Systick_Period_ff(360000);	//72µs * 5ms * 1000
	Systick_Prio_IT(4, callback_systick);
	SysTick_On;
	SysTick_Enable_IT;
	
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );
	
	
	PWM_Init_ff(TIM3, 3, 720);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	Timer_1234_Init_ff(TIM4, 6554);
	Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);

//============================================================================	
	
	StartSon();
	
while	(1)
	{
	}
}

void callback_systick(){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	for (int k=0; k<63; k++)
		tabDFT[k] = DFT_ModuleAuCarre(dma_buf ,k);
	
	if(tabDFT[24] > 0xFFFFF && decalageSon >= LongueurSon)
	{
		StartSon();
	}
	
	int i = 0;
}