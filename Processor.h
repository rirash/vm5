#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <iostream>
#include "Struct.h"
#include "OpCodes.h"
#include "Memory.h"
#include "PSW.h"
#include "Command.h"

class Processor
{
private:
	datatype32 cmd;
	Command* command[23];
	bool JF;
	bool IF;
public:
	PSW psw;
	Memory memory;
	ROH reg[4];

	Processor();

	Processor(Processor&) = delete;
	Processor(Processor&&) = delete;
	Processor operator= (Processor&) = delete;
	Processor operator= (Processor&&) = delete;

	inline cmd32 get_Command() const noexcept { return cmd.command32; }
	void put_JF(bool val) noexcept { JF = val; }
	void put_IF(bool val) noexcept { IF = val; }

	int16_t get_int16(uint16_t num_reg) const;
	uint16_t get_uint16(uint16_t num_reg) const;
	int32_t get_int32(uint16_t num_reg) const;
	uint32_t get_uint32(uint16_t num_reg) const;
	float get_float(uint16_t num_reg) const;
	void put(datatype16 val, uint16_t num_reg);
	void put(datatype32 val, uint16_t num_reg);

	void load_Command() noexcept;
	void reset() noexcept;
	void debug() const noexcept;
	void run() noexcept;
};
#endif//! PROCESSOR_H
