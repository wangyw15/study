from . import code_helper
from compiler.lexer import get_tokens
from compiler.types import TokenType, Token

code_example = code_helper.get_test_code("experiment2_example")
code_valid_identifiers = code_helper.get_test_code("single_line_identifiers")
code_multi_line_var = code_helper.get_test_code("multi_line_var")
code_multi_line_const = code_helper.get_test_code("multi_line_const")
code_multi_line_const_var = code_helper.get_test_code("multi_line_const_var")


def test_get_symbols_example():
    result = get_tokens(code_example)
    expected = [
        Token(TokenType.CONST, "const"),
        Token(TokenType.IDENTIFIER, "a"),
        Token(TokenType.EQUAL, "="),
        Token(TokenType.NUMBER, "10"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.VAR, "var"),
        Token(TokenType.IDENTIFIER, "b"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "c"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.BEGIN, "begin"),
        Token(TokenType.READ, "read"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "b"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.IDENTIFIER, "c"),
        Token(TokenType.BECOMES, ":="),
        Token(TokenType.IDENTIFIER, "a"),
        Token(TokenType.PLUS, "+"),
        Token(TokenType.IDENTIFIER, "b"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.WRITE, "write"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "c"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.END, "end"),
        Token(TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_valid_identifiers():
    result = get_tokens(code_valid_identifiers)
    expected = [
        Token(TokenType.CONST, "Const"),
        Token(TokenType.IDENTIFIER, "num"),
        Token(TokenType.EQUAL, "="),
        Token(TokenType.NUMBER, "100"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.VAR, "Var"),
        Token(TokenType.IDENTIFIER, "a_1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "b2_"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "b_3"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "_b3"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "a1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "B2"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.BEGIN, "Begin"),
        Token(TokenType.READ, "Read"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "A1"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.IDENTIFIER, "b2"),
        Token(TokenType.BECOMES, ":="),
        Token(TokenType.IDENTIFIER, "a1"),
        Token(TokenType.PLUS, "+"),
        Token(TokenType.IDENTIFIER, "num"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.WRITE, "write"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "A1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "B2"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.END, "End"),
        Token(TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_multi_line_var():
    result = get_tokens(code_multi_line_var)
    expected = [
        Token(TokenType.CONST, "Const"),
        Token(TokenType.IDENTIFIER, "num"),
        Token(TokenType.EQUAL, "="),
        Token(TokenType.NUMBER, "100"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.VAR, "Var"),
        Token(TokenType.IDENTIFIER, "a1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "a2"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "b2"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.BEGIN, "Begin"),
        Token(TokenType.READ, "Read"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "A1"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.READ, "Read"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "a2"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.IDENTIFIER, "b2"),
        Token(TokenType.BECOMES, ":="),
        Token(TokenType.IDENTIFIER, "a1"),
        Token(TokenType.PLUS, "+"),
        Token(TokenType.IDENTIFIER, "A2"),
        Token(TokenType.PLUS, "+"),
        Token(TokenType.IDENTIFIER, "num"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.WRITE, "write"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "A1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "B2"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.END, "End"),
        Token(TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_multi_line_const():
    result = get_tokens(code_multi_line_const)
    expected = [
        Token(TokenType.CONST, "Const"),
        Token(TokenType.IDENTIFIER, "num1"),
        Token(TokenType.EQUAL, "="),
        Token(TokenType.NUMBER, "100"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "num2"),
        Token(TokenType.EQUAL, "="),
        Token(TokenType.NUMBER, "200"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "num3"),
        Token(TokenType.EQUAL, "="),
        Token(TokenType.NUMBER, "300"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.VAR, "Var"),
        Token(TokenType.IDENTIFIER, "a1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "b2"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.BEGIN, "Begin"),
        Token(TokenType.READ, "Read"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "A1"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.IDENTIFIER, "b2"),
        Token(TokenType.BECOMES, ":="),
        Token(TokenType.IDENTIFIER, "a1"),
        Token(TokenType.PLUS, "+"),
        Token(TokenType.IDENTIFIER, "num1"),
        Token(TokenType.PLUS, "+"),
        Token(TokenType.IDENTIFIER, "num2"),
        Token(TokenType.PLUS, "+"),
        Token(TokenType.IDENTIFIER, "num3"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.WRITE, "write"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "A1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "B2"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.END, "End"),
        Token(TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_multi_line_const_var():
    result = get_tokens(code_multi_line_const_var)
    expected = [
        Token(TokenType.CONST, "Const"),
        Token(TokenType.IDENTIFIER, "num1"),
        Token(TokenType.EQUAL, "="),
        Token(TokenType.NUMBER, "100"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "num2"),
        Token(TokenType.EQUAL, "="),
        Token(TokenType.NUMBER, "200"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.VAR, "Var"),
        Token(TokenType.IDENTIFIER, "a1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "a2"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "b1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "b2"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.BEGIN, "Begin"),
        Token(TokenType.READ, "Read"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "A1"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.READ, "Read"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "a2"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.IDENTIFIER, "b1"),
        Token(TokenType.BECOMES, ":="),
        Token(TokenType.IDENTIFIER, "a1"),
        Token(TokenType.MINUS, "-"),
        Token(TokenType.IDENTIFIER, "nUm1"),
        Token(TokenType.ASTERISK, "*"),
        Token(TokenType.IDENTIFIER, "num2"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.IDENTIFIER, "B2"),
        Token(TokenType.BECOMES, ":="),
        Token(TokenType.IDENTIFIER, "A2"),
        Token(TokenType.MINUS, "-"),
        Token(TokenType.IDENTIFIER, "num1"),
        Token(TokenType.ASTERISK, "*"),
        Token(TokenType.IDENTIFIER, "NuM2"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.WRITE, "write"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "A1"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "b1"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.WRITE, "write"),
        Token(TokenType.LEFT_PARENTHESIS, "("),
        Token(TokenType.IDENTIFIER, "a2"),
        Token(TokenType.COMMA, ","),
        Token(TokenType.IDENTIFIER, "B2"),
        Token(TokenType.RIGHT_PARENTHESIS, ")"),
        Token(TokenType.SEMICOLON, ";"),
        Token(TokenType.END, "End"),
        Token(TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected
