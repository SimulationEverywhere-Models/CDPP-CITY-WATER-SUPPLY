/*******************************************************************
*
*  DESCRIPTION: Atomic Model Well Pump
*
*  AUTHOR: Laurentiu Checiu
*
*  EMAIL: mailto://lchec097@uottawa.ca;laurentiu.checiu@rogers.com
*
*  DATE: 10/10/2004
*
*******************************************************************/

#ifndef __WELL_PUMP_H
#define __WELL_PUMP_H

#include "atomic.h"     // class Atomic


class WellPump : public Atomic
{
public:
	WellPump( const string &name = "WellPump" );					//Default constructor

	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &start_in;
	const Port &stop_in;
	Port &flow_out;

	float nominal_flow;

	Time preparationTime;
	Time activeTime;

	// Parameters
	static float flow;								// if we have more pumps the flow should be the sum of all flows  from all pumps
	short state;
	short start_command;
	short stop_command;


};	// class WellPump

// ** inline ** //
inline string WellPump::className() const
{
	return "WellPump" ;
}

#endif   //__WELL_PUMP_H
