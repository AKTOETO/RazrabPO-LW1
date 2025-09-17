#ifndef ACTIONS_H
#define ACTIONS_H

#include <memory>
#include <string>

// Интерфейс для всех математических действий
class IAction
{
  public:
    virtual ~IAction() = default;
    virtual double execute(double current_result, double next_value) const = 0;
};

class AdditionAction : public IAction
{
  public:
    double execute(double current_result, double next_value) const override;
};

class SubtractionAction : public IAction
{
  public:
    double execute(double current_result, double next_value) const override;
};

// Фабрика для создания нужного объекта действия на основе символа операции.
std::unique_ptr<IAction> createAction(const std::string &operation_symbol);

#endif // ACTIONS_H