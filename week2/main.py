class SnowBase:
    """
    Базовый класс для снежинок (абстракция).
    Определяет базовые свойства и методы.
    """
    def __init__(self, count: int) -> None:
        self._count = max(0, count)  # Инкапсуляция: защищённый атрибут
    
    def get_count(self) -> int:
        """Возвращает текущее количество снежинок."""
        return self._count
    
    def set_count(self, value: int) -> None:
        """Устанавливает количество снежинок (не меньше 0)."""
        self._count = max(0, value)
    
    def __call__(self) -> str:
        """Позволяет вызвать объект как функцию, возвращая строку с количеством снежинок."""
        return f"Количество снежинок: {self._count}"


class Snow(SnowBase):
    """
    Класс для работы со снежинками.
    Реализует арифметические операции и визуализацию снежинок.
    """
    def __add__(self, other: int) -> 'Snow':
        return Snow(self._count + other)

    def __sub__(self, other: int) -> 'Snow':
        return Snow(max(0, self._count - other))

    def __mul__(self, other: int) -> 'Snow':
        return Snow(self._count * other)

    def __truediv__(self, other: int) -> 'Snow':
        return Snow(max(1, self._count // other))
    
    def makeSnow(self, snowflakes_per_row: int) -> str:
        """
        Формирует снежинки в ряды.
        :param snowflakes_per_row: Количество снежинок в одном ряду.
        :return: Строковое представление снежинок.
        """
        result = "".join('*' * min(snowflakes_per_row, self._count - i) + '\n' 
                          for i in range(0, self._count, snowflakes_per_row))
        return result.strip()


# Пример использования
snow = Snow(12)
print(snow.makeSnow(3))  # Отобразить снежинки по 3 в ряду

# Демонстрация перегрузки операторов
snow = snow + 3
print("\nПосле добавления снежинок:")
print(snow.makeSnow(4))

snow = snow - 5
print("\nПосле удаления снежинок:")
print(snow.makeSnow(3))

snow = snow * 2
print("\nПосле удвоения снежинок:")
print(snow.makeSnow(6))

snow = snow / 3
print("\nПосле деления количества снежинок на 3:")
print(snow.makeSnow(4))

# Вызов объекта как функции(__call__)
print("\nВызов объекта:")
print(snow())
