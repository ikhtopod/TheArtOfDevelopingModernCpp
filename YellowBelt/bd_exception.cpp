#include "bd_exception.h"

BaseException::BaseException() : BaseException("") {}
BaseException::BaseException(std::string message) : m_message(message) {}

std::string BaseException::what() const {
	return m_message;
}


DateException::DateException() : BaseException() {}
DateException::DateException(std::string message) :
	BaseException(message) {}


OperationException::OperationException() : BaseException() {}
OperationException::OperationException(std::string message) :
	BaseException(message) {}


CommandHandlerException::CommandHandlerException() : BaseException() {}
CommandHandlerException::CommandHandlerException(std::string message) :
	BaseException(message) {}
