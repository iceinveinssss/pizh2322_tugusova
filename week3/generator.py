numbers = [1, 3, 4, 6, 9, 11]

result = sum(x**2 for x in numbers if x % 3 == 0)

print(result)  # Выведет: 126
