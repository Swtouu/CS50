from cs50 import SQL
import csv
import os

# Get the current working directory
current_directory = os.getcwd()

# Define the file and database names
FILENAME = "students.csv"
DBNAME = "roster.db"

def main():
    students = list()

    # Open CSV
    try:
        with open(FILENAME, "r") as file:
            reader = csv.DictReader(file)

            for row in reader:
                students.append(row)
    except FileNotFoundError:
        print(f"The file {FILENAME} doesn't exist.")
        return 1

    # Open DB
    if os.path.exists(DBNAME):
        db = SQL(f"sqlite:///{DBNAME}")
    else:
        print(f"The path {DBNAME} does not exist.")
        return 2

    # Copy CSV to DB
    for student in students:
        db.execute("INSERT OR IGNORE INTO students (id, student_name) VALUES (:id, :student_name)",
                   id=student["id"], student_name=student["student_name"])
        db.execute("INSERT OR IGNORE INTO houses (house, head) VALUES (:house, :head)",
                   house=student["house"], head=student["head"])
        db.execute("INSERT OR IGNORE INTO assignments (student_id, house_id) VALUES (:student_id, :house_id)",
                   student_id=student["id"], house_id=student["house"])

if __name__ == "__main__":
    main()
