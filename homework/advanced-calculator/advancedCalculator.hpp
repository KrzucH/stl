#include <iostream>
#include <map>
#include <functional>
#include <cmath>
// Wszystkie komendy kalkulatora powinny być przechowywane w mapie, która jako klucz przechowuje znak `char` odwołujący się do konkretnej komendy (np. `+` -> dodaj , `%` -> modulo), a jako wartości `std::function<>` będące wraperem na wyrażenia lambda dokonujące określonej kalkulacji.

// Program powinien także zwracać odpowiedni kod błędu, jeżeli użytkownik poda złe dane. Np. dzielenie przez `0` lub spróbuje dodać `ala + 5`.

// * Input: `5 + 5` -> operacja dodawania dwóch liczb `5` i `5` -> output: `10`.
// * Input: `5 ^ 2` -> operacje potęgowania -> output `25`.
// * Input: `125 $ 3` -> operacja pierwiastka (sqrt za długie), pierwiastek sześcienny z `125` -> output: `5`.

// Zadanie dostarcz na gałąź [advanced-calculator](https://github.com/coders-school/stl/tree/advanced-calculator/homework/advanced-calculator).

// ___


enum class ErrorCode {
    OK,
    BadCharacter,
    BadFormat,
    DivideBy0,
    SqrtOfNegativeNumber,
    ModuleOfNonIntegerValue
};


ErrorCode process (std::string, double*);



