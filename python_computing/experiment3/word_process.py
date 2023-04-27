import re

def rotate_word(strsrc: str, n: int) -> str:
    '''
    接收一个字符串`strsrc`以及一个整数`n`作为参数，返回新字符串`strdes`，其各个字母是`strsrc`中对应位置各个字母在字母表中“轮转”`n`字符后得到的编码。
    '''
    ret = ''
    for c in strsrc:
        if ord('a') <= ord(c) and ord(c) <= ord('z'):
            ret += chr((ord(c) - ord('a') + n) % 26 + ord('a'))
        elif ord('A') <= ord(c) and ord(c) <= ord('Z'):
            ret += chr((ord(c) - ord('A') + n) % 26 + ord('A'))
        else:
            ret += c
    return ret

def avoids(content: str, prohibited_letters: str) -> bool:
    '''
    接收一个单词和一个含有禁止字母的字符串，判断该单词是否含有禁止字母。
    '''
    if re.search(f'[{prohibited_letters}]', content):
        return True
    return False

def use_only(content: str, allowed_letters: str) -> bool:
    '''
    接收一个单词和一个含有允许字母的字符串，判断该单词是否仅仅由允许字母组成。
    '''
    if re.search(f'[^{allowed_letters}]', content):
        return False
    return True

def use_all(content: str, required_letters: str) -> bool:
    '''
    接收一个单词和一个含有需要字母的字符串，判断该单词是否包含了所有需要字母至少一个。
    '''
    for c in required_letters:
        if c not in content:
            return False
    return True

def has_no_e(content: str) -> bool:
    '''
    判断一个英语单词是否包含字母 e。
    '''
    if re.search('e', content):
        return False
    return True

def is_abecedarian(content: str) -> bool:
    '''
    判断一个英语单词中的字母是否符合字母表序。
    '''
    content = content.lower()
    last = content[0]
    for c in content:
        if ord(c) < ord(last):
            return False
        last = c
    return True

def test():
    print('rotate "hello 111" by 28:', rotate_word('hello 111', 28))
    print(avoids('hello', 'a'))
    print(avoids('The quick brown fox jumps over the lazy dog. ', 'abcde'))
    print(use_only('The quick brown fox jumps over the lazy dog. ', 'abcde'))
    print(use_all('hello', 'hea'))
    print(has_no_e('hello'))
    print(is_abecedarian('abcdef'))
    print(is_abecedarian('abcdegf'))

if __name__ == '__main__':
    words: set[str] = set()
    with open('data/words.txt', 'r') as f:
        words = set(f.read().split())
    
    contains_aeiou: list[str] = []
    not_contains_e: list[str] = []
    abecedarian: list[str] = []
    for w in words:
        if use_all(w, 'aeiou'):
            contains_aeiou.append(w)
        if has_no_e(w):
            not_contains_e.append(w)
        if is_abecedarian(w):
            abecedarian.append(w)
    
    print('Words that contains "aeiou": ')
    print(contains_aeiou)
    print('Percentage of the words that don\'t contains "e": ', len(not_contains_e)/len(words))
    print('Words that is abecedarian: ')
    print(abecedarian)
