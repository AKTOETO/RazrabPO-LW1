#include "action.h"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Использование: " << argv[0] << " <действие> число1 [число2] ..." << std::endl;
        return 1;
    }

    std::unique_ptr<IAction> action = createAction(argv[1]);

    if (!action)
    {
        std::cerr << "Ошибка: Неизвестное действие '" << argv[1] << "'. Используйте '+' или '-'." << std::endl;
        return 1;
    }

    double result = 0.0;
    try
    {
        result = std::stod(argv[2]);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Ошибка: '" << argv[2] << "' не является числом." << std::endl;
        return 1;
    }

    for (int i = 3; i < argc; ++i)
    {
        try
        {
            double num = std::stod(argv[i]);
            result = action->execute(result, num);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Предупреждение: '" << argv[i] << "' не является числом и будет проигнорирован." << std::endl;
        }
    }
    std::cout << "Результат: " << result << std::endl;

    return 0;
}