import string


def dfs(graph, word, stack, words_cnt):
    stack.append(word)

    if word[-1] in graph:
        adjacency = graph[word[-1]].copy()
    else:
        adjacency = {}

    for next_char in adjacency:
        words = adjacency[next_char]
        for word in words:
            if word not in stack:
                dfs(graph, word, stack, words_cnt)

    if len(stack) == words_cnt:
        return stack
    elif len(stack) > 0:
        stack.pop()


def word_chain(words):
    graph = {}
    first_chars = []
    last_chars = []
    for word in words:
        first_char = word[0]
        last_char = word[-1]
        first_chars.append(first_char)
        last_chars.append(last_char)
        if first_char not in graph:
            graph[first_char] = {}
        if last_char not in graph[first_char]:
            graph[first_char][last_char] = []
        graph[first_char][last_char].append(word)

    diff_char_cnt = 0
    first_char_of_chain = ''

    for char in string.ascii_lowercase:
        if first_chars.count(char) != last_chars.count(char):
            diff_char_cnt += 1
            if first_chars.count(char) > last_chars.count(char):
                first_char_of_chain = char

    first_word = ''
    if diff_char_cnt > 2:
        return 'IMPOSSIBLE'
    elif diff_char_cnt == 2:
        first_word = list(filter(lambda w: w[0] == first_char_of_chain, words))[0]
    elif diff_char_cnt == 0:
        recursive_words = list(filter(lambda w: w[0] == w[-1], words))
        for word in recursive_words:
            if first_chars.count(word[0]) - len(recursive_words) == 0:
                return 'IMPOSSIBLE'
        first_word = words[0]
    else:
        return '??'

    result = dfs(graph, first_word, [], len(words))

    if type(result) is list:
        return ' '.join(result)
    else:
        return 'IMPOSSIBLE'


def input_output():
    word_cnt = int(input())
    words = []
    for i in range(word_cnt):
        words.append(input())
    print(word_chain(words))


def execute(func):
    n = int(input())

    for i in range(n):
        func()


execute(input_output)