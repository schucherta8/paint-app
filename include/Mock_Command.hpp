#ifndef MOCK_COMMAND_H
#define MOCK_COMMAND_H
#include <iostream>
#include "Command.hpp"

class Mock_Command : public Command {
	private:
		std::string m_str;

	public:
		Mock_Command();
		Mock_Command(const std::string& str);
		void execute() override;
    	void undo() override;
};

#endif