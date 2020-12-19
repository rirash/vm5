#include "Move.h"

void Load_rr::operator()(Processor& cpu)				//Пересылка регистр-регистр
{
	cmd32 com = cpu.get_Command();					//Разбираем команду
	if (com.command16.s == 0) 					//Имеем дело с 16-битными значениями
	{
		datatype16 t16;
		t16.w16.i16 = cpu.get_int16(com.command16.r2);		//Вытаскаваем из 2-го операнда
		cpu.put(t16, com.command16.r1);				//Кладем в 1-ый операнд
	}
	else								//Имеем дело с 32-битными значениями
	{
		datatype32 t32;
		t32.w32.i32 = cpu.get_int32(com.command16.r2);
		cpu.put(t32, com.command16.r1);
	}
}

void Load_rm::operator()(Processor& cpu)				//Пересылка регистр-память
{
	cmd32 com = cpu.get_Command();
	if (com.command16.s == 0)					//Слово
	{
		datatype16 t16;
		t16.w16.i16 = cpu.get_int16(com.command16.r2); 		//Из регистра (2 операнд)
		cpu.memory.load(t16, cpu.get_int16(com.command16.r1) + com.off);	//В память (адрес в первом операнде + смещение, если есть)
	}
	else								//Двойное слово
	{
		datatype32 t32;
		t32.w32.i32 = cpu.get_int32(com.command16.r2);
		cpu.memory.load(t32, cpu.get_int32(com.command16.r1) + com.off);
	}
}

void Load_mr::operator()(Processor& cpu)				//Пересылка память-регистр
{
	cmd32 com = cpu.get_Command();
	if (com.command16.s == 0)					//Слово
	{
		datatype16 t16;
		t16.w16.i16 = cpu.memory.get_int16(cpu.get_int16(com.command16.r2) + com.off);
		cpu.put(t16, com.command16.r1);
	}
	else								//Двойное слово
	{
		datatype32 t32;
		t32.w32.i32 = cpu.memory.get_int32(cpu.get_int32(com.command16.r2) + com.off);
		cpu.put(t32, com.command16.r1);
	}
}
