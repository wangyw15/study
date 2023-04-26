import random
import re

def markov_analysis(text: str, n: int) -> dict[str, dict[str, int]]:
    text = re.sub(r'[^A-Za-z ]', '', text).lower()
    words = text.split()
    substrings = [words[i: i+n] for i in range(int(len(words)/n)+1)]

    # transition matrix
    transitions: dict[str, dict[str, int]] = {}
    for i in range(len(substrings)-1):
        current: str = ' '.join(substrings[i])
        next: str = ' '.join(substrings[i+1])
        if current not in transitions:
            transitions[current] = {}
        if next not in transitions[current]:
            transitions[current][next] = 0
        transitions[current][next] += 1

    # frequency
    for current in transitions:
        total = sum(transitions[current].values())
        for next in transitions[current]:
            transitions[current][next] /= total

    return transitions

def markov_generate(transistions: dict[str, dict[str, int]], max: int = 10):
    phrases = list(transistions.keys())
    n = len(phrases[0].split())
    current = random.choice(phrases)
    result = current
    for i in range(max):
        options = transistions[current]
        next = random.choices(list(options.keys()), list(options.values()))[0]
        result = ' '.join(result.split() + next.split())
        current = ' '.join(result.split()[-n:])
    return result

if __name__ == '__main__':
    n = 10
    with open('data/emma.txt', 'r') as f:
        result = markov_analysis(f.read(), n)
        print(markov_generate(result, 10))
