import random
import math

N = 100000
K = 0.125

unlucky_streak = 0
longest_unlucky_streak = 0
unluckyness = 0

def calc_prob(chance):
    hits = 0
    s = 0
    for _ in range(N):
        if random.random() < chance + unluckyness:
            s += unluckyness
            hits += 1
            longest_unlucky_streak = max(longest_unlucky_streak, unlucky_streak)
            unlucky_streak = 0
            unluckyness = 0
        else:
            if unlucky_streak * chance > 1:
                unluckyness += chance
            unlucky_streak += 1

    chance += 0.05

    return (hits/N, s/N, longest_unlucky_streak)

p = 0.001

(actual_p, avg_unlucky, lus) = calc_prob(p)

out = "WITH chance=%03f\n" % p
out += "actual chance=%03f\n" % actual_p
out += "average unluckyness=%03f\n" % (avg_unlucky)
out += "lus=%i\n" % lus
print(out)
