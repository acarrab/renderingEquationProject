from sys import argv
if len(argv) == 1:
    print("python ./fancify.py <string> <columns> <symbol>")
elif len(argv) == 2:
    print((' %s '%(argv[1])).center(80, '~'))
elif len(argv) == 3:
    print((' %s '%(argv[1])).center(int(argv[2]), '~'))
else:
    print((' %s '%(argv[1])).center(int(argv[2]), argv[3]))
