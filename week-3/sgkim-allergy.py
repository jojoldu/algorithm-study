def allergy(friends, friends_for_dishes):
    dishes_for_friends = []
    for i, friend in enumerate(friends):
        dishes_for_friends.append([])
        for j, friends_for_dish in enumerate(friends_for_dishes):
            if friend in friends_for_dish:
                dishes_for_friends[i].append(j)
    dishes_for_friends = sorted(dishes_for_friends, key=lambda frs: len(frs))

    return get_dish_cnt(dishes_for_friends)


def get_dish_cnt(dishes_for_friends):
    dish_cnt = 0
    min_dish_cnt = 0
    if len(dishes_for_friends) == 0:
        return dish_cnt
    for dish in dishes_for_friends[0]:
        remain_dishes_for_friends = list(filter(lambda dishes: dish not in dishes, dishes_for_friends))
        dish_cnt = 1 + get_dish_cnt(remain_dishes_for_friends)
        if min_dish_cnt == 0 or dish_cnt < min_dish_cnt:
            min_dish_cnt = dish_cnt
    return min_dish_cnt


def input_output():
    input_str = input().split(" ")
    friend_cnt = int(input_str[0])
    dish_cnt = int(input_str[1])
    friends = input().split(" ")
    friends_for_dishes = []
    if len(friends) != friend_cnt:
        print("error!")
        return
    for i in range(dish_cnt):
        input_str = input().split(" ")
        friend_cnt_for_dish = int(input_str[0])
        friends_for_dish = input_str[1:]
        friends_for_dishes.append(friends_for_dish)
        if len(friends_for_dish) != friend_cnt_for_dish:
            print("error!")
            return

    print(allergy(friends, friends_for_dishes))


def execute(func):
    n = int(input())

    for i in range(n):
        func()


execute(input_output)
