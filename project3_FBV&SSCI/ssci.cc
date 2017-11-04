/************************************************************
 Course		: 	CSC/ECE506
 Source 		:	ssci.cc
 Owner		:	Ed Gehringer
 Email Id	:	efg@ncsu.edu
 ------------------------------------------------------------*
 ï¿½ Please do not replicate this code without consulting
 the owner & instructor! Thanks!
 *************************************************************/
#include "ssci.h"
#include <algorithm>

using namespace std;
void SSCI::update_sharer_entry(int proc_no) {

	cache_list.push_back(proc_no);					// Push the entry to the linked list
}

void SSCI::remove_sharer_entry(int proc_num) {
		cache_list.remove(proc_num);					// Remove the entry from the linked list
}

int SSCI::check_sharer_entry(int proc_num) {
	int count = 1;
	if (!cache_list.empty())
		return count;												// Returning 1 if empty
	else
		return 0; 													// Returning 0 to avoid compilation error

}

void SSCI::sendInv_sharer(ulong addr, int num_proc, int proc_num) {

	for (int i = 0; i < num_proc; i++)
		if ( i != proc_num)
			if ( find ( cache_list.begin(), cache_list.end(), i ) != cache_list.end() )
					sendInv ( addr, i);

}

void SSCI::sendInt_sharer(ulong addr, int num_proc, int proc_num) {

	for (int i = 0; i < num_proc; i++)
			if ( find ( cache_list.begin(), cache_list.end(), i ) != cache_list.end() )
					sendInt ( addr, i);

}
