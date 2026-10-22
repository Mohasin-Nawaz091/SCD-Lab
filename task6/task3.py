import re

date = input("Enter date (DD/MM/YYYY): ")

pattern = (
    r"(0[1-9]|[12]\d|3[01])/"
    r"(0[1-9]|1[0-2])/"
    r"[1-9]\d{3}"
)

if re.fullmatch(pattern, date):
    print("Valid")
else:
    print("Invalid")