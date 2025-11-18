import xlsxwriter
import time

print("Welcome to the Multiplication Table Generator!")

def getMultiplicationTableSize():
    while True:
        try:
            numberToMultiply = float(input("Which number do you want to generate a multiplication table for? "))
            if numberToMultiply == 0:
                print("Please enter a number not equal to 0.")
                continue
        except ValueError:
            print("Invalid input. Please enter a valid number.")
            continue

        while True:
            try:
                tableSize = int(input("Up to which number do you want to multiply? "))
                if tableSize <= 0:
                    print("Please enter a positive integer greater than 0.")
                    continue
                return numberToMultiply, tableSize
            except ValueError:
                print("Invalid input. Please enter a valid integer.")

# Create workbook ONCE at the start
workbook = xlsxwriter.Workbook("MultiplicationTable.xlsx")

# Center alignment format
center_format = workbook.add_format({
    "align": "center",
    "valign": "vcenter"
})

sheet_count = 1  # Used to name sheets: Sheet1, Sheet2, etc.

while True:
    numberToMultiply, tableSize = getMultiplicationTableSize()

    # Create a new sheet for every table
    sheet_name = f"Table_{sheet_count}"
    sheet = workbook.add_worksheet(sheet_name)
    sheet_count += 1

    # Track column widths
    col_widths = [0, 0, 0, 0]

    for i in range(1, tableSize + 1):
        values = [
            str(numberToMultiply),
            "*",
            str(i),
            str(numberToMultiply * i)
        ]

        # Write values and update column width
        for col, value in enumerate(values):
            # Convert numeric-looking strings into float type
            if value.replace('.', '', 1).isdigit():
                sheet.write(i - 1, col, float(value), center_format)
            else:
                sheet.write(i - 1, col, value, center_format)

            col_widths[col] = max(col_widths[col], len(value))

    # Resize columns based on dynamic width
    for col, width in enumerate(col_widths):
        sheet.set_column(col, col, width + 2)

    print(f"\nCreated sheet '{sheet_name}' for {numberToMultiply} up to {tableSize}.")

    anotherTable = input("Do you want to generate another multiplication table? (yes/no): ").strip().lower()
    if anotherTable != 'yes':
        break

# Save workbook ON EXIT only
workbook.close()
print("All tables saved to 'MultiplicationTable.xlsx'. Goodbye!")