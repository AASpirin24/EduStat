# Project description

The system is designed as a modular C++ application. The source code is split into header files and implementation files. Data is stored in a separate CSV file, and logs are stored in a dedicated logs folder.

## Main classes

- `Student`: stores personal information and grades, calculates average recursively.
- `GradeManager`: manages the collection of students and implements search, sorting, and class average logic.
- `FileStorage`: loads and saves student data using CSV format.
- `Statistics`: calculates statistical summaries.
- `InputValidator`: validates names, groups, grades, and user input.
- `Logger`: writes application events to a log file.
- `Menu`: provides the console GUI-style interface.

## Recursive calculation

The recursive average for a student is implemented by summing grades through a helper function that calls itself until it reaches the end of the grade vector.

The recursive class average repeats the same concept over the collection of students.
