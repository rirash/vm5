#include "Processor.h"
#include "iMath.h"
#include "fMath.h"
#include "in_out.h"
#include "Move.h"
#include "Jump.h"

Processor::Processor()
{
	command[stop] = new Stop();

	command[move_rr] = new Load_rr();
	command[move_rm] = new Load_rm();
	command[move_mr] = new Load_mr();

	command[i_add] = new iAdd();
	command[i_sub] = new iSub();
	command[i_mul] = new iMul();
	command[i_div] = new iDiv();
	command[remaind] = new Remainder();

	command[log_and] = new And();
	command[log_or] = new Or();
	command[log_not] = new Not();

	command[f_add] = new fAdd();
	command[f_sub] = new fSub();
	command[f_mul] = new fMul();
	command[f_div] = new fDiv();

	command[jmp] = new Jmp();
	command[jzf] = new JmpZF();
	command[jnzf] = new JmpNZF();
	command[jsf] = new JmpSF();
	command[jnsf] = new JmpNSF();

	command[io] = new IO();
	command[call] = new Call();
	command[ret] = new Return();

	//Все очищаем
	JF = false;
	
	psw.setIP(0);
	psw.setSF(0);
	psw.setZF(0);

	cmd.w32.i32 = 0;
}

void Processor::load_Command() noexcept 			//Загрузка команды из памяти
{
	//Команда загружается в 32-битную команду, вне зависимости от того, используется ли ее часть или же она вся
	cmd.t16[0].i16 = memory.get_int16(psw.getIP());
	uint8_t kop = get_Command().command16.KOP;
	if ((kop < 4 && kop > 1) || (kop < 23 && kop > 17)) 	//Команды с этими КОП - 4 байтные, поэтому занимают два слова
		cmd.t16[1].i16 = memory.get_int16(psw.getIP() + 1);
}

void Processor::reset() noexcept				//Очистка флагов, регистров
{
	psw.setIP(0);
	psw.setSF(0);
	psw.setZF(0);
	for (std::size_t i = 0; i < 4; i++) reg[i].w32.i32 = 0;
	JF = 0;
}

void Processor::debug() const noexcept				//Дебаг
{
	cmd32 com = get_Command();
	std::cout << "\nВыполняемая команда: КОП:" << com.command16.KOP << " s:" <<
		com.command16.s << " r1:" << com.command16.r1 << " r2:" << com.command16.r2
		<< " offset:" << com.off << " flags:" << (int)psw.getZF() << " "
		<< (int)psw.getSF() << " IP:" << psw.getIP() << "\n";
}

void Processor::run() noexcept					//Выполнение программы
{
	load_Command();						//Загружаем первую команду
	debug();
	cmd32 com = get_Command();
	while (com.command16.KOP != stop)			//Пока КОП != 0
	{
		debug();
		uint8_t kop = get_Command().command16.KOP;
		command[kop]->operator()(*this); 		//Выполняем операцию
		if (!JF) 					//"Прыжки" сами выставляют IP
			if ((kop < 4 && kop > 1) || (kop < 23 && kop > 17)) 	//Ппроверка на 2-х или 4-х байтную команду
				psw.setIP(psw.getIP() + 2);
			else psw.setIP(psw.getIP() + 1);
		load_Command();					//Загрузка новой команды
	}
}
