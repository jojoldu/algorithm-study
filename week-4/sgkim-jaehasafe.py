def get_partial_match(N):
    m = len(N)
    pi = m * [0]
    begin, matched = 1, 0
    for i in range(1, m):
        while matched > 0 and N[i] != N[matched]:
            matched = pi[matched - 1]
        if N[i] == N[matched]:
            matched += 1
            pi[i] = matched
    return pi


def kmp_search(H, N):
    n, m = len(H), len(N)
    ret = []
    pi = get_partial_match(N)
    matched = 0
    for i in range(n):
        while matched > 0 and H[i] != N[matched]:
            matched = pi[matched - 1]
        if H[i] == N[matched]:
            matched += 1
            if matched == m:
                ret.append(i - m + 1)
                matched = pi[matched - 1]
    return ret


def get_min_dial_cnt(states):
    min_dial_cnt = 0

    for i in range(len(states) - 1):
        if i % 2 == 0:
            min_dial_cnt += kmp_search(states[i + 1] + states[i + 1], states[i])[0]
        else:
            min_dial_cnt += kmp_search(states[i] + states[i], states[i + 1])[0]

    return min_dial_cnt


def in_out():
    N = int(input())
    states = []
    for i in range(N + 1):
        states += [input()]
    res = get_min_dial_cnt(states)
    print(res)


if __name__ == '__main__':
    C = int(input())
    for i in range(C):
        in_out()

