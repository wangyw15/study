import pytest

from . import code_helper
from compiler import checker

code_example = code_helper.get_test_code("experiment3_example")
code_unpaired_parenthesis = code_helper.get_test_code("expression_unpaired_parenthesis")
code_duplicate_operators = code_helper.get_test_code("expression_duplicate_operators")
code_wrong_factor_leading = code_helper.get_test_code("expression_wrong_factor_leading")
code_invalid_token = code_helper.get_test_code("expression_invalid_token")
code_long = code_helper.get_test_code("expression_long")


def test_check_example():
    assert checker.check(code_example)


def test_check_unpaired_parenthesis():
    with pytest.raises(SyntaxError, match=r"'\(' was never closed"):
        assert not checker.check(code_unpaired_parenthesis)


def test_duplicate_operators():
    with pytest.raises(SyntaxError, match=r"invalid syntax"):
        assert not checker.check(code_duplicate_operators)


def test_wrong_factor_leading():
    with pytest.raises(SyntaxError, match=r"invalid syntax"):
        assert not checker.check(code_wrong_factor_leading)


def test_invalid_token():
    with pytest.raises(SyntaxError, match=r"invalid syntax"):
        assert not checker.check(code_invalid_token)


def test_long():
    assert checker.check(code_long)
