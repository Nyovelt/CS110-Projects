import os

if os.path.exists('bmp.bin'):
    os.remove('bmp.bin')

num = 0
while num <= 0:
    os.system("python.exe bmp2hex.py -kbin {0}.bmp".format(num))
    num += 1