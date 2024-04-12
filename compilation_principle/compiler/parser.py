import re

from compiler.types import TokenType, Token, ExpressionType, ExpressionNode

_ast_root: ExpressionNode = ExpressionNode()
_token_index: int = -1
_tokens: list[Token] = []


def _add_operator() -> ExpressionType:
    """
    <add_operator> ::= '+' | '-'
    :return: the type of the operator if the current token is an add operator, None otherwise
    """
    global _token_index
    # print("plus", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    if _tokens[_token_index].type == TokenType.PLUS:
        _token_index += 1
        return ExpressionType.ADD

    elif _tokens[_token_index].type == TokenType.MINUS:
        _token_index += 1
        return ExpressionType.MINUS

    return ExpressionType.UNKNOWN


def _multiply_operator() -> ExpressionType:
    """
    <multiply_operator> ::= '*' | '/'
    :return: the type of the operator if the current token is a multiply operator, None otherwise
    """
    global _token_index
    # print("multiply", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    if _tokens[_token_index].type == TokenType.ASTERISK:
        _token_index += 1
        return ExpressionType.MULTIPLY

    elif _tokens[_token_index].type == TokenType.SLASH:
        _token_index += 1
        return ExpressionType.DIVIDE

    return ExpressionType.UNKNOWN


def _factor() -> ExpressionNode:
    """
    <factor> ::= <identifier> | <unsigned int> | '(' <expression> ')'
    :return: expression node if the current token is an expression, raise error otherwise
    """
    global _token_index
    # print("factor", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    # check for identifier
    if re.fullmatch(
        TokenType.IDENTIFIER.value,
        _tokens[_token_index].data,
        re.IGNORECASE,
    ):
        node = ExpressionNode(ExpressionType.IDENTIFIER, _tokens[_token_index].data)
        _token_index += 1
        return node

    # check for number
    if re.fullmatch(
        TokenType.NUMBER.value, _tokens[_token_index].data, re.IGNORECASE
    ):
        node = ExpressionNode(ExpressionType.NUMBER, _tokens[_token_index].data)
        _token_index += 1
        return node

    # check for expression with parenthesis
    if not _tokens[_token_index].type == TokenType.LEFT_PARENTHESIS:
        raise SyntaxError("invalid syntax")
    _token_index += 1

    node = _expression()
    if not node:
        raise SyntaxError("invalid syntax")

    if (
        _token_index == len(_tokens)  # unexpected end of expression
        or not _tokens[_token_index].type == TokenType.RIGHT_PARENTHESIS
    ):
        raise SyntaxError("'(' was never closed")
    _token_index += 1

    return node


def _term() -> ExpressionNode:
    """
    <term> ::= <factor> { <multiply_operator> <factor> }
    :return: expression node if the current token is an expression, raise error otherwise
    """
    global _token_index
    # print("item", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    # check for atomic expression
    node = _factor()
    if not node:
        raise SyntaxError("invalid syntax")

    while True:
        # end of expression
        if _token_index == len(_tokens):
            break

        operator = _multiply_operator()
        if operator == ExpressionType.UNKNOWN:
            break

        right_node = _factor()
        if not right_node:
            raise SyntaxError("invalid syntax")

        node = ExpressionNode(operator, "", node, right_node)

    return node


def _expression() -> ExpressionNode:
    """
    <expression> ::= [ +|- ] <term> { <plus_operator> <term> }
    :return: expression node if the current token is an expression, raise error otherwise
    """
    global _token_index
    # print("expr", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    # check for leading operators
    leading_sign = _add_operator()

    node = _term()
    if not node:
        raise SyntaxError("invalid syntax")

    while True:
        # end of expression
        if _token_index == len(_tokens):
            break

        operator = _add_operator()
        if operator == ExpressionType.UNKNOWN:
            break

        right_node = _term()
        if not right_node:
            raise SyntaxError("invalid syntax")

        node = ExpressionNode(operator, "", node, right_node)

    if leading_sign != ExpressionType.UNKNOWN:
        node = ExpressionNode(leading_sign, "", ExpressionNode(ExpressionType.NUMBER, "0"), node)

    return node


def ast(tokens: list[Token]) -> ExpressionNode:
    """
    Parse the given tokens and return the AST
    :param tokens: the list of tokens to parse
    :return: the AST root node
    """
    global _ast_root, _token_index, _tokens
    _tokens = tokens
    _token_index = 0
    _ast_root = ExpressionNode()
    return _expression()


__all__ = [
    "ast",
]
