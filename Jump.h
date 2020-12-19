#ifndef JUMP_H
#define JUMP_H
#include "Command.h"
#include "Processor.h"

class Jmp : public Command 								//Прямой безусловный переход
{
public:
	void go_to(Processor& cpu) noexcept
	{
		cmd32 com = cpu.get_Command();
		uint16_t adress;							//Составной адрес, куда прыгаем
		//По значению, лежащему в первом операнде определяем способ определения адреса
		switch (cpu.get_int16(com.command16.r1))
		{
		case 0: adress = cpu.get_int16(com.command16.r2); break; 		//Адрес лежит в r2
		case 1: adress = cpu.get_int16(com.command16.r2) + com.off; break;	//Адрес = адрес в r2 + смещение
		case 2: adress = com.off;						//Адрес = смещению
		}

		if (com.command16.s == 0)						//Вообще, размер целого операнда. Сейчас же - способ определения перехода
			cpu.psw.setIP(adress); 						//Прямой
		else
			cpu.psw.setIP(cpu.psw.getIP() + adress); 			//Относительный
	}

	void operator()(Processor& cpu) noexcept override { go_to(cpu); }
};

//УСЛОВНЫЕ ПЕРЕХОДЫ
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

//ПЕРЕХОД/ВОЗВРАТ
class Call : public Jmp
{
	void operator()(Processor& cpu) noexcept
	{
		cmd32 com = cpu.get_Command(); 						//Вытаскиваем и разбираем команду
		datatype16 t16; 
		t16.w16.i16 = cpu.psw.getIP();						//Запоминаем адрес возврата
		cpu.put(t16, com.command16.r1);
		cpu.psw.setIP(cpu.get_uint16(com.command16.r2));			//Прыгаем по новому адресу
	}
};

class Return : public Jmp
{
	void operator()(Processor& cpu) noexcept
	{
		cmd32 com = cpu.get_Command();						//Разбираем команду
		cpu.psw.setIP(cpu.get_uint16(com.command16.r1));			//Возвращаемся по старому IP
	}
};

#endif//! JUMP_H
