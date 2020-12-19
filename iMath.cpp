#include "Processor.h"
#include "iMath.h"

//ЦЕЛОЧИСЛЕННАЯ АРИФМЕТИКА
void iMath::change_flag(datatype16 res, Processor& cpu) noexcept 		//Расстановка флагов
{
	if (res.w16.i16 < 0) cpu.psw.setSF(1);
	if (res.w16.i16 == 0) cpu.psw.setZF(1);
}

void iMath::change_flag(datatype32 res, Processor& cpu) noexcept		//Расстановка флагов
{
	if (res.w32.i32 < 0) cpu.psw.setSF(1);
	if (res.w32.i32 == 0) cpu.psw.setZF(1);
}

void iMath::operator()(Processor& cpu)						//Непосредственная операция
{
	cpu.psw.resetFlags();							//Очистка флагов
	cmd32 com = cpu.get_Command();
	if (com.command16.s == 0)						//Если имеем дело с 16-битными операндами...
	{
		datatype16 res;
		res.w16.i16 = (int16_t)calculate(cpu.get_int16(com.command16.r1), cpu.get_int16(com.command16.r2));
		cpu.put(res, com.command16.r1);					//Результат по первому операнду
		change_flag(res, cpu);
	}
	else									//Если имеем дело с 32-битными операндами
	{
		datatype32 res;
		res.w32.i32 = calculate(cpu.get_int32(com.command16.r1), cpu.get_int32(com.command16.r2));
		cpu.put(res, com.command16.r1);					//Результат по первому операнду
		change_flag(res, cpu);
	}
}
