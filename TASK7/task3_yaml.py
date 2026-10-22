
import yaml
import json


# Load configuration from a YAML file
def load_config(filename):
    with open(filename, "r") as file:
        return yaml.safe_load(file)


# Convert YAML data into a JSON file
def yaml_to_json(yaml_filename, json_filename):
    config = load_config(yaml_filename)

    with open(json_filename, "w") as file:
        json.dump(config, file, indent=4)


# Load the configuration
config = load_config("config.yaml")

# Print configuration values
print("Debug mode:", config["debug"])
print("Minimum GPA:", config["min_gpa"])

# Print each student
print("\nStudents:")
for student in config["students"]:
    print(student)

# Confirm students is a list
print("\nType of students:", type(config["students"]))

# Convert YAML to JSON
yaml_to_json("config.yaml", "config_from_yaml.json")

print("\nJSON file created successfully.")
