#include <iostream>
#include "Processor.h"
#include "in_out.h"

//ВВОД/ВЫВОД
void IO::operator()(Processor& cpu) noexcept
{
	enum io_mode : uint8_t 		//Что делаем? Вводим/выводим целые/вещественные
	{
		in_i = 0,
		in_ui = 1,
		in_f = 2,
		out_i = 3,
		out_ui = 4,
		out_f = 5,
	};

	cmd32 com = cpu.get_Command();
	//Режим ввода/вывода определяем по второму операнду
	uint16_t mode = cpu.get_int16(com.command16.r2);
	uint8_t s = com.command16.s;
	if (s == 0)			//Если имеем дело с 16-битными данными
	{
		switch (mode)
		{
		case in_i:
		{
			datatype16 val;
			std::cout << "\nВведите короткое целое знаковое число: "; std::cin >> val.w16.i16;
			cpu.put(val, com.command16.r1);
			break;
		}

		case in_ui:
		{
			datatype16 val;
			std::cout << "\nВведите короткое целове беззнаковое число: "; std::cin >> val.w16.ui16;
			cpu.put(val, com.command16.r1);
			break;
		}

		case out_i:
		{
			std::cout << "\nInt16: " << cpu.get_int16(com.command16.r1); break;
		}

		case out_ui:
		{
			std::cout << "\nUint16: " << cpu.get_uint16(com.command16.r1); break;
		}
		}
	}
	else				//Если имеем дело с 32-битными данными
	{
		switch (mode)
		{
		case in_i:
		{
			datatype32 val;
			std::cout << "\nВведите длинное целое знаковое число: "; std::cin >> val.w32.i32;
			cpu.put(val, com.command16.r1);
			break;
		}

		case in_ui:
		{
			datatype32 val;
			std::cout << "\nВведите длинное целое беззнаковое число: "; std::cin >> val.w32.ui32;
			cpu.put(val, com.command16.r1);
			break;
		}

		case in_f:
		{
			datatype32 val;
			std::cout << "\nВведите вещественное число: "; std::cin >> val.w32.f;
			cpu.put(val, com.command16.r1);
			break;
		}

		case out_i:
		{
			std::cout << "\nInt32: " << cpu.get_int32(com.command16.r1); break;
		}

		case out_ui:
		{
			std::cout << "\nUint32: " << cpu.get_uint32(com.command16.r1); break;
		}

		case out_f:
		{
			std::cout << "\nFloat: " << cpu.get_float(com.command16.r1); break;
		}
		}
	}
}
