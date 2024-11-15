import re
from collections import Counter

input_string = """
IR2: 1002
IR3: 53
IR4: 998
IR1: 48
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1002
IR3: 54
IR4: 998
IR1: 51
IR2: 1001
IR3: 54
IR4: 998
IR1: 51
IR2: 1002
IR3: 54
IR4: 999
IR1: 49
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1001
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 54
IR4: 998
IR1: 50
IR2: 517
IR3: 54
IR4: 998
IR1: 49
IR2: 551
IR3: 54
IR4: 998
IR1: 49
IR2: 1002
IR3: 54
IR4: 998
IR1: 49
IR2: 1002
IR3: 54
IR4: 998
IR1: 52
IR2: 1001
IR3: 54
IR4: 999
IR1: 51
IR2: 1001
IR3: 54
IR4: 998
IR1: 50
IR2: 1002
IR3: 54
IR4: 998
IR1: 50
IR2: 1002
IR3: 54
IR4: 999
IR1: 50
IR2: 1003
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 52
IR2: 1003
IR3: 54
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 998
IR1: 51
IR2: 1002
IR3: 54
IR4: 998
IR1: 52
IR2: 1001
IR3: 54
IR4: 999
IR1: 52
IR2: 1002
IR3: 52
IR4: 998
IR1: 52
IR2: 1002
IR3: 55
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 999
IR1: 49
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1001
IR3: 54
IR4: 998
IR1: 51
IR2: 1001
IR3: 54
IR4: 998
IR1: 51
IR2: 1001
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 54
IR4: 998
IR1: 49
IR2: 1002
IR3: 54
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 997
IR1: 52
IR2: 1002
IR3: 54
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 49
IR2: 1003
IR3: 53
IR4: 999
IR1: 49
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 54
IR4: 998
IR1: 51
IR2: 1001
IR3: 53
IR4: 998
IR1: 50
IR2: 1003
IR3: 54
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 54
IR4: 998
IR1: 50
IR2: 508
IR3: 54
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 997
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1003
IR3: 54
IR4: 998
IR1: 52
IR2: 553
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 54
IR4: 997
IR1: 49
IR2: 1001
IR3: 53
IR4: 998
IR1: 51
IR2: 1001
IR3: 54
IR4: 998
IR1: 100
IR2: 556
IR3: 51
IR4: 1003
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 49
IR2: 1002
IR3: 54
IR4: 998
IR1: 51
IR2: 1002
IR3: 54
IR4: 998
IR1: 51
IR2: 1001
IR3: 55
IR4: 998
IR1: 51
IR2: 1002
IR3: 54
IR4: 997
IR1: 48
IR2: 524
IR3: 54
IR4: 999
IR1: 52
IR2: 1002
IR3: 54
IR4: 997
IR1: 52
IR2: 1001
IR3: 54
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 54
IR4: 998
IR1: 51
IR2: 1002
IR3: 54
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1001
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 1000
IR1: 51
IR2: 1002
IR3: 52
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 577
IR3: 52
IR4: 999
IR1: 51
IR2: 1002
IR3: 52
IR4: 998
IR1: 51
IR2: 1001
IR3: 53
IR4: 997
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 49
IR2: 550
IR3: 52
IR4: 999
IR1: 48
IR2: 1002
IR3: 52
IR4: 999
IR1: 52
IR2: 1002
IR3: 52
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1003
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 49
IR2: 1002
IR3: 51
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 48
IR2: 1003
IR3: 52
IR4: 1000
IR1: 48
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 49
IR2: 1002
IR3: 52
IR4: 1000
IR1: 48
IR2: 1002
IR3: 53
IR4: 999
IR1: 52
IR2: 1002
IR3: 54
IR4: 998
IR1: 49
IR2: 1002
IR3: 52
IR4: 1000
IR1: 47
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 47
IR2: 1002
IR3: 52
IR4: 999
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 49
IR2: 1002
IR3: 53
IR4: 998
IR1: 49
IR2: 1003
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 48
IR2: 1003
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1003
IR3: 51
IR4: 998
IR1: 49
IR2: 1002
IR3: 53
IR4: 999
IR1: 48
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1003
IR3: 53
IR4: 999
IR1: 50
IR2: 1003
IR3: 54
IR4: 998
IR1: 52
IR2: 1002
IR3: 54
IR4: 999
IR1: 50
IR2: 1003
IR3: 52
IR4: 998
IR1: 52
IR2: 676
IR3: 53
IR4: 999
IR1: 52
IR2: 1002
IR3: 52
IR4: 999
IR1: 52
IR2: 1001
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 54
IR4: 999
IR1: 51
IR2: 1002
IR3: 54
IR4: 998
IR1: 51
IR2: 996
IR3: 54
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1001
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 49
IR2: 1003
IR3: 53
IR4: 999
IR1: 49
IR2: 1003
IR3: 53
IR4: 998
IR1: 50
IR2: 515
IR3: 54
IR4: 998
IR1: 50
IR2: 1002
IR3: 51
IR4: 999
IR1: 50
IR2: 976
IR3: 52
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 679
IR3: 53
IR4: 998
IR1: 49
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 997
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 54
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 1002
IR3: 54
IR4: 998
IR1: 51
IR2: 715
IR3: 53
IR4: 998
IR1: 51
IR2: 1001
IR3: 54
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 558
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1001
IR3: 54
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1001
IR3: 54
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 54
IR4: 999
IR1: 49
IR2: 1003
IR3: 54
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1003
IR3: 53
IR4: 999
IR1: 49
IR2: 1002
IR3: 52
IR4: 998
IR1: 48
IR2: 506
IR3: 52
IR4: 1000
IR1: 50
IR2: 1002
IR3: 52
IR4: 1000
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 49
IR2: 556
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 48
IR2: 1002
IR3: 52
IR4: 998
IR1: 49
IR2: 1002
IR3: 53
IR4: 998
IR1: 49
IR2: 1002
IR3: 53
IR4: 999
IR1: 48
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 510
IR3: 53
IR4: 999
IR1: 51
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 48
IR2: 1004
IR3: 53
IR4: 999
IR1: 50
IR2: 1003
IR3: 52
IR4: 999
IR1: 52
IR2: 1001
IR3: 53
IR4: 998
IR1: 50
IR2: 875
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 49
IR2: 1002
IR3: 53
IR4: 998
IR1: 48
IR2: 506
IR3: 53
IR4: 999
IR1: 50
IR2: 513
IR3: 53
IR4: 999
IR1: 51
IR2: 524
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 54
IR4: 998
IR1: 50
IR2: 1001
IR3: 53
IR4: 997
IR1: 51
IR2: 510
IR3: 53
IR4: 999
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1001
IR3: 53
IR4: 998
IR1: 52
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 1003
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 513
IR3: 53
IR4: 999
IR1: 51
IR2: 996
IR3: 53
IR4: 998
IR1: 50
IR2: 515
IR3: 51
IR4: 998
IR1: 52
IR2: 1001
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 999
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 52
IR2: 999
IR3: 53
IR4: 998
IR1: 52
IR2: 1001
IR3: 53
IR4: 999
IR1: 50
IR2: 504
IR3: 51
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 53
IR4: 998
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 999
IR3: 53
IR4: 999
IR1: 52
IR2: 510
IR3: 53
IR4: 998
IR1: 51
IR2: 727
IR3: 52
IR4: 998
IR1: 51
IR2: 528
IR3: 52
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 997
IR1: 50
IR2: 1002
IR3: 53
IR4: 999
IR1: 51
IR2: 1002
IR3: 53
IR4: 999
IR1: 52
IR2: 1002
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 998
IR1: 51
IR2: 1003
IR3: 52
IR4: 998
IR1: 52
IR2: 1002
IR3: 52
IR4: 998
IR1: 51
IR2: 1001
IR3: 53
IR4: 998
IR1: 52
IR2: 531
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 997
IR1: 51
IR2: 1001
IR3: 52
IR4: 997
IR1: 52
IR2: 1003
IR3: 52
IR4: 997
IR1: 52
IR2: 570
IR3: 52
IR4: 997
IR1: 51
IR2: 505
IR3: 52
IR4: 997
IR1: 52
IR2: 1001
IR3: 52
IR4: 997
IR1: 52
IR2: 1001
IR3: 52
IR4: 998
IR1: 52
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 505
IR3: 52
IR4: 998
IR1: 52
IR2: 1002
IR3: 52
IR4: 997
IR1: 51
IR2: 1001
IR3: 52
IR4: 998
IR1: 51
IR2: 1002
IR3: 51
IR4: 998
IR1: 52
IR2: 1002
IR3: 51
IR4: 999
IR1: 50
IR2: 1002
IR3: 51
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 999
IR1: 51
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1003
IR3: 51
IR4: 998
IR1: 50
IR2: 1002
IR3: 51
IR4: 999
IR1: 49
IR2: 1002
IR3: 52
IR4: 999
IR1: 51
IR2: 1001
IR3: 52
IR4: 998
IR1: 50
IR2: 1003
IR3: 52
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 51
IR4: 998
IR1: 49
IR2: 1002
IR3: 52
IR4: 999
IR1: 51
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1003
IR3: 52
IR4: 998
IR1: 50
IR2: 1003
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 998
IR1: 52
IR2: 1003
IR3: 52
IR4: 998
IR1: 52
IR2: 1003
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 49
IR2: 1003
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 51
IR2: 1002
IR3: 51
IR4: 998
IR1: 51
IR2: 1003
IR3: 51
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 999
IR1: 51
IR2: 1002
IR3: 52
IR4: 999
IR1: 52
IR2: 1002
IR3: 52
IR4: 999
IR1: 52
IR2: 1002
IR3: 52
IR4: 998
IR1: 51
IR2: 1003
IR3: 53
IR4: 998
IR1: 51
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1003
IR3: 52
IR4: 998
IR1: 50
IR2: 1003
IR3: 51
IR4: 999
IR1: 49
IR2: 1003
IR3: 52
IR4: 999
IR1: 49
IR2: 1003
IR3: 51
IR4: 999
IR1: 48
IR2: 1003
IR3: 52
IR4: 998
IR1: 48
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1003
IR3: 51
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1002
IR3: 51
IR4: 998
IR1: 50
IR2: 1003
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 51
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1003
IR3: 52
IR4: 998
IR1: 50
IR2: 1003
IR3: 51
IR4: 999
IR1: 49
IR2: 1003
IR3: 52
IR4: 999
IR1: 48
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1003
IR3: 51
IR4: 998
IR1: 49
IR2: 1003
IR3: 52
IR4: 999
IR1: 49
IR2: 1002
IR3: 51
IR4: 999
IR1: 48
IR2: 1003
IR3: 51
IR4: 999
IR1: 49
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1003
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1003
IR3: 51
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1003
IR3: 51
IR4: 998
IR1: 48
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1003
IR3: 51
IR4: 998
IR1: 49
IR2: 1002
IR3: 52
IR4: 999
IR1: 48
IR2: 1002
IR3: 52
IR4: 999
IR1: 47
IR2: 1003
IR3: 51
IR4: 998
IR1: 49
IR2: 1002
IR3: 51
IR4: 998
IR1: 49
IR2: 1002
IR3: 52
IR4: 998
IR1: 47
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 51
IR4: 999
IR1: 48
IR2: 1003
IR3: 52
IR4: 1000
IR1: 49
IR2: 1002
IR3: 52
IR4: 999
IR1: 46
IR2: 1004
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1003
IR3: 51
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1002
IR3: 51
IR4: 998
IR1: 49
IR2: 1002
IR3: 52
IR4: 999
IR1: 48
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1002
IR3: 51
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 50
IR2: 1003
IR3: 52
IR4: 999
IR1: 50
IR2: 1003
IR3: 51
IR4: 998
IR1: 48
IR2: 1003
IR3: 51
IR4: 999
IR1: 49
IR2: 1003
IR3: 51
IR4: 999
IR1: 48
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1002
IR3: 52
IR4: 998
IR1: 48
IR2: 1003
IR3: 52
IR4: 999
IR1: 50
IR2: 1003
IR3: 51
IR4: 998
IR1: 50
IR2: 1003
IR3: 52
IR4: 998
IR1: 52
IR2: 1002
IR3: 52
IR4: 998
IR1: 50
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1002
IR3: 52
IR4: 999
IR1: 49
IR2: 1002
IR3: 52
IR4: 999
IR1: 48
IR2: 1003
IR3: 52
IR4: 999
IR1: 49
IR2: 1003
IR3: 52
IR4: 1000
IR1: 48
IR2: 1003
IR3: 52
IR4: 999
IR1: 51
IR2: 1003
IR3: 51
IR4: 999
IR1: 50
IR2: 1002
IR3: 52
IR4: 998
IR1: 49
IR2: 1003
IR3: 52
IR4: 999
IR1: 51
IR2: 1002
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
'''
IR1 Value Counts:
  46: 1  
  47: 4  
  48: 26 
  49: 54 
  50: 118
  51: 82 
  52: 59
  100: 1
Average IR1: 50.37

IR2 Value Counts:
  504: 1
  505: 2
  506: 2
  508: 1
  510: 3
  513: 2
  515: 2
  517: 1
  524: 2
  528: 1
  531: 1
  550: 1
  551: 1
  553: 1
  556: 2
  558: 1
  570: 1
  577: 1
  676: 1
  679: 1
  715: 1
  727: 1
  875: 1
  976: 1
  996: 2
  999: 2
  1001: 31
  1002: 215
  1003: 62
  1004: 2
Average IR2: 962.45

IR3 Value Counts:
  51: 37
  52: 128
  53: 128
  54: 50
  55: 2
Average IR3: 52.57

IR4 Value Counts:
  997: 16
  998: 192
  999: 128
  1000: 8
  1003: 1
Average IR4: 998.39
'''