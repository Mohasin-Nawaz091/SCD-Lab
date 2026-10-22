inventory_list = []

while True:
    user_input = input("Enter an item (or 'done' to finish): ").strip().lower()

    if user_input == "done":
        break

    if not user_input:
        print("Empty input is not allowed.")
        continue

    if user_input.startswith("remove "):
        item_to_remove = user_input[7:].strip()

        if item_to_remove in inventory_list:
            inventory_list.remove(item_to_remove)
            print(f"'{item_to_remove}' removed successfully.")
        else:
            print(f"'{item_to_remove}' was not found in the inventory.")

    elif user_input in inventory_list:
        print(f"'{user_input}' already exists. Duplicate not added.")

    else:
        inventory_list.append(user_input)
        print(f"'{user_input}' added successfully.")


inventory_list.sort()

total_item_count = len(inventory_list)

print("\nFinal Inventory")
print("----------------")
print(f"Total items: {total_item_count}")

for item in inventory_list:
    print(f"- {item}")