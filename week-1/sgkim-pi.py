from enum import Enum


class PieceManager:
    MIN_PIECE_LEN = 3
    MAX_PIECE_LEN = 5

    def __init__(self):
        self.num_seq_level_dict = {}

    @staticmethod
    def num_seq_str_to_num_seq(num_seq_str):
        return list(map(int, num_seq_str))

    @staticmethod
    def num_seq_to_num_seq_str(num_seq):
        return ''.join(map(str, num_seq))

    def get_piece_level(self, num_seq_str):
        self.register_num_seq_level(num_seq_str, Piece(self.num_seq_str_to_num_seq(num_seq_str)).level.value)

        return self.num_seq_level_dict[num_seq_str]

    def register_num_seq_level(self, num_seq_str, level):
        if num_seq_str not in self.num_seq_level_dict:
            self.num_seq_level_dict[num_seq_str] = level

    def get_min_level(self, num_seq_str):
        if num_seq_str in self.num_seq_level_dict:
            return self.num_seq_level_dict[num_seq_str]

        num_seq = self.num_seq_str_to_num_seq(num_seq_str)
        l = len(num_seq)
        min_level = 0
        start = PieceManager.MIN_PIECE_LEN
        end = min(l, PieceManager.MAX_PIECE_LEN) + 1

        for piece_len in range(start, end):
            remain_len = l - piece_len
            if 0 < remain_len < PieceManager.MIN_PIECE_LEN:
                continue
            new_level = self.get_piece_level(self.num_seq_to_num_seq_str(num_seq[:piece_len]))
            if remain_len > 0:
                new_level += self.get_min_level(self.num_seq_to_num_seq_str(num_seq[piece_len:]))
            if min_level == 0 or new_level < min_level:
                min_level = new_level

        self.register_num_seq_level(num_seq_str, min_level)

        return min_level


class PieceLevel(Enum):
    repeated_nums = 1
    sequential = 2
    zigzag = 4
    equal_diff = 5
    other = 10


class Piece:
    def __init__(self, nums):
        self.nums = nums
        self.level = self.check_level()

    def check_level(self):
        check_list = [True] * 5

        first_num = self.nums[0]
        second_num = self.nums[1]
        seq_diff = 0
        num_diff = 0

        if second_num - first_num == 1:
            check_list[3] = False
            seq_diff = 1
        elif second_num - first_num == -1:
            check_list[3] = False
            seq_diff = -1
        else:
            check_list[1] = False
            num_diff = self.nums[1] - self.nums[0]

        for i in range(1, len(self.nums)):
            if self.nums[i] != first_num:
                check_list[0] = False
            if i != len(self.nums) - 1 and self.nums[i + 1] - self.nums[i] != seq_diff:
                check_list[1] = False
            if not ((i % 2 == 0 and self.nums[i] == first_num) or (i % 2 == 1 and self.nums[i] == second_num)):
                check_list[2] = False
            if i != len(self.nums) - 1 and self.nums[i + 1] - self.nums[i] != num_diff:
                check_list[3] = False

        switcher = {
            0: PieceLevel.repeated_nums,
            1: PieceLevel.sequential,
            2: PieceLevel.zigzag,
            3: PieceLevel.equal_diff,
            4: PieceLevel.other
        }

        for i in range(len(check_list)):
            if check_list[i]:
                return switcher.get(i)


def input_output(piece_manager):
    num_seq_str = input()
    min_level = piece_manager.get_min_level(num_seq_str)

    return min_level


def execute(func):
    piece_manager = PieceManager()

    n = int(input())

    for i in range(n):
        print(func(piece_manager))


execute(input_output)
