class Food:
    def __init__(self, name: str):
        self.food_name = name

class Customer:
    def place_order(self):
        pass

class Employee:
    def take_order(self) -> Food:
        return Food('hamburger')

class Lunch:
    def __init__(self, customer: Customer, employee: Employee):
        self._customer = customer
        self._employee = employee
        self._orders: list[str] = []

    def order(self, name: str):
        self._customer.place_order()
        food = self._employee.take_order()
        self._orders.append(food)

    def result(self) -> list[str]:
        return self._orders
    
