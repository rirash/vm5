#include "Struct.h"
#include "Processor.h"

int16_t Processor::get_int16(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 7) throw std::invalid_argument("Некорректный номер регистра!");
	return reg[num_reg / 2].w16[num_reg % 2].i16;
}

uint16_t Processor::get_uint16(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 7) throw std::invalid_argument("Некорректный номер регистра!");
	return reg[num_reg / 2].w16[num_reg % 2].ui16;
}

int32_t Processor::get_int32(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 3) throw std::invalid_argument("Некорректный номер регистра!");
	return reg[num_reg].w32.i32;
}

uint32_t Processor::get_uint32(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 3) throw std::invalid_argument("Некорректный номер регистра!");
	return reg[num_reg].w32.ui32;
}

float Processor::get_float(uint16_t num_reg) const
{
	if (num_reg < 0 || num_reg > 3) throw std::invalid_argument("Некорректный номер регистра!");
	return reg[num_reg].w32.f;
}

void Processor::put(datatype16 val, uint16_t num_reg)
{
	if (num_reg < 0 || num_reg > 7) throw std::invalid_argument("Некорректный номер регистра!");
	reg[num_reg / 2].w16[num_reg % 2].i16 = val.w16.i16;
}

void Processor::put(datatype32 val, uint16_t num_reg)
{
	if (num_reg < 0 || num_reg > 3) throw std::invalid_argument("Некорректный номер регистра!");
	reg[num_reg].w32.i32 = val.w32.i32;
}