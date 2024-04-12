import re

from compiler.lexer import get_tokens
from compiler.types import TokenType, Token, ExpressionType, ExpressionNode

_expression_index: int = -1
_expression_tokens: list[Token] = []


def _add_operator() -> bool:
    """
    <add_operator> ::= '+' | '-'
    :return: True if the current token is a plus operator, False otherwise
    """
    global _expression_index
    # print("plus", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    if _expression_tokens[_expression_index].type in [TokenType.PLUS, TokenType.MINUS]:
        _expression_index += 1
        return True
    return False


def _multiply_operator() -> bool:
    """
    <multiply_operator> ::= '*' | '/'
    :return: True if the current token is a multiply operator, False otherwise
    """
    global _expression_index
    # print("multiply", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    if _expression_tokens[_expression_index].type in [TokenType.ASTERISK, TokenType.SLASH]:
        _expression_index += 1
        return True
    return False


def _factor() -> bool:
    """
    <factor> ::= <identifier> | <unsigned int> | '(' <expression> ')'
    :return: True if the current token is a factor, False otherwise
    """
    global _expression_index
    # print("factor", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    # check for identifier
    if re.fullmatch(
        TokenType.IDENTIFIER.value,
        _expression_tokens[_expression_index].data,
        re.IGNORECASE,
    ):
        _expression_index += 1
        return True

    # check for number
    if re.fullmatch(
        TokenType.NUMBER.value, _expression_tokens[_expression_index].data, re.IGNORECASE
    ):
        _expression_index += 1
        return True

    # check for expression with parenthesis
    if not _expression_tokens[_expression_index].type == TokenType.LEFT_PARENTHESIS:
        raise SyntaxError("invalid syntax")
    _expression_index += 1

    if not _expression():
        return False

    if (
        _expression_index == len(_expression_tokens)  # unexpected end of expression
        or not _expression_tokens[_expression_index].type == TokenType.RIGHT_PARENTHESIS
    ):
        raise SyntaxError("'(' was never closed")
    _expression_index += 1

    return True


def term() -> bool:
    """
    <term> ::= <factor> { <multiply_operator> <factor> }
    :return: True if the current token is an item, False otherwise
    """
    global _expression_index
    # print("item", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    # check for atomic expression
    if not _factor():
        return False

    while True:
        if (
            _expression_index == len(_expression_tokens)  # end of expression
            or not _multiply_operator()
        ):
            break
        if not _factor():
            return False
    return True


def _expression() -> bool:
    """
    <expression> ::= [ +|- ] <term> { <plus_operator> <term> }
    :return: True if the current token is an expression, False otherwise
    """
    global _expression_index
    # print("expr", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    # check for prefix operators
    _add_operator()

    if not term():
        return False

    while True:
        if (
                _expression_index == len(_expression_tokens)    # end of expression
                or not _add_operator()
        ):
            break
        if not term():
            return False

    return True


def ast(code: str) -> bool:
    """
    Check if the given code is a valid expression
    :param code: the code to check
    :return: True if the code is a valid expression, False otherwise
    """
    global _expression_index, _expression_tokens
    _expression_tokens = get_tokens(code)
    _expression_index = 0
    return _expression()


__all__ = [
    "ast",
]
