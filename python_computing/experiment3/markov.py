import random
import re

def markov_analysis(text: str, n: int) -> dict[str, dict[str, float]]:
    # text = re.sub(r'[^A-Za-z ]', '', text).replace('\n', ' ').replace('\r', ' ').lower() # remove non-alphabetic characters
    words = text.split() # split into words
    phrases = [words[i: i+n] for i in range(int(len(words)/n)+1)] # split into phrases

    # transition matrix
    transitions: dict[str, dict[str, float]] = {}
    for i in range(len(phrases)-1): # ignore last phrase
        current: str = ' '.join(phrases[i])
        next: str = ' '.join(phrases[i+1])
        if current not in transitions.keys():
            transitions[current] = {}
        if next not in transitions[current].keys():
            transitions[current][next] = 0
        transitions[current][next] += 1
    # frequency
    for current in transitions:
        total = sum(transitions[current].values())
        for next in transitions[current]:
            transitions[current][next] /= total

    return transitions

def generate_next(transistions: dict[str, dict[str, float]], current: str):
    if current not in transistions.keys():
        return None
    options = transistions[current]
    p = random.random()
    choices = random.choices(list(options.keys()), weights=list(options.values()))
    return choices[0]

def markov_generate(transistions: dict[str, dict[str, float]], max_len: int = 2):
    phrases = list(transistions.keys())
    current = random.choice(phrases)
    results = [current]
    for i in range(max_len):
        current = generate_next(transistions, current)
        if current is None:
            break
        results.append(current)
    return ' '.join(results)

if __name__ == '__main__':
    n = 1
    with open('data/emma.txt', 'r') as f:
        result = markov_analysis(f.read(), n)
        print(markov_generate(result, 100))
