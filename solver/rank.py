class Rank():
    def __init__(self, name="unnamed_rank", **kwargs):
        self.params = {"rtype": None, "base": 0, "rate": 1, "target": {1,2,3,4,5,6}, "level": 1}
        self.name = name
        for k, v in kwargs.items():
            if k in self.params:
                self.params[k] = v

    def get_point(self, pattern):
        rtype = self.params["rtype"]

        point = self.params["base"] + sum([p for p in pattern if p in self.params["target"]])*self.params["rate"]
        if rtype == "straight":
            if self.is_straight(pattern, self.params["level"]): return point
            else: return 0
        elif rtype == "group":
            if self.is_group(pattern, self.params["level"]): return point
            else: return 0
        elif rtype == "fullhouse":
            if self.is_fullhouse(pattern): return point
            else: return 0
        else:
            return point

    def is_straight(self, pattern, level):
        count = 1
        buf = -1
        for p in pattern:
            if p > buf+1: count = 1
            elif p == buf+1: count += 1
            buf = p

            if count >= level: return True

        return False

    def is_group(self, pattern, level):
        count = 1
        buf = -1
        for p in pattern:
            if p == buf: count += 1
            else:
                count = 1
            buf = p

            if count >= level: return True

        return False

    def is_fullhouse(self, pattern):
        sort = set(pattern)
        if len(sort) == 2 and pattern[1] != pattern[3]:
            return True
        else:
            return False

    def __str__(self):
        return self.name

if __name__ == "__main__":
    rank = Rank("3ダイス", rtype="fullhouse", level=3)
    pattern = (2,2,2,4,4)
    print(rank)
    print(f"{pattern} = {rank.get_point(pattern)}")