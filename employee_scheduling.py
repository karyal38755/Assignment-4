import argparse
import random

DAYS = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
SHIFTS = ["morning", "afternoon", "evening"]

class Employee:
    def __init__(self, name):
        self.name = name
        self.days_worked = 0
        self.assigned = {d: None for d in DAYS}

def empty_schedule():
    return {d: {s: [] for s in SHIFTS} for d in DAYS}

def collect_employees(names):
    return [Employee(n) for n in names]

def collect_preferences(employees):
    prefs = {}
    for e in employees:
        prefs[e.name] = {}
        print(f"preferences for {e.name}")
        for d in DAYS:
            s = input(f"{d} shift (morning afternoon evening or enter): ").strip()
            if s in SHIFTS:
                prefs[e.name][d] = s
    return prefs

def assign_preferences(employees, prefs, schedule):
    for e in employees:
        for day, shift in prefs.get(e.name, {}).items():
            if e.days_worked >= 5:
                continue
            if e.assigned[day] is not None:
                continue
            if len(schedule[day][shift]) < 2:
                schedule[day][shift].append(e.name)
                e.assigned[day] = shift
                e.days_worked += 1

def resolve_conflicts(employees, schedule):
    for e in employees:
        for d in DAYS:
            if e.assigned[d] is not None or e.days_worked >= 5:
                continue
            for s in SHIFTS:
                if len(schedule[d][s]) < 2:
                    schedule[d][s].append(e.name)
                    e.assigned[d] = s
                    e.days_worked += 1
                    break

def fill_shifts(employees, schedule):
    for d in DAYS:
        for s in SHIFTS:
            while len(schedule[d][s]) < 2:
                candidates = [
                    e for e in employees
                    if e.days_worked < 5 and e.assigned[d] is None
                ]
                if not candidates:
                    break
                chosen = random.choice(candidates)
                schedule[d][s].append(chosen.name)
                chosen.assigned[d] = s
                chosen.days_worked += 1

def print_schedule(schedule):
    for d in DAYS:
        print(d)
        for s in SHIFTS:
            print(" ", s, ":", schedule[d][s])
        print()

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--employees",
        nargs="+",
        required=True,
        help="list of employee names"
    )
    args = parser.parse_args()

    employees = collect_employees(args.employees)
    prefs = collect_preferences(employees)

    schedule = empty_schedule()
    assign_preferences(employees, prefs, schedule)
    resolve_conflicts(employees, schedule)
    fill_shifts(employees, schedule)
    print_schedule(schedule)

if __name__ == "__main__":
    main()
