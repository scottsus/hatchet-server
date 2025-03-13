# Archived: example for Russell

def substring_to_integer(string, start, length, dtype, is_signed=False):
    end = start + length
    hex_string = string[start:end]
    print(hex_string)
    value = int(hex_string, 16)
    if is_signed:
        bit_width = length * 4
        value = extend_sign(value, bit_width)
    return value, end

def extend_sign(value, bit_width):
    if value >= (1 << (bit_width - 1)):
        return value - (1 << bit_width)
    return value


def print_hex_string(string):
    index = 1

    op, index = substring_to_integer(string, index, 2, int)
    cnt, index = substring_to_integer(string, index, 4, int)
    passo, index = substring_to_integer(string, index, 4, int)
    flag, index = substring_to_integer(string, index, 4, int)

    xm, index = substring_to_integer(string, index, 5, int, is_signed=True)
    ym, index = substring_to_integer(string, index, 5, int, is_signed=True)
    x, index = substring_to_integer(string, index, 5, int, is_signed=True)
    y, index = substring_to_integer(string, index, 5, int, is_signed=True)

    zi, index = substring_to_integer(string, index, 4, int)
    zp, index = substring_to_integer(string, index, 4, int)

    lat, index = substring_to_integer(string, index, 8, int, is_signed=True)
    lon, index = substring_to_integer(string, index, 8, int, is_signed=True)

    q, index = substring_to_integer(string, index, 2, int)
    nord, index = substring_to_integer(string, index, 4, int, is_signed=True)
    delta, index = substring_to_integer(string, index, 4, int, is_signed=True)
    crc, index = substring_to_integer(string, index, 4, int)

    print(f"op: {op}, cnt: {cnt}, passo: {passo}, flag: {flag}, xm: {xm}, ym: {ym}, x: {x}, y: {y}, zi: {zi}, zp: {zp}, lat: {lat}, lon: {lon}, q: {q}, nord: {nord}, delta: {delta}, crc: {crc}")

def read_file_content(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except Exception as e:
        print(f"Failed to read from file: {e}")
        return None

def process_file(file_path):
    content = read_file_content(file_path)
    if content is None:
        return

    lines = content.splitlines()

    for line in lines:
        if line.startswith("#"):
            print_hex_string(line)
        elif line.startswith(">MAG="):
            pass  # print(f"MAG data: {line}")

file_path = "raw.74h"
process_file(file_path)
