#ifndef COMMAND_H
#define COMMAND_H

class Processor;
class Command							//Абстрактный класс КОМАНДА
{
public:
	virtual void operator() (Processor& cpu) = 0;
};

#endif//! COMMAND_H
