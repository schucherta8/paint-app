#include "Command_Stream.hpp"

Command_Stream::Command_Stream() {
	m_current = m_commands.end();
}

void Command_Stream::add(Command* c) {
	if(m_current != m_commands.end()) {
		std::list<Command*>::iterator end = --m_commands.end();
		while(m_current != end) {
			remove();
			end = --m_commands.end();
		}
	}
	m_commands.push_back(c);
	m_current = --m_commands.end();
}

bool Command_Stream::previous() {
	if(!m_commands.empty()) {
		m_current--;
		return true;
	}
	return false;
}

Command* Command_Stream::getCurrent() {
	if(!m_commands.empty()) {
		return *m_current;
	}
	return nullptr;
}

bool Command_Stream::next() {
	if(m_current != --m_commands.end()) {
		m_current++;
		return true;
	}
	return false;
}

void Command_Stream::remove() {
	if(!m_commands.empty()) {
		Command* cmd = m_commands.back();
		delete cmd;
		--m_current;
		m_commands.pop_back();
	}
}

bool Command_Stream::isEmpty() {
	return m_commands.empty();
}

void Command_Stream::clear() {
	while(!isEmpty()) {
		remove();
	}
}