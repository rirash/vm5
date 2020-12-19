#include "Processor.h"
#include "fMath.h"

void fMath::change_flag(datatype32 res, Processor& cpu) noexcept 		//Расстановка флагов
{
	if (res.w32.f < 0) cpu.psw.setSF(1);
	if (fabs(res.w32.f) < 0.000000001) cpu.psw.setZF(1);
}

void fMath::operator()(Processor& cpu)						//Как таковая операция
{
	cpu.psw.resetFlags();							//Очищаем флаги
	datatype32 res;
	cmd32 com = cpu.get_Command();
	res.w32.f = calculate(cpu.get_float(com.command16.r1), cpu.get_float(com.command16.r2)); //Выполняем операцию
	cpu.put(res, com.command16.r1);						//Результат кладем в первый операнд
	change_flag(res, cpu);							//Расстановка флагов
}
