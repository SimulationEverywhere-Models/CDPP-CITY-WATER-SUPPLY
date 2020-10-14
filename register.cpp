/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Laurentiu Checiu
*
*  EMAIL: mailto://lchec097@uottawa.ca;laurentiu.checiu@rogers.com
*
*  DATE: 10/10/2004
*
*******************************************************************/

#include "modeladm.h"
#include "mainsimu.h"
#include "reservoir.h"        	// class Reservoir
#include "pump.h"        		// class Pump
#include "well_pump.h"        		// class WellPump

void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Reservoir>(), "Reservoir" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Pump>(), "Pump" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<WellPump>(), "WellPump" ) ;
}

