#ifndef IMATH_H
#define IMATH_H
#include "Struct.h"
#include "Command.h"

class iMath : public Command
{
	void change_flag(datatype32 res, Processor& cpu) noexcept;
	void change_flag(datatype16 res, Processor& cpu) noexcept;
	virtual int32_t calculate(int32_t left, int32_t right) = 0;
	void operator()(Processor& cpu);
};

class iAdd : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right) { return left + right; }
};

class iSub : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right) { return left - right; }
};

class iMul : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right) { return left * right; }
};

class iDiv : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right)
	{ 
		if (right == 0) throw std::invalid_argument("Деление на ноль невозможно!");
		return left / right; 
	}
};

class Remainder : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right) { return left % right; }
};

class Inc : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right) { return left + 1; }
};

class Dec : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right) { return left - 1; }
};

class And : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right) { return left & right; }
};

class Or : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right) { return left | right; }
};

class Not : public iMath
{
	virtual int32_t calculate(int32_t left, int32_t right)  { return ~left; }
};
#endif//! IMATH_H
