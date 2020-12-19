#ifndef MOVE_H
#define MOVE_H
#include "Struct.h"
#include "Processor.h"
#include "Command.h"

class Load_rr : public Command			//Пересылка регистр-регистр
{
	void operator()(Processor& cpu);
};

class Load_rm : public Command			//Пересылка регистр-память
{
	void operator()(Processor& cpu);
};

class Load_mr : public Command			//Пересылка память-регистр
{
	void operator()(Processor& cpu);
};
#endif//! MOVE_H
