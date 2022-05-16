

#include "DriverJeuLaser.h"
#include "DFT.h"

extern short TabCos[64];
extern short TabSin[64];
extern short LeSignal[64];


int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();

	int tabDFT[64] = {0};
	for (int k=0; k<63; k++)
		tabDFT[k] = DFT_ModuleAuCarre(LeSignal ,k);
	
	
	

//============================================================================	
	
	
while	(1)
	{
	}
}

