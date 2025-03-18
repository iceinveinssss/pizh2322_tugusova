class Pizza:
    """
    Базовый класс для представления пиццы.
    """
    def __init__(self, name: str, dough: str, sauce: str, toppings: list[str]):
        """
        Атрибуты:
            name (str): Название пиццы.
            dough (str): Тип теста.
            sauce (str): Тип соуса.
            toppings (list[str]): Список начинок.
        """
        self.name = name
        self.dough = dough
        self.sauce = sauce
        self.toppings = toppings

    def prepare(self) -> None:
        """Подготовка пиццы: замес теста, сбор ингредиентов."""
        print(f"Подготовка {self.name}: замес теста {self.dough}, добавление соуса {self.sauce} и начинок {', '.join(self.toppings)}.")

    def bake(self) -> None:
        """Выпечка пиццы."""
        print(f"Выпечка {self.name}")

    def cut(self) -> None:
        """Нарезка пиццы."""
        print(f"Нарезка {self.name}")

    def pack(self) -> None:
        """Упаковка пиццы."""
        print(f"Упаковка {self.name}")

class PepperoniPizza(Pizza):
    """Класс для представления пиццы Пепперони."""
    def __init__(self):
        super().__init__("Пепперони", "тонкое тесто", "томатный соус", ["пепперони", "сыр моцарелла"])

class BarbecuePizza(Pizza):
    """Класс для представления пиццы Барбекю."""
    def __init__(self):
        super().__init__("Барбекю", "толстое тесто", "барбекю соус", ["курица", "лук", "сыр моцарелла"])

class SeafoodPizza(Pizza):
    """Класс для представления пиццы Дары Моря."""
    def __init__(self):
        super().__init__("Дары Моря", "тонкое тесто", "сливочный соус", ["креветки", "мидии", "сыр моцарелла"])

class Order:
    """
    Класс для представления заказа.
    """
    def __init__(self):
        self.items: list[Pizza] = []

    def add_item(self, pizza: Pizza) -> None:
        """Добавление пиццы в заказ."""
        self.items.append(pizza)

    def calculate_total(self) -> float:
        """Расчет общей стоимости заказа."""
        return len(self.items) * 10  # Примерная стоимость каждой пиццы

    def display_order(self) -> None:
        """Отображение информации о заказе."""
        print("Ваш заказ:")
        for pizza in self.items:
            print(f"- {pizza.name}")
        print(f"Общая стоимость: {self.calculate_total()} руб.")

class Terminal:
    """
    Класс для взаимодействия с пользователем через терминал.
    """
    def __init__(self):
        self.menu: dict[int, Pizza] = {
            1: PepperoniPizza(),
            2: BarbecuePizza(),
            3: SeafoodPizza()
        }

    def display_menu(self) -> None:
        """Отображение меню на экране."""
        print("Меню:")
        for key, pizza in self.menu.items():
            print(f"{key}. {pizza.name}")

    def take_order(self) -> Order:
        """Прием заказа от пользователя."""
        order = Order()
        while True:
            self.display_menu()
            choice = input("Выберите номер пиццы (или 'готово' для завершения): ")
            if choice.lower() == 'готово':
                break
            try:
                pizza = self.menu[int(choice)]
                order.add_item(pizza)
                print(f"{pizza.name} добавлена в заказ.")
            except (KeyError, ValueError):
                print("Неверный выбор. Пожалуйста, попробуйте еще раз.")
        return order

    def process_payment(self, amount: float) -> bool:
        """Обработка оплаты."""
        print(f"Оплата {amount} руб.")
        return True  # В реальной системе здесь будет логика обработки платежа

    def complete_order(self, order: Order) -> None:
        """Завершение заказа и передача на выполнение."""
        order.display_order()
        if self.process_payment(order.calculate_total()):
            for pizza in order.items:
                pizza.prepare()
                pizza.bake()
                pizza.cut()
                pizza.pack()
            print("Заказ готов! Спасибо за покупку.")

# Пример использования
if __name__ == "__main__":
    terminal = Terminal()
    order = terminal.take_order()
    terminal.complete_order(order)