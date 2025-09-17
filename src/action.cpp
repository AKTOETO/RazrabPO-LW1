#include "action.h"

double AdditionAction::execute(double current_result, double next_value) const
{
    return current_result + next_value;
}

double SubtractionAction::execute(double current_result, double next_value) const
{
    return current_result - next_value;
}

std::unique_ptr<IAction> createAction(const std::string &operation_symbol)
{
    if (operation_symbol == "+")
    {
        return std::make_unique<AdditionAction>();
    }
    if (operation_symbol == "-")
    {
        return std::make_unique<SubtractionAction>();
    }
    return nullptr;
}