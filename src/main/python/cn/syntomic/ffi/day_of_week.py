from datetime import datetime

def day_of_week(date):
    return datetime.strptime(date, "%Y-%d-%m").weekday() + 1

if __name__ == "__main__":
    print(day_of_week("1994-05-05"))
