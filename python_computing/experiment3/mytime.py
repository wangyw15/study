import datetime

class Time:
    def __init__(self, h: int = 0, m: int = 0, s: int = 0):
        self.hour = 0
        if 0 <= h and h < 24:
            self.hour = h
        else:
            raise Exception("Invalid hour")
        
        self.minute = 0
        if 0 <= m and m < 60:
            self.minute = m
        else:
            raise Exception("Invalid minute")
        
        self.second = 0
        if 0 <= s and s < 60:
            self.second = s
        else:
            raise Exception("Invalid second")

    def __str__(self) -> str:
        return f'{str(self.hour).zfill(2)}:{str(self.minute).zfill(2)}:{str(self.second).zfill(2)}'

    def __add__(self, other):
        second = self.second + other.second
        minute = self.minute + other.minute + int(second / 60)
        hour = self.hour + other.hour + int(minute / 60)
        return Time(hour % 24, minute % 60, second % 60)
        # t1 = datetime.datetime(hour=self.hour, minute=self.minute, second=self.second)
        # t2 = datetime.timedelta(hours=other.hour, minutes=other.minute, seconds=other.second)
        # result = t1 + t2
    
    @staticmethod
    def time2int(cls) -> int:
        return cls.hour*3600 + cls.minute*60 + cls.second
    
    @staticmethod
    def printtime(cls) -> None:
        print(cls)

    def isafter(self, other) -> bool:
        if self.hour > other.hour:
            return True
        elif self.minute > other.minute:
            return True
        elif self.second > other.second:
            return True
        return False

    def increment(self, s: int) -> None:
        if s < 0:
            raise Exception("Invalid second")
        second = self.second + s % 60
        minute = self.minute + int(s / 60) + int(second / 60)
        hour = self.hour + int(s / 3600) + int(minute / 60)
        self.hour = hour % 24
        self.minute = minute % 60
        self.second = second % 60

    @staticmethod
    def isvalid(h: int, m: int, s: int):
        if h < 0 or h >= 24:
            return False
        if m < 0 or m >= 60:
            return False
        if s < 0 or s >= 60:
            return False
        return True

if __name__ == '__main__':
    t = Time(1, 5, 1)
    Time.printtime(t)
    t.increment(119)
    print(t)
    t += Time(0, 5, 0)
    print(t)
    print('t is after 02:00:00:', t.isafter(Time(2, 0, 0)))
    print(Time.time2int(t))
    print('00:00:76 is valid:', Time.isvalid(0, 0, 76))
