#ifndef MOVE_H
#define MOVE_H
#include "Struct.h"
#include "Processor.h"
#include "Command.h"

class Load_rr : public Command
{
	void operator()(Processor& cpu);
};

class Load_rm : public Command
{
	void operator()(Processor& cpu);
};

class Load_mr : public Command
{
	void operator()(Processor& cpu);
};
#endif//! MOVE_H
