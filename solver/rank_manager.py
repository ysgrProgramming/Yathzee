from rank import Rank

class RankManager():
    def __init__(self, rank_list):
        self.rank_list = rank_list
    
    def set_bonus(self, name="unnamed bonus", **kwargs):
        self.bonus_params = {
            "base": 0,
            "marker": 0,
            "target": []
        }

        for k, v in kwargs.items():
            if k in self.bonus_params:
                self.bonus_params[k] = v
    
    
