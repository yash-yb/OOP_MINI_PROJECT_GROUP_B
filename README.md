# Student Report Card System

A console-based **Student Report Card System** written in **C++**. The program stores student records in a CSV file and provides options to add, search, view, edit, and delete student information.

## Features

- **Add student:** Enter a roll number, name, age, and one or more subjects with marks.
- **Prevent duplicate roll numbers:** A new record is rejected if its roll number already exists.
- **Search student:** Find a student using their roll number.
- **View student report:** Display the student's personal details, subject-wise marks, and calculated average.
- **Edit student:** Update the student's name, age, a subject name, or subject marks.
- **Delete student:** Remove a selected student record.
- **View all students:** Display every saved student's roll number, name, and average marks.
- **Persistent storage:** Save records in `students.csv`, so data remains available after the program exits.
- **Basic validation:** Check age, number of subjects, marks, subject positions, and menu choices.

## Technologies and concepts

- Language: C++
- Standard library: `iostream`, `vector`, `fstream`, `string`, `sstream`, and `limits`
- Object-oriented programming: classes, inheritance, encapsulation, member functions, and static functions
- File handling: reading from and writing to a CSV file
- Exception handling: `throw` and `try`/`catch`
- STL containers: `vector`

## Project structure

```text
Student-Report-Card-System/
├── main.cpp
├── README.md
└── students.csv       # Created/updated when records are saved
```

The source code is contained in `main.cpp`. The CSV file is created in the program's **current working directory** when the first save occurs.

## How to compile and run

You need a C++ compiler such as `g++`.

```bash
g++ -std=c++11 main.cpp -o student_report
./student_report
```

On Windows with MinGW:

```bash
g++ -std=c++11 main.cpp -o student_report.exe
student_report.exe
```

## How to use

After starting the program, select an option from the main menu:

| Option | Operation |
|---|---|
| 1 | Add Student |
| 2 | Search Student Details |
| 3 | Get All Students |
| 4 | Exit |

When searching for a student, enter the roll number. The program displays the record and offers options to edit it, delete it, or return to the main menu.

When adding a student, enter the number of subjects and then provide each subject name and its marks. Marks must be between 0 and 100, inclusive.

## Average calculation

The average is calculated using:

\[
\text{Average} = \frac{\text{Sum of subject marks}}{\text{Number of subjects}}
\]

The calculation is performed by the `average()` member function.

## Data storage format

Each student is stored as one line in `students.csv`, using this field order:

```text
roll_number,name,age,number_of_subjects,subject_1,marks_1,subject_2,marks_2,...
```

Example:

```csv
CS101,Aarav,19,3,Mathematics,85,Physics,78,Programming,92
```

The program reads all records into a `vector<student_details>`, changes the in-memory collection, and writes the collection back to the CSV file when a record is added, edited, or deleted.

## Main classes

### `person`

A base class containing the protected data members `name` and `age`.

### `student_details`

Inherits from `person` and stores:
- `rollno` — student's roll number
- `marks` — vector of subject marks
- `sub_name` — vector of subject names

The class also contains functions for input, display, editing, average calculation, CSV loading/saving, and student record operations.

## Important implementation notes and limitations

- The CSV handling is a simple comma-separated format. Names and subject names containing commas are not escaped or quoted, so such values can break the record format.
- The program expects `students.csv` to contain records in the format described above. It does not implement a CSV parser for quoted fields.
- The source code validates several user inputs, but malformed numeric input during some edit operations may still leave the input stream in a failed state.
- The program does not currently provide sorting, subject-level grade classification, password protection, or a graphical interface.
- The CSV file is rewritten when records are saved. Keep a backup if the records are important.

## Future enhancements

- Use a proper CSV escaping/parsing approach or a database such as SQLite.
- Add stronger validation and recovery for every numeric input.
- Add sorting, filtering, and grade/percentage classification.
- Add export and print-friendly report generation.
- Separate declarations, implementation, and program entry point into multiple source files.

## License

No license has been specified for this project.
