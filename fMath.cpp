#include "Processor.h"
#include "fMath.h"

void fMath::change_flag(datatype32 res, Processor& cpu) noexcept
{
	if (res.w32.f < 0) cpu.psw.setSF(1);
	if (fabs(res.w32.f) < 0.000000001) cpu.psw.setZF(1);
}

void fMath::operator()(Processor& cpu)
{
	cpu.psw.resetFlags();
	datatype32 res;
	cmd32 com = cpu.get_Command();
	res.w32.f = calculate(cpu.get_float(com.command16.r1), cpu.get_float(com.command16.r2));
	cpu.put(res, com.command16.r1);
	change_flag(res, cpu);
}