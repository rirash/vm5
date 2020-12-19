#ifndef IN_OUT_H
#define IN_OUT_H
#include "Command.h"

//ВВОД/ВЫВОД
class IO : public Command
{
	virtual void operator()(Processor& cpu) noexcept override;	//Непосредственно операция
};
#endif//! IN_OUT_H
