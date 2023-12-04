source = '0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d'


def transform(s: str):
    chunks = s.split('0x')
    chunks = [chunk for chunk in chunks if chunk != '']
    res = ""
    for chunk in chunks:
        segs = [chunk[i:i+2] for i in range(0, len(chunk), 2)]
        reverse = [chr(int(hex, 16)) for hex in segs[::-1]]
        res = res + "".join(reverse)
    return res


print(transform(source))
