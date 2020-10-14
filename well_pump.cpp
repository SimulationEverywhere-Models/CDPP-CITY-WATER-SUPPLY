/*******************************************************************
*
*  DESCRIPTION: Atomic Model Pump
*
*  AUTHOR: Laurentiu Checiu
*
*  EMAIL: mailto://lchec097@uottawa.ca;laurentiu.checiu@rogers.com
*
*  DATE: 10/10/2004
*
*******************************************************************/

/** include files **/
#include "well_pump.h"		// class WellPump
#include "message.h"    	// class ExternalMessage, InternalMessage
#include "mainsimu.h"   	// MainSimulator::Instance().getParameter( ... )
#include "strutil.h"    	// str2float( ... )

/** static variables **/

float WellPump::flow = 0.0;


/** public functions **/

/*******************************************************************
* Function Name: Pump
* Description: Constructor
********************************************************************/


WellPump::WellPump( const string &name )
: Atomic( name )
, start_in( addInputPort( "start_in" ) )
, stop_in( addInputPort( "stop_in" ) )
, flow_out( addOutputPort( "flow_out" ) )
, preparationTime(0,0,0,1)
, activeTime(0,0,10,0)
, state(0)
, start_command(0)
, stop_command(0)
{
	string nom_debit( MainSimulator::Instance().getParameter( description(), "nominal_flow" ) ) ;
	nominal_flow = str2float( nom_debit ) ;
}

/*******************************************************************
* Function Name: initFunction
* Description:
********************************************************************/
Model &WellPump::initFunction()
{
	this->passivate() ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &WellPump::externalFunction( const ExternalMessage &msg )
{
	if ( msg.port() == start_in )
	{
		this->start_command = static_cast< short >( msg.value()) ;

		this->state = this->start_command;

		this->start_command = 0;											// reset start command

		this->flow += this->nominal_flow * this->state;

		this->holdIn( active, this->preparationTime ) ;
	}

	if ( msg.port() == stop_in )
	{
		this->stop_command = static_cast< short >( msg.value()) ;

		this->flow -= this->nominal_flow * this->state;

		this->state = 0;
		this->stop_command = 0;											// reset stop command

		this->holdIn( active, this->preparationTime ) ;
	}

	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &WellPump::internalFunction( const InternalMessage & )
{
	if (this->state)
		this->holdIn( active, this->activeTime ) ;					// Pumping
	else
		this->passivate() ;
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &WellPump::outputFunction( const InternalMessage &msg )
{
	this->sendOutput( msg.time(), this->flow_out, this->flow ) ;
	return *this ;
}
