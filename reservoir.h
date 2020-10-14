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

#ifndef __RESERVOIR_H
#define __RESERVOIR_H

#include "atomic.h"     // class Atomic

class Reservoir : public Atomic
{
public:
	Reservoir( const string &name = "Reservoir" );					//Default constructor

	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &q_in;
	const Port &qp_in;
	Port &level_out;
	Port &low_level_out;

	float level;
	float alarm_level;
	short low_level;
	float debit_supp;
	float debit_pump;
	float volume;

	Time preparationTime;
	Time initialTime_supp;
	Time initialTime_pump;

};	// class Reservoir

// ** inline ** //
inline string Reservoir::className() const
{
	return "Reservoir" ;
}

#endif   //__RESERVOIR_H
