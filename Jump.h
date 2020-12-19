#ifndef JUMP_H
#define JUMP_H
#include "Command.h"
#include "Processor.h"

class Stop : public Command
{
	void operator()(Processor& cpu) noexcept override { cpu.put_IF(1); }
};

class Jmp : public Command
{
public:
	void go_to(Processor& cpu) noexcept
	{
		cmd32 com = cpu.get_Command();
		uint16_t adress;//Ќовый адрес
		//ѕусть в первом операнде находитс€ "метод" составлени€ адреса
		switch (cpu.get_int16(com.command16.r1))
		{
		case 0: adress = cpu.get_int16(com.command16.r2); break; //јдрес в r2
		case 1: adress = cpu.get_int16(com.command16.r2) + com.off; break;//јдрес = адрес в r2 + offset
		case 2: adress = com.off;//јдрес = offset
		}

		if (com.command16.s == 0)//пр€мой переход
			cpu.psw.setIP(adress); //ip = адрес
		else                      //относительный переход
			cpu.psw.setIP(cpu.psw.getIP() + adress); //ip += адрес
	}

	void operator()(Processor& cpu) noexcept override { go_to(cpu); }
};

class JmpZF : public Jmp
{
	void operator()(Processor& cpu) noexcept override
	{
		if (cpu.psw.getZF() == 1) go_to(cpu);
	}
};

class JmpNZF : public Jmp
{
	void operator()(Processor& cpu) noexcept override
	{
		if (cpu.psw.getZF() == 0) go_to(cpu);
	}
};

class JmpSF : public Jmp
{
	void operator()(Processor& cpu) noexcept override
	{
		if (cpu.psw.getSF() == 1) go_to(cpu);
	}
};

class JmpNSF : public Jmp
{
	void operator()(Processor& cpu) noexcept override
	{
		if (cpu.psw.getSF() == 0) go_to(cpu);
	}
};

class Call : public Jmp
{
	void operator()(Processor& cpu) noexcept
	{
		cmd32 com = cpu.get_Command(); //¬ытаскиваем и разбираем команду
		datatype16 t16; 
		t16.w16.i16 = cpu.psw.getIP();//—охран€ем ip
		cpu.put(t16, com.command16.r1);//в первый операнд
		cpu.psw.setIP(cpu.get_uint16(com.command16.r2));//мен€ем ip на адрес во втором
	}
};

class Return : public Jmp
{
	void operator()(Processor& cpu) noexcept
	{
		cmd32 com = cpu.get_Command();//вытаскиваем и разбираем команду
		cpu.psw.setIP(cpu.get_uint16(com.command16.r1));//вытаскиваем адрес возврата
	}
};

#endif//! JUMP_H
