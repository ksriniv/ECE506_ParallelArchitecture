/************************************************************
 Course		: 	CSC/ECE506
 Source 		:	directory.h
 Owner		:	Ed Gehringer
 Email Id	:	efg@ncsu.edu
 ------------------------------------------------------------*
 © Please do not replicate this code without consulting
 the owner & instructor! Thanks!
 *************************************************************/

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
#include "main.h"

typedef unsigned long ulong;
typedef unsigned char uchar;
typedef unsigned int uint;

//***directory states***/
enum dir_state {
	U, 	// unowned
	EM, // exclusive-modified
	S_ 	// shared
};
//
class dir_entry {
public:
	ulong tag;
	dir_state state;
	virtual ~dir_entry() { }
	virtual unsigned long get_dir_tag() = 0;
	virtual dir_state get_state() = 0;
	virtual void set_dir_state(dir_state d_state) = 0;
	virtual void set_dir_tag(unsigned long a) = 0;
	virtual void update_sharer_entry(int proc_num) = 0;
	virtual void remove_sharer_entry(int proc_num) = 0;
	virtual int check_sharer_entry(int np) = 0;
	virtual void sendInv_sharer(ulong addr, int proc_num, int num_proc) = 0;
	virtual void sendInt_sharer(ulong addr, int proc_num, int num_proc) = 0;
};
//
class Directory {
//
private:
	static ulong dir_size;
public:
	vector<dir_entry *> entry;
	ulong invalidations, interventions;
	Directory(ulong, int);
	virtual ~Directory();
//
	dir_entry* find_empty_line(ulong dir_tag);
    dir_entry* find_dir_line(ulong);
//	
	ulong get_invalidations() 	{return invalidations;}
//	
//  The following five methods were incorrectly copied from cache.h.
//  Normally you don't need to implement them.
//	virtual void signalRd(ulong, int) 	{return;};
//  virtual void signalRdX(ulong, int) 	{return;};
//  virtual void signalUpgr(ulong, int)	{return;};
//  virtual void Int(ulong) 			{return;};
//  virtual void Inv(ulong) 			{return;};
};
//
#endif
