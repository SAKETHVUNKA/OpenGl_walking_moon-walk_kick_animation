import csv
import os

data = []

rightuo = 0
rightun = 0
rightlo = 0
rightln = 0
leftuo = 0
leftun = 0
leftlo = 0
leftln = 0

hrightuo = 0
hrightun = 0
hrightlo = 0
hrightln = 0
hleftuo = 0
hleftun = 0
hleftlo = 0
hleftln = 0

abdTxo = 0  
abdTyo = 0  
abdRo  = 0
abdTxn = 0 
abdTyn = 0
abdRn  = 0

steps = 100

generated_data = []


def assign(old, new):
    global rightuo, rightun, rightlo, rightln, leftln, leftlo, leftun, leftuo, hrightuo, hrightun, hrightlo, hrightln, hleftln, hleftlo, hleftun, hleftuo , abdTxo , abdTyo , abdRo , abdTxn , abdTyn , abdRn 
    rightuo = data[old][4]
    rightun = data[new][4]
    rightlo = data[old][5]
    rightln = data[new][5]
    leftuo = data[old][6]
    leftun = data[new][6]
    leftlo = data[old][7]
    leftln = data[new][7]

    hrightuo = data[old][0]
    hrightun = data[new][0]
    hrightlo = data[old][1]
    hrightln = data[new][1]
    hleftuo = data[old][2]
    hleftun = data[new][2]
    hleftlo = data[old][3]
    hleftln = data[new][3]
    abdTxn = data[new][8]
    abdTxo = data[old][8]
    abdTyo = data[old][9]
    abdTyn = data[new][9]
    abdRo = data[old][10]
    abdRn = data[new][10]
    
    
    # print(rightuo,rightun,rightlo,rightln)


def fill(old, new, steps):
    assign(old, new)
    for i in range(steps):
        generated_data.append([rightuo+(i+1)*(rightun-rightuo)/(steps), rightlo+(i+1)*((rightln-rightlo)/steps), leftuo+(i+1)*((leftun-leftuo)/steps), leftlo+(i+1)*((leftln-leftlo)/steps),
                              hrightuo+(i+1)*(hrightun-hrightuo)/(steps), hrightlo+(i+1)*((hrightln-hrightlo)/steps), hleftuo+(i+1)*((hleftun-hleftuo)/steps), hleftlo+(i+1)*((hleftln-hleftlo)/steps) , abdTxo+((i+1)*(abdTxn-abdTxo)/steps) ,abdTyo+((i+1)*(abdTyn-abdTyo)/steps) , abdRo+((i+1)*(abdRn-abdRo)/steps) ])

        print([rightuo+(i+1)*(rightun-rightuo)/(steps), rightlo+(i+1)*((rightln-rightlo)/steps), leftuo+(i+1)*((leftun-leftuo)/steps), leftlo+(i+1)*((leftln-leftlo)/steps),
                              hrightuo+(i+1)*(hrightun-hrightuo)/(steps), hrightlo+(i+1)*((hrightln-hrightlo)/steps), hleftuo+(i+1)*((hleftun-hleftuo)/steps), hleftlo+(i+1)*((hleftln-hleftlo)/steps) , (abdTxn-abdTxo)/steps ,(abdTyn-abdTyo)/steps , (abdRn-abdRo)/steps])


def generateData():  # rh,lh,rl,lg,abdT,abdR
    data.append([15, -5, -15, -5, -10, 5, 10, 27.5, 0, 0, 0])
    data.append([25,25,-25,130,35,-15,-35,5,0,0,0])
    data.append([30,25,-20,130,45,-40,-40,7.5,1.54,0,0])
    data.append([0,90,-15,5,10,-10,-15,-35,4,1.5,0])
    data.append([80,110,-80,5,-20,-20,60,2,10,2.8,0])
    data.append([110,100,-110,80,20,-70,15,-5,12,4,10])
    data.append([85,10,-135,75,110,0,20,-5,14,4,10])
    data.append([60,15,-60,30,120,-5,-5,-2,16,2.5,25])
    data.append([45,15,-60,30,95,-5,-5,-2,17,.75,25])
    data.append([30,10,-40,20,70,-10,-25,-2,18,0,15])
    data.append([15,-5,-15,5,-10,5,10,-10,25,0,0])
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

csv_filename = "kick.csv"

data=generateData()
generate_csv_with_float_values(csv_filename,generated_data)