#ifndef OPCODES_H
#define OPCODES_H
#include <cinttypes>

enum Operations : uint8_t
{
    stop = 0,                                   //Завершение работы
    
    //ПЕРЕСЫЛКИ
    move_rr = 1,                                //Пересылка регистр-регистр
    move_rm = 2,                                //Пересылка регистр-память
    move_mr = 3,                                //Пересылка память-регистр

    //ЦЕЛОЧИСЛЕННАЯ АРИФМЕТИКА
    i_add = 4,                                  //Целочисленный плюс
    i_sub = 5,                                  //Минус
    i_mul = 6,                                  //Умножение
    i_div = 7,                                  //Деление
    remaind = 8,                                //Остаток от деления
    inc = 9,                                    //Инкремент
    dec = 10,                                   //Декремент

    log_and = 11,                               //Логическое И
    log_or = 12,                                //Логическое ИЛИ
    log_not = 13,                               //Логическое НЕ

    //ВЕЩЕСТВЕННАЯ АРИФМЕТИКА
    f_add = 14,                                 //Вещественный плюc
    f_sub = 15,                                 //Минус
    f_mul = 16,                                 //Умножение
    f_div = 17,                                 //Деление

    //ПЕРЕХОДЫ
    jmp = 18,                                   //Прямой безусловный переход
    jzf = 19,                                   //Если ZF = 1
    jnzf = 20,                                  //Если ZF = 0
    jsf = 21,                                   //Если SF = 1
    jnsf = 22,                                  //Если SF = 0


    io = 23,                                    //Здесь буду команды ввода/вывода
    call = 24,                                  //Переход к подпрограмме
    ret = 25,                                   //Возврат к программе
};
#endif // OPCODES_H
