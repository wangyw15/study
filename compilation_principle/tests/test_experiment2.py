from . import code_helper
from compiler.lexer import get_symbols, SymbolType

code_example = code_helper.get_test_code("experiment2_example")
code_valid_identifiers = code_helper.get_test_code("single_line_identifiers")
code_multi_line_var = code_helper.get_test_code("multi_line_var")
code_multi_line_const = code_helper.get_test_code("multi_line_const")
code_multi_line_const_var = code_helper.get_test_code("multi_line_const_var")


def test_get_symbols_example():
    result = get_symbols(code_example)
    expected = [
        (SymbolType.CONST, "const"),
        (SymbolType.IDENTIFIER, "a"),
        (SymbolType.EQUAL, "="),
        (SymbolType.NUMBER, "10"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.VAR, "var"),
        (SymbolType.IDENTIFIER, "b"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "c"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.BEGIN, "begin"),
        (SymbolType.READ, "read"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "b"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.IDENTIFIER, "c"),
        (SymbolType.BECOMES, ":="),
        (SymbolType.IDENTIFIER, "a"),
        (SymbolType.PLUS, "+"),
        (SymbolType.IDENTIFIER, "b"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.WRITE, "write"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "c"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.END, "end"),
        (SymbolType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_valid_identifiers():
    result = get_symbols(code_valid_identifiers)
    expected = [
        (SymbolType.CONST, "Const"),
        (SymbolType.IDENTIFIER, "num"),
        (SymbolType.EQUAL, "="),
        (SymbolType.NUMBER, "100"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.VAR, "Var"),
        (SymbolType.IDENTIFIER, "a_1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "b2_"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "b_3"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "_b3"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "a1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "B2"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.BEGIN, "Begin"),
        (SymbolType.READ, "Read"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "A1"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.IDENTIFIER, "b2"),
        (SymbolType.BECOMES, ":="),
        (SymbolType.IDENTIFIER, "a1"),
        (SymbolType.PLUS, "+"),
        (SymbolType.IDENTIFIER, "num"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.WRITE, "write"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "A1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "B2"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.END, "End"),
        (SymbolType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_multi_line_var():
    result = get_symbols(code_multi_line_var)
    expected = [
        (SymbolType.CONST, "Const"),
        (SymbolType.IDENTIFIER, "num"),
        (SymbolType.EQUAL, "="),
        (SymbolType.NUMBER, "100"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.VAR, "Var"),
        (SymbolType.IDENTIFIER, "a1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "a2"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "b2"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.BEGIN, "Begin"),
        (SymbolType.READ, "Read"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "A1"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.READ, "Read"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "a2"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.IDENTIFIER, "b2"),
        (SymbolType.BECOMES, ":="),
        (SymbolType.IDENTIFIER, "a1"),
        (SymbolType.PLUS, "+"),
        (SymbolType.IDENTIFIER, "A2"),
        (SymbolType.PLUS, "+"),
        (SymbolType.IDENTIFIER, "num"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.WRITE, "write"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "A1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "B2"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.END, "End"),
        (SymbolType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_multi_line_const():
    result = get_symbols(code_multi_line_const)
    expected = [
        (SymbolType.CONST, "Const"),
        (SymbolType.IDENTIFIER, "num1"),
        (SymbolType.EQUAL, "="),
        (SymbolType.NUMBER, "100"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "num2"),
        (SymbolType.EQUAL, "="),
        (SymbolType.NUMBER, "200"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "num3"),
        (SymbolType.EQUAL, "="),
        (SymbolType.NUMBER, "300"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.VAR, "Var"),
        (SymbolType.IDENTIFIER, "a1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "b2"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.BEGIN, "Begin"),
        (SymbolType.READ, "Read"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "A1"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.IDENTIFIER, "b2"),
        (SymbolType.BECOMES, ":="),
        (SymbolType.IDENTIFIER, "a1"),
        (SymbolType.PLUS, "+"),
        (SymbolType.IDENTIFIER, "num1"),
        (SymbolType.PLUS, "+"),
        (SymbolType.IDENTIFIER, "num2"),
        (SymbolType.PLUS, "+"),
        (SymbolType.IDENTIFIER, "num3"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.WRITE, "write"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "A1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "B2"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.END, "End"),
        (SymbolType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected


def test_get_symbols_multi_line_const_var():
    result = get_symbols(code_multi_line_const_var)
    expected = [
        (SymbolType.CONST, "Const"),
        (SymbolType.IDENTIFIER, "num1"),
        (SymbolType.EQUAL, "="),
        (SymbolType.NUMBER, "100"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "num2"),
        (SymbolType.EQUAL, "="),
        (SymbolType.NUMBER, "200"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.VAR, "Var"),
        (SymbolType.IDENTIFIER, "a1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "a2"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "b1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "b2"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.BEGIN, "Begin"),
        (SymbolType.READ, "Read"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "A1"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.READ, "Read"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "a2"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.IDENTIFIER, "b1"),
        (SymbolType.BECOMES, ":="),
        (SymbolType.IDENTIFIER, "a1"),
        (SymbolType.MINUS, "-"),
        (SymbolType.IDENTIFIER, "nUm1"),
        (SymbolType.TIMES, "*"),
        (SymbolType.IDENTIFIER, "num2"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.IDENTIFIER, "B2"),
        (SymbolType.BECOMES, ":="),
        (SymbolType.IDENTIFIER, "A2"),
        (SymbolType.MINUS, "-"),
        (SymbolType.IDENTIFIER, "num1"),
        (SymbolType.TIMES, "*"),
        (SymbolType.IDENTIFIER, "NuM2"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.WRITE, "write"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "A1"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "b1"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.WRITE, "write"),
        (SymbolType.LEFT_PARENTHESIS, "("),
        (SymbolType.IDENTIFIER, "a2"),
        (SymbolType.COMMA, ","),
        (SymbolType.IDENTIFIER, "B2"),
        (SymbolType.RIGHT_PARENTHESIS, ")"),
        (SymbolType.SEMICOLON, ";"),
        (SymbolType.END, "End"),
        (SymbolType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected
