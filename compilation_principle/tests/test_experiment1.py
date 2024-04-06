import pytest

import test_code
from compiler import lexer

code_normal = test_code.get_test_code("experiment1_example")

code_valid_identifiers = test_code.get_test_code("single_line_identifiers")

code_multiline_var = test_code.get_test_code("multi_line_var")

code_multiline_const = test_code.get_test_code("multi_line_const")

code_mixed_multiline = test_code.get_test_code("multi_line_const_var")

code_invalid_identifier = test_code.get_test_code("invalid_identifiers")

code_undefined_symbol = test_code.get_test_code("undefined_symbol")


def test_get_defined_identifiers_normal():
    result = lexer.get_defined_identifiers(code_normal)
    assert "num" in result
    assert "a1" in result
    assert "b2" in result


def test_get_defined_identifiers_valid():
    result = lexer.get_defined_identifiers(code_valid_identifiers)
    assert "num" in result
    assert "a1" in result
    assert "b2" in result
    assert "a_1" in result
    assert "b2_" in result
    assert "b_3" in result
    assert "_b3" in result


def test_get_defined_identifiers_multiline_var():
    result = lexer.get_defined_identifiers(code_multiline_var)
    assert "num" in result
    assert "a1" in result
    assert "a2" in result
    assert "b2" in result


def test_get_defined_identifiers_multiline_var_const():
    result = lexer.get_defined_identifiers(code_multiline_const)
    assert "num1" in result
    assert "num2" in result
    assert "num3" in result
    assert "a1" in result
    assert "b2" in result


def test_get_defined_identifiers_mixed_multiline_var_const():
    result = lexer.get_defined_identifiers(code_mixed_multiline)
    assert "num1" in result
    assert "num2" in result
    assert "a1" in result
    assert "a2" in result
    assert "b1" in result
    assert "b2" in result


def test_get_defined_identifier_invalid_identifier():
    with pytest.raises(SyntaxError):
        lexer.get_defined_identifiers(code_invalid_identifier)


def test_count_identifiers_normal():
    result = lexer.count_identifiers(code_normal)
    assert result["num"] == 2
    assert result["a1"] == 4
    assert result["b2"] == 3


def test_count_identifiers_valid():
    result = lexer.count_identifiers(code_valid_identifiers)
    assert result["num"] == 2
    assert result["a1"] == 4
    assert result["b2"] == 3
    assert result["a_1"] == 1
    assert result["b2_"] == 1
    assert result["b_3"] == 1
    assert result["_b3"] == 1


def test_count_identifiers_multiline_var():
    result = lexer.count_identifiers(code_multiline_var)
    assert result["num"] == 2
    assert result["a1"] == 4
    assert result["a2"] == 3
    assert result["b2"] == 3


def test_count_identifiers_multiline_var_const():
    result = lexer.count_identifiers(code_multiline_const)
    assert result["num1"] == 2
    assert result["num2"] == 2
    assert result["num3"] == 2
    assert result["a1"] == 4
    assert result["b2"] == 3


def test_count_identifiers_mixed_multiline_var_const():
    result = lexer.count_identifiers(code_mixed_multiline)
    assert result["num1"] == 3
    assert result["num2"] == 3
    assert result["a1"] == 4
    assert result["a2"] == 4
    assert result["b1"] == 3
    assert result["b2"] == 3
