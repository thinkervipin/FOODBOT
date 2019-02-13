import cv2
import serial
import AGV_utilities as utils
import AGV_imagery as IMG
import json

def decode_serial_old_school(command,incoming_variables = 1,delimiter = ','):
    command = command.split(delimiter)
    command = [float(f) for f in command]
    if not len(command) == incoming_variables:
        print ('[ERROR] Data not correct : '+str(command))
        command = [0 for f in range(incoming_variables)]
        return command

def decode_to_json(command):
    
    status = 'empty'
    ret_val = {"status":status}
    if len(command)!=0:
        try:
            data = json.loads(command)
            status = data["status"]
            ret_val = data
        except:
            status = "data error"
    return ret_val

def encode_serial(command):
    return json.dumps(command)




def order_serial(command,ser):
    
        command +='\n'
        
        ack_str = ''
        check = 0
        while True:
            data = ser.read()
            data = data.decode()
            if not data == '':
                if ord(data) == ord(';'):
                    check +=1
                    if check==2:
                        break;
                ack_str += data

        ser.flushInput()
        ser.flushOutput()
        ser.write(command.encode())
        
        ack_str = ack_str.split(';')[1]
        return ack_str


if __name__ == '__main__':
    
    SER = serial.Serial("/dev/cu.usbmodem14201",115200)
    MAP = IMG.DRAW_MAP()
    count = 0
    dis = 0
    key = 0
    kp=0
    while True:
        key = 0 if key <0 else key
        count+= (10 if chr(key)=='a' else (-10 if chr(key)=='d'else 0))
        dis+=(10 if chr(key)=='w' else (-10 if chr(key)=='s'else 0))
        kp+=(0.5 if chr(key)=='u' else (-0.5 if chr(key)=='j'else 0))
        command_out = {"DIR":count,
                        "DIS":dis,
                        "kp":kp

                        }
        
        command_out = encode_serial(command_out)
        command_in = order_serial(command_out,SER)
        command_in = decode_to_json(command_in)
        
        print command_in
        print count ,',',dis,',',kp
        
        if command_in["status"] != "auto":
            continue
    
        x =   int(command_in["X"])
        y =   int(command_in["Y"])
        mag = int(command_in["YAW_COMP"])
        odo = int(command_in["YAW_ODO"])
        
        
        MAP.draw_vehicle_marker(utils.Vector3(x,y,0),utils.Vector3(0,0,odo),arrow_size=30,text="ODO: {} , MAG: {}".format(odo,mag))
        key = cv2.waitKey(1)
        try:
            MAP.show_map()
        
        except:
            print "Map load error!"
        if key == ord('x'):
            break
