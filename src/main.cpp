#include "action.h"
#include <iostream>
#include <memory>
#include <string>
#include <pqxx/pqxx>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Использование: " << argv[0] << " <действие> число1 [число2] ..." << std::endl;
        return 1;
    }

    std::string input = argv[1], output;

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

    input += argv[2];

    for (int i = 3; i < argc; ++i)
    {
        input += std::string(" ") + argv[i];
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
    output = std::to_string(result);

    try {
        pqxx::connection C("dbname=postgres user=postgres password=2811 host=localhost port=5432");
        if (C.is_open()) {
            std::cout << "Successfully connected to the database: " << C.dbname() << std::endl;
        } else {
            std::cout << "Failed to connect to the database." << std::endl;
            return 1;
        }

        pqxx::work W(C);

        std::string sql = "INSERT INTO public.history (input, output) VALUES ($1, $2)";

        W.exec(pqxx::zview{sql}, pqxx::params{input, output});

        W.commit();

        std::cout << "Data successfully inserted into the database." << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}