#include "Move.h"

void Load_rr::operator()(Processor& cpu)
{
	cmd32 com = cpu.get_Command();
	if (com.command16.s == 0) //Говорим о слове
	{
		datatype16 t16;
		t16.w16.i16 = cpu.get_int16(com.command16.r2);
		cpu.put(t16, com.command16.r1);
	}
	else//Говорим о двойном слове
	{
		datatype32 t32;
		t32.w32.i32 = cpu.get_int32(com.command16.r2);
		cpu.put(t32, com.command16.r1);
	}
}

void Load_rm::operator()(Processor& cpu)
{
	cmd32 com = cpu.get_Command();
	if (com.command16.s == 0)//Говорим о слове
	{
		datatype16 t16;
		t16.w16.i16 = cpu.get_int16(com.command16.r2);
		cpu.memory.load(t16, cpu.get_int16(com.command16.r1) + com.off);
	}
	else//Говорим о двойном слове
	{
		datatype32 t32;
		t32.w32.i32 = cpu.get_int32(com.command16.r2);
		cpu.memory.load(t32, cpu.get_int32(com.command16.r1) + com.off);
	}
}

void Load_mr::operator()(Processor& cpu)
{
	cmd32 com = cpu.get_Command();
	if (com.command16.s == 0)//Говорим о слове
	{
		datatype16 t16;
		t16.w16.i16 = cpu.memory.get_int16(cpu.get_int16(com.command16.r2) + com.off);
		cpu.put(t16, com.command16.r1);
	}
	else
	{
		datatype32 t32;
		t32.w32.i32 = cpu.memory.get_int32(cpu.get_int32(com.command16.r2) + com.off);
		cpu.put(t32, com.command16.r1);
	}
}