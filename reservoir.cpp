/*******************************************************************
*
*  DESCRIPTION: Atomic Model Reservoir
*
*  AUTHOR: Laurentiu Checiu
*
*  EMAIL: mailto://lchec097@uottawa.ca;laurentiu.checiu@rogers.com
*
*  DATE: 10/10/2004
*
*******************************************************************/

/** include files **/
#include "reservoir.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Reservoir
* Description:
********************************************************************/
Reservoir::Reservoir( const string &name )
: Atomic( name )
, q_in( addInputPort( "q_in" ) )
, qp_in( addInputPort( "qp_in" ) )
, level_out( addOutputPort( "level_out" ) )
, low_level_out( addOutputPort( "low_level_out" ) )
, volume(1000.0)
, debit_supp(0.0)
, debit_pump(0.0)
, level(1.0)
, alarm_level(0.75)
, low_level(0)
, preparationTime(0,0,1,0)
, initialTime_supp(0,0,0,0)
, initialTime_pump(0,0,0,0)
{
		string al_niv( MainSimulator::Instance().getParameter( description(), "alarm_level" )  ) ;
		if (al_niv != "")
			alarm_level = str2float( al_niv );
}

/*******************************************************************
* Function Name: initFunction
* Description:
********************************************************************/
Model &Reservoir::initFunction()
{
	this->passivate() ;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Reservoir::externalFunction( const ExternalMessage &msg )
{
	Time time_supp(0,0,0,0);
	Time time_pump(0,0,0,0);
	Time duration(0,0,0,0);

	unsigned long secunde = 0;

	if ( msg.port() == q_in )									// flow from wells - supply
	{
		this->debit_supp = static_cast< float >( msg.value()) ;
		time_supp = msg.time();
		duration = msg.time() - initialTime_supp;
		secunde = duration.seconds();
		this->volume += this->debit_supp * secunde / 1000;		// liters -> m3
		initialTime_supp = msg.time();
	}

	if ( msg.port() == qp_in )									// flow from pump station
	{
		this->debit_pump = static_cast< float >( msg.value()) ;
		duration = msg.time() - initialTime_pump;
		secunde = duration.seconds();
		this->volume -= this->debit_pump * secunde / 1000;		// liters -> m3
		initialTime_pump = msg.time();
	}

	this->level = this->volume / 1000;											// 1000 = surface

	if (this->level < this->alarm_level)
		this->low_level = 1;
	else
		this->low_level = 0;

	this->holdIn( active, this->preparationTime ) ;
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Reservoir::internalFunction( const InternalMessage & )
{
	this->passivate() ;

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Reservoir::outputFunction( const InternalMessage &msg )
{
	this->sendOutput( msg.time(), this->level_out, this->level ) ;
	this->sendOutput( msg.time(), this->low_level_out, this->low_level ) ;
	return *this ;
}
