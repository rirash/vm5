#ifndef COMMAND_H
#define COMMAND_H

class Processor;
class Command
{
public:
	virtual void operator() (Processor& cpu) = 0;
};

template <typename T>
T op_plus(const T& left, const T& right) { return left + right; }
template <typename T>
T op_minus(const T& left, const T& right) { return left - right; }
template <typename T>
T op_mul(const T& left, const T& right) { return left * right; }
template <typename T>
T op_div(const T& left, const T& right) { return left / right; }
template <typename T>
T op_and(const T& left, const T& right) { return left & right; }
template <typename T>
T op_or(const T& left, const T& right) { return left | right; }
template <typename T>
T op_remainder(const T& left, const T& right) { return left % right; }

#endif//! COMMAND_H
