#ifndef IN_OUT_H
#define IN_OUT_H
#include "Command.h"

class IO : public Command
{
	virtual void operator()(Processor& cpu) noexcept override;
};
#endif//! IN_OUT_H
