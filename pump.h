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

#ifndef __PUMP_H
#define __PUMP_H

#include "atomic.h"     // class Atomic


class Pump : public Atomic
{
public:
	Pump( const string &name = "Pump" );					//Default constructor

	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &start_in;
	const Port &stop_in;
	const Port &level_in;
	const Port &low_level_in;
	const Port &power_in;
	Port &state_out;
	Port &flow_out;
	Port &wflow_out;

	float alarm_level;
	float nominal_flow;

	Time preparationTime;
	Time activeTime;

	// Parameters
	static float flow;								// if we have more pumps the flow should be the sum of all flows  from all pumps
	static float well_flow;							// pumps  from wells
	float level;
	short low_level;
	short state;
	short power;
	short start_command;
	short stop_command;


};	// class Pump

// ** inline ** //
inline string Pump::className() const
{
	return "Pump" ;
}

#endif   //__PUMP_H
