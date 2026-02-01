# Employee Shift Scheduler

## Overview
This is a small command-line application for managing employee schedules at a company that operates 7 days a week. Employees can select their preferred shifts (morning, afternoon, evening) for each day. The program automatically generates a weekly schedule that ensures:

- No employee works more than one shift per day.  
- No employee works more than 5 days per week.  
- Each shift has at least 2 employees. If insufficient employees are available, additional employees are randomly assigned.  
- Conflicts between employee preferences and shift availability are detected and resolved automatically.  

Two implementations are provided: Python and C++.

---

## Features
- Interactive CLI input for employee names and shift preferences.  
- Automatic conflict resolution and random assignment for underfilled shifts.  
- Weekly scheduling output in a readable format.  
- Constraints enforcement: max 5 working days per employee, max 1 shift per day, minimum 2 employees per shift.  
- Extensible code structure for future enhancements (priority-based preferences, file input/output, GUI).  

---

## Requirements

### Python Version
- Python 3.6+  
- Standard Python libraries: `argparse`, `random`, `sys`  

### C++ Version
- C++11 compatible compiler (e.g., `g++`)  
- Standard C++ libraries  

---

## Usage

### Python Version
1. Save the file as `schedule.py`.  
2. Run the program with employee names as CLI arguments:

```bash
# Python
python3 employee_scheduling.py --employees Sam Trent 

# C++
g++ -std=c++11 -o schedule scheduling_cplusplus.cpp
./schedule Sam Trent
