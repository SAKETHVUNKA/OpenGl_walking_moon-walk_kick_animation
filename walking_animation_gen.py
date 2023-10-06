import csv
import os

data=[]

rightuo=0
rightun=0
rightlo=0
rightln=0
leftuo=0
leftun=0
leftlo=0
leftln=0

hrightuo=0
hrightun=0
hrightlo=0
hrightln=0
hleftuo=0
hleftun=0
hleftlo=0
hleftln=0

steps=75

generated_data=[]

def assign(old,new):
    global rightuo,rightun,rightlo,rightln,leftln,leftlo,leftun,leftuo,hrightuo,hrightun,hrightlo,hrightln,hleftln,hleftlo,hleftun,hleftuo
    rightuo=data[old][0]
    rightun=data[new][0]
    rightlo=data[old][1]
    rightln=data[new][1]
    leftuo=data[old][2]
    leftun=data[new][2]
    leftlo=data[old][3]
    leftln=data[new][3]
    
    hrightuo=data[old][4]
    hrightun=data[new][4]
    hrightlo=data[old][5]
    hrightln=data[new][5]
    hleftuo=data[old][6]
    hleftun=data[new][6]
    hleftlo=data[old][7]
    hleftln=data[new][7]
    # print(rightuo,rightun,rightlo,rightln)

def fill(old,new,steps):
    assign(old,new)
    for i in range(steps):
        generated_data.append([rightuo+(i+1)*(rightun-rightuo)/(steps),rightlo+(i+1)*((rightln-rightlo)/steps),leftuo+(i+1)*((leftun-leftuo)/steps),leftlo+(i+1)*((leftln-leftlo)/steps),  hrightuo+(i+1)*(hrightun-hrightuo)/(steps),hrightlo+(i+1)*((hrightln-hrightlo)/steps),hleftuo+(i+1)*((hleftun-hleftuo)/steps),hleftlo+(i+1)*((hleftln-hleftlo)/steps)])

        print([rightuo+(i+1)*(rightun-rightuo)/(steps),rightlo+(i+1)*((rightln-rightlo)/steps),leftuo+(i+1)*((leftun-leftuo)/steps),leftlo+(i+1)*((leftln-leftlo)/steps),  hrightuo+(i+1)*(hrightun-hrightuo)/(steps),hrightlo+(i+1)*((hrightln-hrightlo)/steps),hleftuo+(i+1)*((hleftun-hleftuo)/steps),hleftlo+(i+1)*((hleftln-hleftlo)/steps)])
        
        

def generateData():#rl,lg,rh,lh
    # data.append([15,-5,-15,-5,-10,5,10,20])
    # data.append([5,0,5,-45,-5,5,0,25])
    # data.append([0,0,15,-45,-5,15,5,20])
    # data.append([-10,-2.5,40,-25,5,25,-10,15])
    # data.append([-15,-5,25,-10,10,30,-25,28])
    # data.append([-15,-5,15,-5,10,20,-10,5])
    # data.append([5,-45,5,0,0,25,-5,5])
    # data.append([15,-45,0,0,5,20,-5,15])
    # data.append([40,-25,-10,-2.5,-10,15,5,25])
    # data.append([25,-10,-15,-5,-25,28,10,30])
    # data.append([15,-5,-15,-5,-10,5,10,20])
    
    data.append([15,-5,-15,-5,-10,5,10,27.5])
    data.append([5,0,5,-45,-7.5,10,7.5,24])
    data.append([0,0,15,-45,2.5,15,5,20])
    data.append([-10,-2.5,40,-25,5,22.5,-10,15])
    data.append([-15,-5,25,-10,7.5,30,-15,10])
    data.append([-15,-5,15,-5,10,27.5,-10,5])
    data.append([5,-45,5,0,0,25,-7.5,7.5])
    data.append([15,-45,0,0,5,20,2.5,15])
    data.append([40,-25,-10,-2.5,-10,15,5,22.5])
    data.append([25,-10,-15,-5,-15,10,10,30])
    data.append([15,-5,-15,-5,-10,5,10,27.5])
    
    # data.append([45,-5,-45,-5])
    # data.append([0,0,0,-45])
    # data.append([-45,0,45,-45])
    # data.append([0,-2.5,0,-25])
    # data.append([45,-5,-45,-10])
    # data.append([0,-5,0,-5])
    # data.append([-45,-45,45,0])
    # data.append([0,-45,0,0])
    # data.append([45,-25,-45,-2.5])
    # data.append([0,-10,0,-5])
    # data.append([-45,-5,45,-5])
    global steps
    for i in range(0,10):
        generated_data.append(data[i])
        print(i,i+1)
        fill(i,i+1,steps)
        print(i,i+1)
        print()
    # generated_data.append(data[i])

def generate_csv_with_float_values(csv_filename, data_dict):
    header = ["rightLeg_u","rightLeg_l","leftLeg_u", "leftLeg_l"]

    file_exists = os.path.isfile(csv_filename)

    with open(csv_filename, mode='a', newline='') as csv_file:
        writer = csv.writer(csv_file)
        for row in data_dict:
            writer.writerow(row)

csv_filename = "walking_efficient.csv"

data=generateData()
generate_csv_with_float_values(csv_filename,generated_data)