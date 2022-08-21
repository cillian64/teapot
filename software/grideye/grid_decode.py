import base64


def decode(data):
    """
    Decode a 48 character base64 chunk to grid-eye data.
    Returns a tuple of Average, centre, and pixels, all in degrees celcius
    """

    lut = [
        -48, -24, -12, -6, -4, -3, -2, -1,
        1, 2, 3, 4, 6, 12, 24, 48]

    packed = base64.b64decode(data)

    centre = (packed[-2] << 8 | packed[-1]) / 4.0
    average = (packed[-4] << 8 | packed[-3]) / 4.0

    # Unpack the first 32 bytes into 2x nibbles:
    unpacked = []
    for b in packed[:32]:
        unpacked.append(b >> 4)
        unpacked.append(b & 0x0f)

    # Decode the nibbles using the LUT
    for idx, b in enumerate(unpacked):
        unpacked[idx] = lut[b] / 4.0 + average

    return (average, centre, unpacked)
