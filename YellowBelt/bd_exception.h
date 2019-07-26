#pragma once

#include <string>

class BaseException {
protected:
	std::string m_message {};

public:
	explicit BaseException();
	explicit BaseException(std::string message);

	virtual std::string what() const;
};

class DateException : public BaseException {
public:
	explicit DateException();
	explicit DateException(std::string message);
};

class OperationException : public BaseException {
public:
	explicit OperationException();
	explicit OperationException(std::string message);
};

class CommandHandlerException : public BaseException {
public:
	explicit CommandHandlerException();
	explicit CommandHandlerException(std::string message);
};

