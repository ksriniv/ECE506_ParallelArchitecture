/************************************************************
			Course 		: 	CSC456
			Source 		:	msi.cc
			Instructor	:	Ed Gehringer
			Email Id	:	efg@ncsu.edu
------------------------------------------------------------
	© Please do not replicate this code without consulting
		the owner & instructor! Thanks!
*************************************************************/ 
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
using namespace std;
#include "main.h"
#include "moesi.h"

void MOESI::PrRd(ulong addr, int processor_number) {
} 

void MOESI::PrWr(ulong addr, int processor_number) {
} 


void MOESI::BusRd(ulong addr) {
} 

void MOESI::BusRdX(ulong addr) {
} 

void MOESI::BusUpgr(ulong addr) {
} 

bool MOESI::writeback_needed(cache_state state) {
	//edit this function to return the correct boolean value
	return false;
}
