class Food:
    def __init__(self, name: str):
        self.food_name = name
        self.complete = False

class Customer:
    def __init__(self, customer_name: str):
        self._customer_name = customer_name

    def place_order(self, food_name: str) -> Food:
        return Food(food_name)

class Employee:
    def __init__(self, employee_name: str):
        self._employee_name = employee_name

    def take_order(self, food: Food) -> None:
        food.complete = True

class Lunch:
    def __init__(self, customer: Customer, employee: Employee):
        self._customer = customer
        self._employee = employee
        self._orders: list[Food] = []

    def order(self, name: str):
        food = self._customer.place_order(name)
        self._orders.append(food)
        self._employee.take_order(food)

    def result(self) -> list[Food]:
        return self._orders
    
def main():
    customer = Customer('Yui')
    employee = Employee('KFC')
    lunch = Lunch(customer, employee)
    while True:
        print('''
订餐系统：
1. 订餐
2. 查看所有
q. 退出
        '''.strip())
        choice = input('请选择功能: ')
        if choice == 'q':
            break
        elif choice == '1':
            name = input('请输入食物名称: ')
            lunch.order(name)
        elif choice == '2':
            for i in lunch.result():
                print(i.food_name)

if __name__ == '__main__':
    main()
