import re
from collections import Counter

input_string = """
IR1: 72
IR2: 1001
IR3: 76
IR4: 995
IR1: 72
IR2: 1001
IR3: 93
IR4: 995
IR1: 73
IR2: 1001
IR3: 84
IR4: 994
IR1: 76
IR2: 1002
IR3: 84
IR4: 995
IR1: 73
IR2: 1002
IR3: 75
IR4: 994
IR1: 84
IR2: 1002
IR3: 88
IR4: 995
IR1: 72
IR2: 1001
IR3: 77
IR4: 993
IR1: 72
IR2: 1002
IR3: 77
IR4: 991
IR1: 82
IR2: 1001
IR3: 85
IR4: 995
IR1: 71
IR2: 1001
IR3: 78
IR4: 994
IR1: 80
IR2: 1002
IR3: 84
IR4: 995
IR1: 80
IR2: 1001
IR3: 84
IR4: 995
IR1: 70
IR2: 1001
IR3: 88
IR4: 993
IR1: 74
IR2: 1002
IR3: 84
IR4: 994
IR1: 73
IR2: 1001
IR3: 82
IR4: 995
IR1: 77
IR2: 1001
IR3: 84
IR4: 996
IR1: 74
IR2: 1001
IR3: 86
IR4: 996
IR1: 77
IR2: 1001
IR3: 86
IR4: 996
IR1: 74
IR2: 988
IR3: 84
IR4: 982
IR1: 69
IR2: 982
IR3: 82
IR4: 977
IR1: 70
IR2: 982
IR3: 82
IR4: 977
IR1: 68
IR2: 976
IR3: 77
IR4: 971
IR1: 68
IR1: 72
IR2: 1001
IR3: 72
IR4: 995
IR1: 74
IR2: 1002
IR3: 76
IR4: 994
IR1: 72
IR2: 1001
IR3: 73
IR4: 995
IR1: 72
IR2: 1001
IR3: 75
IR4: 994
IR1: 71
IR2: 1001
IR3: 77
IR4: 995
IR1: 73
IR2: 1001
IR3: 74
IR4: 994
IR1: 73
IR2: 1001
IR3: 75
IR4: 994
IR1: 74
IR2: 1001
IR3: 77
IR4: 995
IR1: 73
IR2: 1001
IR3: 77
IR4: 995
IR1: 76
IR2: 1001
IR3: 77
IR4: 995
IR1: 75
IR2: 1001
IR3: 80
IR4: 995
IR1: 73
IR2: 1001
IR3: 84
IR4: 994
IR1: 72
IR2: 1002
IR3: 79
IR4: 994
IR1: 72
IR2: 1000
IR3: 78
IR4: 992
IR1: 76
IR2: 1001
IR3: 80
IR4: 995
IR1: 74
IR2: 1002
IR3: 80
IR4: 995
IR1: 74
IR2: 1001
IR3: 80
IR4: 993
IR1: 74
IR2: 1002
IR3: 79
IR4: 994
IR1: 73
IR2: 1001
IR3: 80
IR4: 995
IR1: 71
IR2: 1002
IR3: 74
IR4: 995
IR1: 74
IR2: 1002
IR3: 78
IR4: 995
IR1: 73
IR2: 1001
IR3: 76
IR4: 993
IR1: 70
IR2: 1001
IR3: 74
IR4: 995
IR1: 74
IR2: 1001
IR3: 81
IR4: 994
IR1: 78
IR2: 1002
IR3: 82
IR4: 996
IR1: 75
IR2: 1002
IR3: 79
IR4: 995
IR1: 71
IR2: 1001
IR3: 77
IR4: 994
IR1: 72
IR2: 1001
IR3: 76
IR4: 995

"""


# Initialize empty lists for each IR sensor
ir1_values = []
ir2_values = []
ir3_values = []
ir4_values = []

# Extract values using regex
matches = re.findall(r"IR1: (\d+)|IR2: (\d+)|IR3: (\d+)|IR4: (\d+)", input_string)

# Populate the sensor lists
for match in matches:
    if match[0]:
        ir1_values.append(int(match[0]))
    elif match[1]:
        ir2_values.append(int(match[1]))
    elif match[2]:
        ir3_values.append(int(match[2]))
    elif match[3]:
        ir4_values.append(int(match[3]))

# Use Counter to get unique values and their counts, then sort by value
ir1_count = dict(sorted(Counter(ir1_values).items()))
ir2_count = dict(sorted(Counter(ir2_values).items()))
ir3_count = dict(sorted(Counter(ir3_values).items()))
ir4_count = dict(sorted(Counter(ir4_values).items()))

# Function to print counts and averages
def print_counts_and_average(sensor_name, count_dict, values_list):
    print(f"{sensor_name} Value Counts:")
    for value, count in count_dict.items():
        print(f"  {value}: {count}")
    
    # Calculate and print average
    average = sum(values_list) / len(values_list) if values_list else 0
    print(f"Average {sensor_name}: {average:.2f}\n")

# Print the results
print_counts_and_average("IR1", ir1_count, ir1_values)
print_counts_and_average("IR2", ir2_count, ir2_values)
print_counts_and_average("IR3", ir3_count, ir3_values)
print_counts_and_average("IR4", ir4_count, ir4_values)

# Output
# IR1 Value Counts:
  68: 2 
  69: 1 
  70: 3 
  71: 4 
  72: 10
  73: 9 
  74: 10
  75: 2
  76: 3
  77: 2
  78: 1
  80: 2
  82: 1
  84: 1
Average IR1: 73.57

IR2 Value Counts:
  976: 1
  982: 2
  988: 1
  1000: 1
  1001: 31
  1002: 14
Average IR2: 999.74

IR3 Value Counts:
  72: 1
  73: 1
  74: 3
  75: 3
  76: 4
  77: 8
  78: 3
  79: 3
  80: 5
  81: 1
  82: 4
  84: 8
  85: 1
  86: 2
  88: 2
  93: 1
Average IR3: 79.80

IR4 Value Counts:
  971: 1
  977: 2
  982: 1
  991: 1
  992: 1
  993: 4
  994: 13
  995: 23
  996: 4
Average IR4: 993.06