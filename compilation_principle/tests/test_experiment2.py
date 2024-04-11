from . import code_helper
from compiler.lexer import get_tokens
from compiler.types import TokenType

code_example = code_helper.get_test_code("experiment2_example")
code_valid_identifiers = code_helper.get_test_code("single_line_identifiers")
code_multi_line_var = code_helper.get_test_code("multi_line_var")
code_multi_line_const = code_helper.get_test_code("multi_line_const")
code_multi_line_const_var = code_helper.get_test_code("multi_line_const_var")


def test_get_symbols_example():
    result = get_tokens(code_example)
    expected = [
        (TokenType.CONST, "const"),
        (TokenType.IDENTIFIER, "a"),
        (TokenType.EQUAL, "="),
        (TokenType.NUMBER, "10"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.VAR, "var"),
        (TokenType.IDENTIFIER, "b"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "c"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.BEGIN, "begin"),
        (TokenType.READ, "read"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "b"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.IDENTIFIER, "c"),
        (TokenType.BECOMES, ":="),
        (TokenType.IDENTIFIER, "a"),
        (TokenType.PLUS, "+"),
        (TokenType.IDENTIFIER, "b"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.WRITE, "write"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "c"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.END, "end"),
        (TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_valid_identifiers():
    result = get_tokens(code_valid_identifiers)
    expected = [
        (TokenType.CONST, "Const"),
        (TokenType.IDENTIFIER, "num"),
        (TokenType.EQUAL, "="),
        (TokenType.NUMBER, "100"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.VAR, "Var"),
        (TokenType.IDENTIFIER, "a_1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "b2_"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "b_3"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "_b3"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "a1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "B2"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.BEGIN, "Begin"),
        (TokenType.READ, "Read"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "A1"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.IDENTIFIER, "b2"),
        (TokenType.BECOMES, ":="),
        (TokenType.IDENTIFIER, "a1"),
        (TokenType.PLUS, "+"),
        (TokenType.IDENTIFIER, "num"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.WRITE, "write"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "A1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "B2"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.END, "End"),
        (TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_multi_line_var():
    result = get_tokens(code_multi_line_var)
    expected = [
        (TokenType.CONST, "Const"),
        (TokenType.IDENTIFIER, "num"),
        (TokenType.EQUAL, "="),
        (TokenType.NUMBER, "100"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.VAR, "Var"),
        (TokenType.IDENTIFIER, "a1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "a2"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "b2"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.BEGIN, "Begin"),
        (TokenType.READ, "Read"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "A1"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.READ, "Read"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "a2"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.IDENTIFIER, "b2"),
        (TokenType.BECOMES, ":="),
        (TokenType.IDENTIFIER, "a1"),
        (TokenType.PLUS, "+"),
        (TokenType.IDENTIFIER, "A2"),
        (TokenType.PLUS, "+"),
        (TokenType.IDENTIFIER, "num"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.WRITE, "write"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "A1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "B2"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.END, "End"),
        (TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_multi_line_const():
    result = get_tokens(code_multi_line_const)
    expected = [
        (TokenType.CONST, "Const"),
        (TokenType.IDENTIFIER, "num1"),
        (TokenType.EQUAL, "="),
        (TokenType.NUMBER, "100"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "num2"),
        (TokenType.EQUAL, "="),
        (TokenType.NUMBER, "200"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "num3"),
        (TokenType.EQUAL, "="),
        (TokenType.NUMBER, "300"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.VAR, "Var"),
        (TokenType.IDENTIFIER, "a1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "b2"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.BEGIN, "Begin"),
        (TokenType.READ, "Read"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "A1"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.IDENTIFIER, "b2"),
        (TokenType.BECOMES, ":="),
        (TokenType.IDENTIFIER, "a1"),
        (TokenType.PLUS, "+"),
        (TokenType.IDENTIFIER, "num1"),
        (TokenType.PLUS, "+"),
        (TokenType.IDENTIFIER, "num2"),
        (TokenType.PLUS, "+"),
        (TokenType.IDENTIFIER, "num3"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.WRITE, "write"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "A1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "B2"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.END, "End"),
        (TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_multi_line_const_var():
    result = get_tokens(code_multi_line_const_var)
    expected = [
        (TokenType.CONST, "Const"),
        (TokenType.IDENTIFIER, "num1"),
        (TokenType.EQUAL, "="),
        (TokenType.NUMBER, "100"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "num2"),
        (TokenType.EQUAL, "="),
        (TokenType.NUMBER, "200"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.VAR, "Var"),
        (TokenType.IDENTIFIER, "a1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "a2"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "b1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "b2"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.BEGIN, "Begin"),
        (TokenType.READ, "Read"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "A1"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.READ, "Read"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "a2"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.IDENTIFIER, "b1"),
        (TokenType.BECOMES, ":="),
        (TokenType.IDENTIFIER, "a1"),
        (TokenType.MINUS, "-"),
        (TokenType.IDENTIFIER, "nUm1"),
        (TokenType.TIMES, "*"),
        (TokenType.IDENTIFIER, "num2"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.IDENTIFIER, "B2"),
        (TokenType.BECOMES, ":="),
        (TokenType.IDENTIFIER, "A2"),
        (TokenType.MINUS, "-"),
        (TokenType.IDENTIFIER, "num1"),
        (TokenType.TIMES, "*"),
        (TokenType.IDENTIFIER, "NuM2"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.WRITE, "write"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "A1"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "b1"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.WRITE, "write"),
        (TokenType.LEFT_PARENTHESIS, "("),
        (TokenType.IDENTIFIER, "a2"),
        (TokenType.COMMA, ","),
        (TokenType.IDENTIFIER, "B2"),
        (TokenType.RIGHT_PARENTHESIS, ")"),
        (TokenType.SEMICOLON, ";"),
        (TokenType.END, "End"),
        (TokenType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected
