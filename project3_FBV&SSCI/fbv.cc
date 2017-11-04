/************************************************************
 Course		: 	CSC/ECE506
 Source 		:	fbv.cc
 Owner		:	Ed Gehringer
 Email Id	:	efg@ncsu.edu
 ------------------------------------------------------------*
 © Please do not replicate this code without consulting
 the owner & instructor! Thanks!
 *************************************************************/
#include "fbv.h"

void FBV::update_sharer_entry(int proc_num) {
	bit[proc_num] = true;
}

void FBV::remove_sharer_entry(int proc_num) {
	bit[proc_num] = false;
}

int FBV::check_sharer_entry(int num_proc) {

	for (int i = 0; i < num_proc; i ++ ){
		if (bit[i])
			return 1;
	}
	return 0; // Returning 0 to avoid compilation errors.
}

void FBV::sendInt_sharer(ulong addr, int num_proc, int proc_num) {

	for (int i = 0; i < num_proc; i ++)	{
		if (i != proc_num)
			if(bit [i])
				sendInt(addr, i);
			}
	}

void FBV::sendInv_sharer(ulong addr, int num_proc, int proc_num) {

	for (int i = 0; i < num_proc; i ++)	{
		if (i != proc_num)
			if(bit [i]){
				sendInv(addr, i);
		}
	}

}
