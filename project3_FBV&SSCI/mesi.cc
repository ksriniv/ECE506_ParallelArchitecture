/************************************************************
 Course		: 	CSC/ECE506
 Source 		:	mesi.cc
 Owner		:	Ed Gehringer
 Email Id	:	efg@ncsu.edu
 ------------------------------------------------------------*
 © Please do not replicate this code without consulting
 the owner & instructor! Thanks!
 *************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "cache.h"

#include "main.h"
#include "mesi.h"

/*--------- MESI Allocate Function --------------*/

cache_line * MESI::allocate_line(ulong addr) {
	ulong tag;
	cache_state state;

	cache_line *victim = find_line_to_replace(addr);
	assert(victim != 0);
	state = victim->get_state();
	if (state == M)
		write_back(addr);

	ulong victim_tag = victim->get_tag();
	dir_entry* dir_line = directory->find_dir_line(victim_tag);
	if (dir_line != NULL) {
		dir_line->remove_sharer_entry(cache_num);
		int present = 0;
		present = dir_line->check_sharer_entry(num_processors);
		if (!present)
			dir_line->state = U;
	}

	tag = tag_field(addr);
	victim->set_tag(tag);
	victim->set_state(I);
	return victim;
}

/*--------- Processor Read Function--------------*/

void MESI::PrRd(ulong addr, int processor_number) {
	current_cycle++;
	reads++;
	// cout << "Reads is :" << reads << endl;
	cache_line *line = find_line(addr);
	if (line == NULL || line->get_state() == I ){					// This is a miss

		read_misses++;
		cache_line *newline = allocate_line(addr);
		dir_entry *dir_line = directory->find_dir_line(tag_field (addr));

  	//cout << "DIR Line is :"<< dir_line -> get_state() << "   Naanga irukom" << endl;
		// Note : != assignment does not work with enum!!
		if (dir_line == NULL || dir_line -> get_state() == U){ 		 											// State I --> E
			I2E++;
			newline->set_state(E);

		}

		else {																																				// State I --> S
			I2S++;
			newline->set_state(S);
		}
		// Read miss --> SignalRd
		signal_rds++;
		signalRd(addr, processor_number);
}

else if ((line->get_state() == E || line->get_state() == S || line->get_state() == M )){
		 update_LRU(line);
  }
}

/*--------- Processor Write Function--------------*/
void MESI::PrWr(ulong addr, int processor_number) {
  current_cycle++;
  writes++;
  cache_line * line = find_line(addr);
	if (line == NULL || line->get_state() == I){
		/* This is a miss */
		write_misses++;
    cache_line *newline = allocate_line(addr);

		I2M++;
    newline->set_state(M);
		signal_rdxs++;
		signalRdX(addr, processor_number);
	}

	else{

    if (line->get_state() == E){
			E2M++;
			line->set_state(M);
      update_LRU(line);
		}

		else if (line->get_state() == S){
			S2M++;
      line->set_state(M);
      update_LRU(line);
			signal_upgrs++;
			signalUpgr(addr, processor_number);

		}

		else if (line->get_state() == M){
			/* Since it's a hit, update LRU and update state */
			update_LRU(line);
		}
	}
}

/*-------------- Signal Read Function ----------------*/
void MESI::signalRd(ulong addr, int processor_number) {
	//	cout << "Enterting Signal Read" << endl;
		dir_entry* dir_line = directory->find_dir_line(tag_field (addr));
		/*---------- Directory Update ------------- */
		if ( dir_line == NULL ){
				dir_entry* newline = directory -> find_empty_line(tag_field (addr));
				newline ->tag = tag_field (addr);
				newline ->state = EM;
				newline ->update_sharer_entry(processor_number);
				}

		else if (dir_line -> get_state()  == U ){
					dir_line -> state = EM;
					dir_line -> update_sharer_entry(processor_number);
				}
		else if (dir_line -> get_state()  == S_)
					dir_line -> update_sharer_entry(processor_number);
		else if (dir_line -> get_state()  == EM){
					dir_line -> sendInt_sharer (addr, num_processors, processor_number);
					dir_line -> state = S_;
					dir_EM2S++;
					cache2cache ++;
					dir_line -> update_sharer_entry (processor_number);
		}
	//	cout << "Exiting Signal Read" << endl;
}

/*-------------- Signal ReadX Function ----------------*/
void MESI::signalRdX(ulong addr, int processor_number) {

	dir_entry* dir_line = directory->find_dir_line(tag_field (addr));

/*---------- Directory Update ------------- */
	if ( dir_line == NULL ){
			dir_entry* newline = directory -> find_empty_line(tag_field (addr));
			newline ->tag = tag_field (addr);
			newline ->state = EM;
			newline ->update_sharer_entry(processor_number);
			}

	else if (dir_line -> get_state() == U ){
				dir_line -> state = EM;
				dir_line -> update_sharer_entry(processor_number);
			}
	else if (dir_line -> get_state() == S_){
				dir_line -> state = EM;
				dir_S2EM ++;
				dir_line -> sendInv_sharer (addr, num_processors, processor_number);			// Send Invalidations
				cache2cache++;																														// Update Cache2Cache
				for (int i = 0; i < num_processors; i++)
						dir_line -> remove_sharer_entry (i);																	// Remove other sharer entries
				dir_line -> update_sharer_entry(processor_number);
			}
	else if (dir_line -> get_state()  == EM){
				dir_line -> sendInv_sharer (addr, num_processors, processor_number);			// Send Invalidations
				cache2cache ++;																														// Update Cache2Cache
				for (int i = 0; i < num_processors; i++)
						dir_line -> remove_sharer_entry (i);																	// Remove other sharer entries

				dir_line -> update_sharer_entry (processor_number);
	}
}

void MESI::signalUpgr(ulong addr, int processor_number) {
	dir_entry* dir_line = directory->find_dir_line(tag_field (addr));
	if (dir_line -> get_state()  == S_){
				dir_S2EM ++;
				dir_line -> sendInv_sharer (addr, num_processors, processor_number);			// Send Invalidations

				for (int i = 0; i < num_processors; i++)
						dir_line -> remove_sharer_entry (i);																	// Remove other sharer entries
				dir_line -> update_sharer_entry(processor_number);
			}
	dir_line -> state = EM;
}

void MESI::Int(ulong addr) {
	/* Update the relevant counter, if the cache copy is dirty, same needs to be written back to main memory.
	This is achieved by simply updating the writeback counter */
	cache_line *line = find_line(addr);
	if (line -> get_state() == M || line -> get_state() == E)
		write_back(addr);
	if	(line -> get_state() == M)
		M2S ++;
	else if (line -> get_state() == E)
	  E2S ++;

	line -> set_state(S);
	interventions ++;

}

void MESI::Inv(ulong addr) {
	cache_line *line = find_line(addr);
	if (line -> get_state() == M || line -> get_state() == E)
		write_back(addr);
	line -> set_state(I);
	invalidations++;
}
