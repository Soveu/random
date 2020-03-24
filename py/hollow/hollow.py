#!/usr/bin/python

import base64
import json
from Crypto.Cipher import AES

FILEPATH = "/home/soveu/.config/unity3d/Team Cherry/Hollow Knight/user2.dat"
KEY = b"UKu52ePUBwetZ9wNX88o54dnfKRu0T1l"
MAGIC = b"\x00\x01\x00\x00\x00\xff\xff\xff\xff\x01\x00\x00\x00\x00\x00\x00\x00\x06\x01\x00\x00\x00"

def decrypt_save(filecontents):
    decoded = base64.b64decode(filecontents[len(MAGIC):])
    aes = AES.new(KEY, AES.MODE_ECB)
    decrypted = aes.decrypt(decoded)
    
    return decrypted

def encrypt_save(data):
    padding_len = 16 - len(data) % 16
    data += bytes([padding_len]) * padding_len

    aes = AES.new(KEY, AES.MODE_ECB)
    encrypted = aes.encrypt(data)
    encoded = base64.b64encode(encrypted)

    return encoded

def gen_header(data):
    length = min(0x7FFFFFFF, len(data))
    ret = bytearray()

    for i in range(4):
        if (length >> 7) != 0:
            ret.append((length & 0x7F) | 0x80)
            length >>= 7
        else:
            ret.append(length & 0x7F)
            length >>= 7
            break

    if length != 0:
        ret.append(length)

    return ret

def remove_padding(data):
    # get rid of padding
    return data[:-data[-2]]

s1 = None
with open(FILEPATH, 'rb') as f:
    s1 = f.read()

origsave = remove_padding(decrypt_save(s1))
print(origsave[-16:])

savejson = json.loads(origsave)
savejson["playerData"]["geo"] = -1
savejson["playerData"]["playTime"] = 3600.0 * 24 * 365 * 10

encsave = encrypt_save(json.dumps(savejson, separators=(',',':')).encode('utf-8'))
s2 = MAGIC + gen_header(encsave) + encsave + b'\x0B'

with open(FILEPATH, 'wb+') as f:
    f.write(s2)

