#include "Struct.h"
#include "Processor.h"

//Для регистров интерфейс в Processor.h, а реализовать как-то нужно... Так вот...
//Получение всего и вся из регистров
//Необходимо учесть, что всего 16-битных регистров 8, однако они объединены в 4 32-битных регистра union-ом...)
//+ не нужно учитывать четный номер регистра или нет при 32-битных данных
int16_t Processor::get_int16(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 7) throw std::invalid_argument("Нет такого регистра!");
	return reg[num_reg / 2].w16[num_reg % 2].i16; 				//Танцы с бубном, дабы получить нужный регистр
}

uint16_t Processor::get_uint16(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 7) throw std::invalid_argument("Нет такого регистра!");
	return reg[num_reg / 2].w16[num_reg % 2].ui16;
}

int32_t Processor::get_int32(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 3) throw std::invalid_argument("Нет такого регистра!");
	return reg[num_reg].w32.i32;
}

uint32_t Processor::get_uint32(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 3) throw std::invalid_argument("Нет такого регистра!");
	return reg[num_reg].w32.ui32;
}

float Processor::get_float(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 3) throw std::invalid_argument("Нет такого регистра!");
	return reg[num_reg].w32.f;
}

void Processor::put(datatype16 val, uint16_t num_reg)
{
	if (num_reg < 0 || num_reg > 7) throw std::invalid_argument("Нет такого регистра!");
	reg[num_reg / 2].w16[num_reg % 2].i16 = val.w16.i16;
}

void Processor::put(datatype32 val, uint16_t num_reg)
{
	if (num_reg < 0 || num_reg > 3) throw std::invalid_argument("Нет такого регистра!");
	reg[num_reg].w32.i32 = val.w32.i32;
}
