def format_float_return(func):
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        if isinstance(result, float):
            return round(result, 2)
        return result
    return wrapper

# Пример использования
@format_float_return
def get_price():
    return 123.4567  # Будет округлено до 123.46

@format_float_return
def get_name():
    return "Python"  # Не изменится

print(get_price())  # Выведет: 123.46
print(get_name())   # Выведет: Python
