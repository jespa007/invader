/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */
#pragma once

class System{
public:
	static void synchTime();
	static Uint32 getTime();
	//static Uint32 getSynchTime();

private:
	static Uint32 synch_time;
};
