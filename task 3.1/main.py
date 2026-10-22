def validate_pin(entered_pin):
    correct_pin = 1234
    return entered_pin == correct_pin


def check_balance(balance, amount):
    return amount <= balance


def is_valid_multiple(amount):
    return amount % 500 == 0


def withdraw(balance, amount):
    return balance - amount


def format_receipt(account_holder, amount, new_balance):
    receipt = (
        "\n========== RECEIPT ==========\n"
        f"Account Holder : {account_holder}\n"
        f"Amount Withdrawn: {amount}\n"
        f"Remaining Balance: {new_balance}\n"
        "============================="
    )
    return receipt


def main():
    
    balance = 10000

    
    account_holder = input("Enter account holder name: ")
    pin = int(input("Enter PIN: "))
    amount = int(input("Enter withdrawal amount: "))

    if not validate_pin(pin):
        print("Invalid PIN.")
        return

    if not is_valid_multiple(amount):
        print("Withdrawal amount must be a multiple of 500.")
        return

    if not check_balance(balance, amount):
        print("Insufficient balance.")
        return

    new_balance = withdraw(balance, amount)

 
    receipt = format_receipt(account_holder, amount, new_balance)
    print(receipt)


if __name__ == "__main__":
    main()