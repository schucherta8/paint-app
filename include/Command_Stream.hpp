#ifndef COMMAND_STREAM_H
#define COMMAND_STREAM_H

#include <list>
#include <stdbool.h>
#include "Command.hpp"

class Command_Stream {
	private:
	   	//List to store commands
    	std::list<Command*> m_commands;
    	//Pointer to current command
    	std::list<Command*>::iterator m_current;	

	public:
		Command_Stream();
		void add(Command* c);
		bool previous();
		Command* getCurrent();
		bool next();
		void remove();
		bool isEmpty();
		void clear();
};

#endif