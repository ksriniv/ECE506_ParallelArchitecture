/************************************************************
 Course		: 	CSC/ECE506
 Source 		:	directory.cc
 Owner		:	Ed Gehringer
 Email Id	:	efg@ncsu.edu
 ------------------------------------------------------------*
 � Please do not replicate this code without consulting
 the owner & instructor! Thanks!
 *************************************************************/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "directory.h"
#include "main.h"
#include "fbv.h"
#include "ssci.h"

ulong Directory::dir_size = 0;

Directory::Directory(ulong num_entries, int type) {
	invalidations = interventions = 0;
	dir_size = num_entries;

	for (uint i = 0; i < dir_size; i++) {
		if (type) {
			entry.push_back(new SSCI());
		}
		else {
			entry.push_back(new FBV());
//			cout << "Creating FBV" << endl;
		}
		entry[i]->tag = 0;
		entry[i]->state = U;
	}
}

Directory::~Directory() {
	for (uint i = 0; i < dir_size; i++) {
		delete entry[i];
	}
}
//
dir_entry *Directory::find_dir_line(ulong tag) {

	for (uint i = 0; i < dir_size; i++)	{
		if ((entry[i]->tag) == tag)	{
			return entry[i];
		}
	}
	return NULL;
}
//
dir_entry *Directory::find_empty_line(ulong tag) {

	for (uint i = 0; i < dir_size; i++)	{
		if ( entry[i]->get_state() == U){
			return entry[i];
		}
	}

	return NULL;
}
//
