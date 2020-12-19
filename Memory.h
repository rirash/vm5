#ifndef MEMORY_H
#define MEMORY_H
#include "Struct.h"
class Memory
{
private:
    datatype16* memory;                                                                 //Память состоит из слов (16-битная команда или же 16-битная переменная)
public:
    Memory() { memory = new datatype16[65536]; }
    Memory(Memory&) = delete;
    Memory operator = (Memory&) = delete;

    ~Memory() { delete[] memory; }

    //Загрузка в память двух видов типов данных
    void load(const datatype16& elem, uint16_t adr) noexcept 
    { 
        memory[adr].w16 = elem.w16; 
    }
    void load(const datatype32& elem, uint16_t adr) noexcept
    {
        memory[adr].w16 = elem.t16[0];
        memory[adr + 1].w16 = elem.t16[1];
    }

    int16_t get_int16(uint16_t adr) const noexcept { return memory[adr].w16.i16; }      //Получаем целое знаковое 16-битное значение из памяти
    uint16_t get_uint16(uint16_t adr) const noexcept { return memory[adr].w16.ui16; }   //Получаем целое беззнаковое 16-битное значение из памяти
    int32_t get_int32(uint16_t adr) const noexcept                                      //Получаем целое знаковое 32-битное значение из памяти
    {
        datatype32 t32;
        t32.t16[0] = memory[adr].w16;
        t32.t16[1] = memory[adr + 1].w16;
        return t32.w32.i32;
    }
    uint32_t get_uint32(uint16_t adr) const noexcept                                    //Получаем целое беззнаковое 32-битное значение из памяти
    {
        datatype32 t32;
        t32.w32.i32 = get_int32(adr);
        return t32.w32.ui32;
    }
    float get_float(uint16_t adr) const noexcept                                        //Получаем вещественное значение из памяти
    {
        datatype32 t32;
        t32.w32.i32 = get_int32(adr);
        return t32.w32.f;
    }
};
#endif // MEMORY_H
