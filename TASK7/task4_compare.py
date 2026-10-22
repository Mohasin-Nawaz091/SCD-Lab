
import json
import os
import yaml
import xml.etree.ElementTree as ET


students = [
    {"name": "Ali Khan", "age": 22, "gpa": 3.75},
    {"name": "Sara Ahmed", "age": 21, "gpa": 3.90},
    {"name": "John Doe", "age": 23, "gpa": 3.60}
]


with open("students.json", "w") as file:
    json.dump(students, file, indent=4)


with open("students.yaml", "w") as file:
    yaml.safe_dump(students, file, sort_keys=False)


root = ET.Element("students")

for student in students:
    student_element = ET.SubElement(root, "student")

    for key, value in student.items():
        field = ET.SubElement(student_element, key)
        field.text = str(value)

tree = ET.ElementTree(root)
ET.indent(tree, space="    ")
tree.write("students.xml", encoding="unicode",
           xml_declaration=False)


print("File Sizes:")

for filename in ["students.json", "students.xml", "students.yaml"]:
    print(f"{filename} size: {os.path.getsize(filename)} bytes")


def sum_gpa_row_based(student_list):
    total = 0

    for student in student_list:
        total += student["gpa"]

    return total

def sum_gpa_columnar(columns):
    return sum(columns["gpa"])


columns = {
    "name": [student["name"] for student in students],
    "age": [student["age"] for student in students],
    "gpa": [student["gpa"] for student in students]
}


row_sum = sum_gpa_row_based(students)
column_sum = sum_gpa_columnar(columns)

print("\nRow based GPA sum:", row_sum)
print("Columnar GPA sum:", column_sum)
print("Results match:", row_sum == column_sum)
