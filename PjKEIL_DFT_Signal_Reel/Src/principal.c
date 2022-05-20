

#include "DriverJeuLaser.h"
#include "DFT.h"
#include <stdlib.h>
#include <stdio.h>
#include "DFT.h"
#include "../GestionSon.h"

#define TRIGGER_FREQ 0x0000FFFF
#define NB_JOUEURS 6


void init_systick();
void init_ADC();
void init_pwm();
void callback_systick();





extern int PeriodeSonMicroSec;

extern int decalageSon;
extern int LongueurSon;

int indice = 0;

extern short TabCos[64];
extern short TabSin[64];
extern short LeSignal[64];


short dma_buf[64] = {0};
int tabDFT[64] = {0};
int scoreJoueurs[NB_JOUEURS] = {0};
int dftJoueurs[NB_JOUEURS] = {0};

int freqJoueurs[NB_JOUEURS] = {85, 90, 95, 100, 115, 120};


int main(void)
{
// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

	CLOCK_Configure();
	
	init_systick();
	init_ADC();
	init_pwm();
	
//============================================================================	
	
	
	while	(1)
	{
	}
}

void callback_systick(){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	// on récupere les DFT
	for (int k=0; k<63; k++)
		tabDFT[k] = DFT_ModuleAuCarre(dma_buf ,k);
	
	// pour chaque joueur, on vérifie sa fréquence de tir
	for(int i=0;i<NB_JOUEURS;i++)
	{
		indice = freqJoueurs[i]/5;
		dftJoueurs[i] = tabDFT[indice];
		
		// si un tir est détecté, on déclenche le son et on ajoute un point au joueur concerné
		if(tabDFT[indice] > TRIGGER_FREQ && decalageSon >= LongueurSon)
		{
			StartSon();
			scoreJoueurs[i] ++;
		}
		int i = 0;
	}
	
}


void init_systick()
{
	Systick_Period_ff(360000);	//72µs * 5ms * 1000
	Systick_Prio_IT(4, callback_systick);
	SysTick_On;
	SysTick_Enable_IT;
}

void init_ADC()
{
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );
}

void init_pwm()
{
	PWM_Init_ff(TIM3, 3, 720);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	Timer_1234_Init_ff(TIM4, 6554);
	Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);
}
