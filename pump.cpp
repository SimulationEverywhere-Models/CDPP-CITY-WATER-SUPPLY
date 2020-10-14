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
#include "pump.h"      // class Pump
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "strutil.h"       // str2float( ... )

/** public functions **/

/*******************************************************************
* Function Name: Pump
* Description:
********************************************************************/
float Pump::flow = 0.0;
float Pump::well_flow = 0.0;

Pump::Pump( const string &name )
: Atomic( name )
, start_in( addInputPort( "start_in" ) )
, stop_in( addInputPort( "stop_in" ) )
, level_in( addInputPort( "level_in" ) )
, low_level_in( addInputPort( "low_level_in" ) )
, power_in( addInputPort( "power_in" ) )
, state_out( addOutputPort( "state_out" ) )
, flow_out( addOutputPort( "flow_out" ) )
, wflow_out( addOutputPort( "wflow_out" ) )
, preparationTime(0,0,10,0)
, activeTime(0,0,10,0)
, level(2.3)
, state(0)
, power(1)
, start_command(0)
, stop_command(0)
{
	string nom_debit( MainSimulator::Instance().getParameter( description(), "nominal_flow" ) ) ;
	if (nom_debit != "")
		nominal_flow = str2float( nom_debit ) ;

	string al_niv( MainSimulator::Instance().getParameter( description(), "alarm_level" )  ) ;
	if (al_niv != "")
		alarm_level = str2float( al_niv );
}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &Pump::initFunction()
{
	this->passivate() ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Pump::externalFunction( const ExternalMessage &msg )
{
	if ( msg.port() == power_in )
	{
		this->power = static_cast< short >( msg.value()) ;
	}

	if ( msg.port() == level_in )
	{
		this->level = static_cast< float >( msg.value()) ;
	}

	if ( msg.port() == low_level_in )
	{
		this->low_level = static_cast< short >( msg.value()) ;

		if (this->low_level)
		{
			this->state = 0;												// stop pumps
			this->flow = 0.0;
			this->passivate() ;
		}
		else
			this->holdIn( active, this->preparationTime ) ;

	}

	if ( msg.port() == start_in )
	{
		this->start_command = static_cast< short >( msg.value()) ;

		if ( this->level > this->alarm_level )
		{
			this->state = this->start_command & this->power;
		}

		this->start_command = 0;											// reset start command

		this->flow += this->nominal_flow * this->state;

		this->holdIn( active, this->preparationTime ) ;
	}

	if ( msg.port() == stop_in )
	{
		this->stop_command = static_cast< short >( msg.value()) ;

		if (this->state)
		{
			this->flow -= this->nominal_flow;
		}

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
Model &Pump::internalFunction( const InternalMessage & )
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
Model &Pump::outputFunction( const InternalMessage &msg )
{
	this->sendOutput( msg.time(), this->flow_out, this->flow ) ;
	this->sendOutput( msg.time(), this->state_out, this->state ) ;
	return *this ;
}
