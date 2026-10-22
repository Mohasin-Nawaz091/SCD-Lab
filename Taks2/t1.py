shopping_list = {}

while True:
    item = input("Enter item name (or 'done' to finish): ").strip()

    if item.lower() == "done":
        break

    if not item:
        print("Item name cannot be empty.")
        continue

    try:
        quantity = int(input("Enter quantity: "))

        if quantity <= 0:
            print("Quantity must be greater than 0.")
            continue

    except ValueError:
        print("Please enter a valid number.")
        continue

    if item in shopping_list:
        shopping_list[item] += quantity
    else:
        shopping_list[item] = quantity

print("\nFinal Shopping List:")
for item, quantity in shopping_list.items():
    print(f"{item}: {quantity}")