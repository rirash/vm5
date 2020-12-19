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
		uint16_t adress;//����� �����
		//����� � ������ �������� ��������� "�����" ����������� ������
		switch (cpu.get_int16(com.command16.r1))
		{
		case 0: adress = cpu.get_int16(com.command16.r2); break; //����� � r2
		case 1: adress = cpu.get_int16(com.command16.r2) + com.off; break;//����� = ����� � r2 + offset
		case 2: adress = com.off;//����� = offset
		}

		if (com.command16.s == 0)//������ �������
			cpu.psw.setIP(adress); //ip = �����
		else                      //������������� �������
			cpu.psw.setIP(cpu.psw.getIP() + adress); //ip += �����
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
		cmd32 com = cpu.get_Command(); //����������� � ��������� �������
		datatype16 t16; 
		t16.w16.i16 = cpu.psw.getIP();//��������� ip
		cpu.put(t16, com.command16.r1);//� ������ �������
		cpu.psw.setIP(cpu.get_uint16(com.command16.r2));//������ ip �� ����� �� ������
	}
};

class Return : public Jmp
{
	void operator()(Processor& cpu) noexcept
	{
		cmd32 com = cpu.get_Command();//����������� � ��������� �������
		cpu.psw.setIP(cpu.get_uint16(com.command16.r1));//����������� ����� ��������
	}
};

#endif//! JUMP_H
