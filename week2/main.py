class Snow:
    count: int  # Количество снежинок

    def __init__(self, count: int) -> None:
        self.count = count  # Инициализация количества снежинок

    # Перегрузка операторов
    def __add__(self, other: int) -> 'Snow':
        return Snow(self.count + other)

    def __sub__(self, other: int) -> 'Snow':
        return Snow(max(0, self.count - other))  # Количество не может быть отрицательным

    def __mul__(self, other: int) -> 'Snow':
        return Snow(self.count * other)

    def __truediv__(self, other: int) -> 'Snow':
        return Snow(max(1, self.count // other))  # Минимум 1 снежинка

    def makeSnow(self, snowflakes_per_row: int) -> str:
        result = ""  # Создаём пустую строку для хранения снежинок
        i = 0  # Счётчик для отслеживания текущей позиции снежинок
    
        # Цикл продолжается, пока количество добавленных снежинок меньше общего числа
        while i < self.count:
            # Создаём строку снежинок:
            # Берём минимум из снежинок на ряд или оставшихся снежинок
            row = '*' * min(snowflakes_per_row, self.count - i)
    
            # Добавляем строку снежинок и символ переноса строки
            result += row + '\n'
    
            # Увеличиваем счётчик на количество снежинок в одном ряду
            i += snowflakes_per_row
    
        # Убираем лишний перенос строки в конце строки перед возвратом
        return result.strip()



# Пример использования
snow: Snow = Snow(12)
print(snow.makeSnow(3))  # Отобразить снежинки по 5 в ряду

# Демонстрация перегрузки операторов
snow = snow + 3
print("\nПосле добавления снежинок:\n", snow.makeSnow(4))

snow = snow - 5
print("\nПосле удаления снежинок:\n", snow.makeSnow(3))

snow = snow * 2
print("\nПосле удвоения снежинок:\n", snow.makeSnow(6))

snow = snow / 3
print("\nПосле деления количества снежинок на 3:\n", snow.makeSnow(4))
