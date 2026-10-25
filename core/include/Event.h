#pragma once
#include <string>

// Базовый класс для всех событий в системе
class Event {
private:
    std::string type; 

public:
    // explicit запрещает неявное преобразование строки в Event
    // Теперь нельзя случайно передать просто "Motion" туда, где нужен объект Event
    explicit Event(std::string eventType) : type(std::move(eventType)) {}
    
    // virtual деструктор ОБЯЗАТЕЛЕН для базовых классов
    // Он гарантирует, что при удалении наследника через указатель на Event
    // вызовется и деструктор наследника (иначе будет утечка памяти).
    virtual ~Event() = default;
    
    // Геттер для чтения типа события
    std::string getType() const { return type; }
};