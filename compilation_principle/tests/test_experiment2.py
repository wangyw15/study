from . import code_helper
from compiler import lexer

code_example = code_helper.get_test_code("experiment2_example")


def test_example():
    result = lexer.get_symbols(code_example)
    expected = [
        (lexer.SymbolType.CONST, "const"),
        (lexer.SymbolType.IDENTIFIER, "a"),
        (lexer.SymbolType.EQUAL, "="),
        (lexer.SymbolType.NUMBER, "10"),
        (lexer.SymbolType.SEMICOLON, ";"),
        (lexer.SymbolType.VAR, "var"),
        (lexer.SymbolType.IDENTIFIER, "b"),
        (lexer.SymbolType.COMMA, ","),
        (lexer.SymbolType.IDENTIFIER, "c"),
        (lexer.SymbolType.SEMICOLON, ";"),
        (lexer.SymbolType.BEGIN, "begin"),
        (lexer.SymbolType.READ, "read"),
        (lexer.SymbolType.LEFT_PARENTHESIS, "("),
        (lexer.SymbolType.IDENTIFIER, "b"),
        (lexer.SymbolType.RIGHT_PARENTHESIS, ")"),
        (lexer.SymbolType.SEMICOLON, ";"),
        (lexer.SymbolType.IDENTIFIER, "c"),
        (lexer.SymbolType.BECOMES, ":="),
        (lexer.SymbolType.IDENTIFIER, "a"),
        (lexer.SymbolType.PLUS, "+"),
        (lexer.SymbolType.IDENTIFIER, "b"),
        (lexer.SymbolType.SEMICOLON, ";"),
        (lexer.SymbolType.WRITE, "write"),
        (lexer.SymbolType.LEFT_PARENTHESIS, "("),
        (lexer.SymbolType.IDENTIFIER, "c"),
        (lexer.SymbolType.RIGHT_PARENTHESIS, ")"),
        (lexer.SymbolType.SEMICOLON, ";"),
        (lexer.SymbolType.END, "end"),
        (lexer.SymbolType.PERIOD, "."),
    ]

    assert len(result) == len(expected)
    assert result == expected
