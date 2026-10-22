import re

password = input("Enter your password: ")

pattern = r'^(?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[!@#$%^&*]).{8,}$'

if re.match(pattern, password):
    print("Valid")
else:
    print("Invalid")