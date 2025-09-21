from maix import time
from MaixAPI.apriltagmap import AprilTagConfig
from MaixAPI.uarttransmit import CMD_Packet, DataTransimit

"""
Example usage: Users can refer to following lines for implementation.
"""
CMD = CMD_Packet()
CMD.Vx = 0.0
CMD.Vy = 0.0
CMD.Vw = 0
CMD.motorsPos = [45, 90, 90, 90, 90, 90]

print(CMD.Vx, CMD.Vy, CMD.Vw)
print(CMD.motorsPos)

while True:
    DataTransimit(CMD)
    print(CMD.Vx, CMD.Vy, CMD.Vw)
    # you can refer to this line to control your frequency
    time.sleep_ms(10)