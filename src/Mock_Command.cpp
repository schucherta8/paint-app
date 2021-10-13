#include "Mock_Command.hpp"

Mock_Command::Mock_Command() : m_str("") {}

Mock_Command::Mock_Command(const std::string& str) : m_str(str) {}

void Mock_Command::execute() {
	std::cout << m_str << " executing..." << std::endl;
}

void Mock_Command::undo() {
	std::cout << m_str << " undoing..." << std::endl;
}