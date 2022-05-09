

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

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();


	int res = DFT_ModuleAuCarre(TabSin,1);
	

//============================================================================	
	
	
while	(1)
	{
	}
}

