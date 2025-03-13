class NumberBase:
    """
    Абстрактный базовый класс для чисел.
    Определяет базовые операции, которые должны поддерживать подклассы.
    """
    def __init__(self, value: int):
        self._value = value
    
    def get_value(self) -> int:
        """Возвращает числовое значение."""
        return self._value
    
    def __call__(self) -> str:
        """Позволяет вызывать объект, возвращая строковое представление числа."""
        return str(self._value)
    
    def __add__(self, other: 'NumberBase') -> 'NumberBase':
        return self.__class__(self._value + other._value)
    
    def __sub__(self, other: 'NumberBase') -> 'NumberBase':
        if self._value - other._value <= 0:
            raise ValueError("Resulting value must be positive")
        return self.__class__(self._value - other._value)
    
    def __mul__(self, other: 'NumberBase') -> 'NumberBase':
        return self.__class__(self._value * other._value)
    
    def __truediv__(self, other: 'NumberBase') -> 'NumberBase':
        if other._value == 0:
            raise ZeroDivisionError("Cannot divide by zero")
        return self.__class__(self._value // other._value)


class Roman(NumberBase):
    """
    Класс для работы с римскими числами.
    Поддерживает преобразование, арифметические операции и строковое представление.
    """
    ROMAN_NUMERALS = {
        'I': 1, 'IV': 4, 'V': 5, 'IX': 9, 'X': 10, 'XL': 40, 'L': 50,
        'XC': 90, 'C': 100, 'CD': 400, 'D': 500, 'CM': 900, 'M': 1000
    }
    
    def __init__(self, value):
        """
        Инициализация объекта Roman.
        :param value: Либо строка римского числа, либо целое число.
        """
        if isinstance(value, str):
            super().__init__(self.roman_to_int(value))
        elif isinstance(value, int):
            super().__init__(value)
        else:
            raise ValueError("Invalid value type")
    
    @staticmethod
    def roman_to_int(roman: str) -> int:
        """Преобразование римского числа в арабское."""
        result, i = 0, 0
        roman = roman.upper()
        while i < len(roman):
            if i + 1 < len(roman) and roman[i:i+2] in Roman.ROMAN_NUMERALS:
                result += Roman.ROMAN_NUMERALS[roman[i:i+2]]
                i += 2
            else:
                result += Roman.ROMAN_NUMERALS[roman[i]]
                i += 1
        return result
    
    @staticmethod
    def int_to_roman(number: int) -> str:
        """Преобразование арабского числа в римское."""
        result = ""
        for roman, value in sorted(Roman.ROMAN_NUMERALS.items(), key=lambda x: -x[1]):
            while number >= value:
                result += roman
                number -= value
        return result
    
    def __call__(self) -> str:
        """Позволяет вызывать объект, возвращая римское число в строке."""
        return self.int_to_roman(self._value)
    
    def __str__(self) -> str:
        """Строковое представление римского числа."""
        return self.int_to_roman(self._value)


# Пример использования
if __name__ == "__main__":
    a = Roman("X")  # 10
    b = Roman("IV")  # 4
    
    print(f"{a} + {b} = {a + b}")  # X + IV = XIV (10 + 4 = 14)
    print(f"{a} - {b} = {a - b}")  # X - IV = VI (10 - 4 = 6)
    print(f"{a} * {b} = {a * b}")  # X * IV = XL (10 * 4 = 40)
    print(f"{a} / {b} = {a / b}")  # X / IV = II (10 // 4 = 2)
    
    # Вызов объекта как функции(__call__)
    print(f"Вызов объекта: {a()}")
