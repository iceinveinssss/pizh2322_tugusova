class Roman:
    # Словарь соответствий римских цифр и их значений
    ROMAN_NUMERALS = {
        'I': 1, 'IV': 4, 'V': 5, 'IX': 9, 'X': 10, 'XL': 40, 'L': 50,
        'XC': 90, 'C': 100, 'CD': 400, 'D': 500, 'CM': 900, 'M': 1000
    }
    
    def __init__(self, value):
        """
        Инициализация объекта Roman.
        Принимает либо строку римского числа, либо целое число.
        """
        if isinstance(value, str):
            self.value = self.roman_to_int(value)  # Конвертация из римского в арабское число
        elif isinstance(value, int):
            self.value = value  # Использование уже готового числа
        else:
            raise ValueError("Invalid value type")
    
    @staticmethod
    def roman_to_int(roman):
        #Преобразование римского числа в арабское.
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
    def int_to_roman(number):
        #Преобразование арабского числа в римское.

        result = ""
        for roman, value in sorted(Roman.ROMAN_NUMERALS.items(), key=lambda x: -x[1]):
            while number >= value:
                result += roman
                number -= value
        return result
    
    def __add__(self, other):
        #Оператор сложения для римских чисел.
        return Roman(self.value + other.value)
    
    def __sub__(self, other):
        """
        Оператор вычитания для римских чисел.
        Не допускает отрицательных значений.
        """
        if self.value - other.value <= 0:
            raise ValueError("Resulting value must be positive")
        return Roman(self.value - other.value)
    
    def __mul__(self, other):
        #Оператор умножения для римских чисел.
        return Roman(self.value * other.value)
    
    def __truediv__(self, other):
        #Оператор целочисленного деления для римских чисел.
        if other.value == 0:
            raise ZeroDivisionError("Cannot divide by zero")
        return Roman(self.value // other.value)
    
    def __str__(self):
        #Возвращает строковое представление римского числа.
        return self.int_to_roman(self.value)
    
# Пример использования
if __name__ == "__main__":
    a = Roman("X")  # 10
    b = Roman("IV")  # 4
    
    print(f"{a} + {b} = {a + b}")  # X + IV = XIV (10 + 4 = 14)
    print(f"{a} - {b} = {a - b}")  # X - IV = VI (10 - 4 = 6)
    print(f"{a} * {b} = {a * b}")  # X * IV = XL (10 * 4 = 40)
    print(f"{a} / {b} = {a / b}")  # X / IV = II (10 // 4 = 2)
