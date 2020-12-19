#ifndef STRUCT_H
#define STRUCT_H
#include <cinttypes>

union word16                    //Данные в 16 битов
{
    int16_t i16;                //Целое знаковое
    uint16_t ui16;              //Целое беззнаковое
};

union word32                    //Данные в 32 бита
{
    int32_t i32;                //Целое знаковое
    uint32_t ui32;              //Целое беззнаковое
    float f;                    //Вещественное
};

struct cmd16                    //Команда в 16 битов
{
    int KOP : 7;            //Код операции
    int s : 1;              //Размер операнда
    int r1 : 4;             //Первый операнд
    int r2 : 4;             //Второй операнд
};

struct cmd32                    //Команда в 32 бита
{
    cmd16 command16;            //Команда в 16 битов
    uint16_t off;               //Смещение
};

union datatype16               //16-битное число
{
    word16 w16;                 //Слово
    cmd16 command16;            //Команда к нему
};

struct datatype32                //32-битное число
{
    word32 w32;                 //Двойное слово
    word16 t16[2];
    cmd32 command32;
};

union ROH
{
    word16 w16[2];
    word32 w32;
};
#endif // STRUCT_H
