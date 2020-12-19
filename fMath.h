#ifndef FMATH_H
#define FMATH_H
#include <cmath>
#include "Struct.h"
#include "Command.h"

//ВЕЩЕСТВЕННАЯ АРИФМЕТИКА
class fMath : public Command
{
	void change_flag(datatype32 res, Processor& cpu) noexcept;
	virtual float calculate(float left, float right) = 0;
	void operator()(Processor& cpu);
};

class fAdd : public fMath
{
	float calculate(float left, float right) { return left + right; }
};

class fSub : public fMath
{
	float calculate(float left, float right) { return left - right; }
};

class fMul : public fMath
{
	float calculate(float left, float right) { return left * right; }
};

class fDiv : public fMath
{
	float calculate(float left, float right)
	{ 
		if (fabs(right) < 0.000000001) throw std::invalid_argument("Деление на ноль невозможно!");
		return left / right; 
	}
};






#endif//! FMATH_H
