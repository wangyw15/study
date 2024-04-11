import re

from compiler.lexer import get_tokens
from compiler.types import TokenType, Token

_PLUS_IDENTIFIERS = [TokenType.PLUS, TokenType.MINUS]
_MULTIPLY_IDENTIFIERS = [TokenType.TIMES, TokenType.SLASH]

_expression_index: int = -1
_expression_tokens: list[Token] = []


def check_plus_operators() -> bool:
    """
    <plus_operator> ::= '+' | '-'
    :return: True if the current token is a plus operator, False otherwise
    """
    global _expression_index
    print("plus", end=" ")
    print(_expression_index, end=" ")
    print(_expression_tokens[_expression_index][1])

    if _expression_tokens[_expression_index][0] in _PLUS_IDENTIFIERS:
        _expression_index += 1
        return True
    return False


def check_multiply_operators() -> bool:
    """
    <multiply_operator> ::= '*' | '/'
    :return: True if the current token is a multiply operator, False otherwise
    """
    global _expression_index
    print("multiply", end=" ")
    print(_expression_index, end=" ")
    print(_expression_tokens[_expression_index][1])

    if _expression_tokens[_expression_index][0] in _MULTIPLY_IDENTIFIERS:
        _expression_index += 1
        return True
    return False


def check_factor() -> bool:
    """
    <factor> ::= <identifier> | <unsigned int> | '(' <expression> ')'
    :return: True if the current token is a factor, False otherwise
    """
    global _expression_index
    print("factor", end=" ")
    print(_expression_index, end=" ")
    print(_expression_tokens[_expression_index][1])

    # check for identifier
    if re.fullmatch(
        TokenType.IDENTIFIER.value,
        _expression_tokens[_expression_index][1],
        re.IGNORECASE,
    ):
        _expression_index += 1
        return True

    # check for number
    if re.fullmatch(
        TokenType.NUMBER.value, _expression_tokens[_expression_index][1], re.IGNORECASE
    ):
        _expression_index += 1
        return True

    # check for expression with parenthesis
    if not _expression_tokens[_expression_index][0] == TokenType.LEFT_PARENTHESIS:
        raise SyntaxError("invalid syntax")
    _expression_index += 1

    if not check_expression():
        return False

    if (
        _expression_index == len(_expression_tokens)  # unexpected end of expression
        or not _expression_tokens[_expression_index][0] == TokenType.RIGHT_PARENTHESIS
    ):
        raise SyntaxError("'(' was never closed")
    _expression_index += 1

    return True


def check_item() -> bool:
    """
    <item> ::= <factor> { <multiply_operator> <factor> }
    :return: True if the current token is an item, False otherwise
    """
    global _expression_index
    print("item", end=" ")
    print(_expression_index, end=" ")
    print(_expression_tokens[_expression_index][1])

    # check for atomic expression
    if not check_factor():
        return False

    while True:
        # check for end of expression
        if _expression_index == len(_expression_tokens):
            return True
        if not check_multiply_operators():
            break
        if not check_factor():
            return False
    return True


def check_expression() -> bool:
    """
    <expression> ::= [ +|- ] <item> { <plus_operator> <item> }
    :return: True if the current token is an expression, False otherwise
    """
    global _expression_index
    print("expr", end=" ")
    print(_expression_index, end=" ")
    print(_expression_tokens[_expression_index][1])

    # check for prefix operators
    check_plus_operators()

    if not check_item():
        return False

    while True:
        # check for end of expression
        if _expression_index == len(_expression_tokens):
            return True
        if not check_plus_operators():
            break
        if not check_item():
            return False

    return True


def check(code: str) -> bool:
    """
    Check if the given code is a valid expression
    :param code: the code to check
    :return: True if the code is a valid expression, False otherwise
    """
    global _expression_index, _expression_tokens
    _expression_tokens = get_tokens(code)
    _expression_index = 0
    return check_expression()


__all__ = [
    "check_expression",
]
