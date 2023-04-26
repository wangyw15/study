def ack(m: int, n: int) -> int:
    if m == 0:
        return n+1
    elif m > 0 and n == 0:
        return ack(m-1, 1)
    elif m > 0 and n > 0:
        return ack(m-1, ack(m, n-1))
    return 0

if __name__ == '__main__':
    print(ack(3, 4))
