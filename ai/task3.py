
def fruit_basket():
    banana = "banana"
    apple = "apple"
    cherry = "cherry"

    items = [banana, apple, cherry]

    rejected = ["big", "attractive", "big", "tasty"]

    fruit = ["apple", "banana", "cherry"]
    quantity = [5, 4, 3]

    
    for f in fruit:
        for r in rejected:
            print(r, f)


    for i in range(len(fruit)):
        if fruit[i] == "apple":
            print("Quantity of apple:", quantity[i])


fruit_basket()