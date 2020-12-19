#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Processor.h"

bool loader(const std::string& filename, Processor& cpu)        //Загрузчик
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string str;
    char teg;                                                   //Наши обозначения: начало команды, запоминаем IP и т.д.
    uint16_t adr = 0;                                           //Начальный адрес записи
    datatype16 type16;
    datatype32 type32;
    file >> str;
    if (str[0] != 'a')                                          //Если не прописали адрес записи - вылет программы
    {
        std::cout << "\nerror a!\n";
        return false;
    }
    else
    {
        file >> str;
        adr = (uint16_t)std::stoi(str);                         //Запоминаем адрес записи
        std::getline(file, str);                                //Пропускаем комментарий
        while (!file.eof())                                     //Пока не конец файла
        {
            //Новая строка кода
            file >> str;
            teg = str[0];
            switch (teg)
            {
            case 's':                                           //Если запоминаем IP...
            {
                file >> str;
                cpu.psw.setIP((uint16_t)std::atoi(str.c_str()));
                std::getline(file, str);                        //Пропускаем комментарии
                break;
            }

            case 'c':                                           //Команда
            {
                file >> str;
                for (std::size_t i = 0; i < 4; i++)             //т.к. как минимум 4 составляющих
                {
                    switch (i)
                    {
                    case 0:
                        type16.command16.KOP = std::atoi(str.c_str()); break;   //КОП
                    case 1:
                        type16.command16.s = std::atoi(str.c_str()); break;     //Размер операндов
                    case 2:
                        type16.command16.r1 = std::atoi(str.c_str()); break;    //Первый операнд
                    case 3:
                        type16.command16.r2 = std::atoi(str.c_str());           //Второй операнд
                    }
                    file >> str;
                }
                cpu.memory.load(type16, adr);                                   //Запоминаем наше 16-битное чудовище в память по адресу...
                adr++;                                                          //Увеличиваем адрес
                if (str[0] != ';')                      //НО! Есть еще смещение. Если следующее слово - не начало комментария, значит, наткнулись на смещение
                {
                    type16.w16.i16 = (int16_t)std::stoi(str);
                    cpu.memory.load(type16, adr);
                    adr++;                                                      //Увеличиваем адрес
                }
                std::getline(file, str);                                        //Теперь уж точно пропускаем комментарий
                break;
            }

            case 'i':                                                           //Знаковые и беззнаковые числа в 16 бит
            {
                file >> str;
                type16.w16.i16 = (int16_t)std::stoi(str);
                cpu.memory.load(type16, adr);
                adr++;
                std::getline(file, str);
                break;
            }

            case 'I':                                                           //Знаковые и беззнаковые числа в 32 бита
            {
                file >> str;
                type32.w32.i32 = std::stoi(str);
                cpu.memory.load(type32, adr);
                adr += 2;
                std::getline(file, str);
                break;
            }

            case 'f':                                                           //Вещественные числа
            {
                file >> str;
                type32.w32.f = std::stof(str);
                cpu.memory.load(type32, adr);
                adr += 2;
                std::getline(file, str);
                break;
            }

            default:                                                            //Если ничего подобного не встретилось - ошибка!
            {
                std::cout << "\nerror ind!\n";
                return false;
            }
            }
            std::cout << adr;
        }
    }
    file.close();
    return true;
}


int main()
{
    setlocale(0, "rus");
    std::cout << "   Курсовая работа по дисциплине Архитектура вычислительных систем.\n";
    std::cout << "         VM5. Двухадресная, с РОН, один операнд в регистре.\n";
    std::cout << "   Работу выполнила студентка АГТУ ДИПРб-21/1 Ефремова Анастасия.\n";

    Processor cpu;
    std::cout << "\nФайл: prog.txt\n";
    if (loader("prog.txt", cpu))
    {
        std::cout << "Загрузка прошла успешно.\n";
        cpu.run();
        std::cout << "Программа успешно выполнена.\n";
    }
    else std::cout << "Не удалось загрузить файл.\n";
    system("pause");

    return 0;
}
