import lexer
import pytest

code_normal = """
Const num=100;
Var a1,b2;
Begin
    Read(A1);
    b2:=a1+num;
    write(A1,B2);
End.
    """

code_valid_identifiers = """
Const num=100;
Var a_1,b2_,b_3,_b3,a1,B2;
Begin
    Read(A1);
    b2:=a1+num;
    write(A1,B2);
End.
    """

code_multiline_var = """
Const num=100;
Var a1,
    a2,
    b2;
Begin
    Read(A1);
    Read(a2);
    b2:=a1+A2+num;
    write(A1,B2);
End.
    """

code_multiline_const = """
Const num1=100,
      num2=200,
      num3=300;
Var a1,b2;
Begin
    Read(A1);
    b2:=a1+num1+num2+num3;
    write(A1,B2);
End.
    """

code_mixed_multiline = """
Const num1=100, num2=200;
Var a1, a2,
    b1, b2;
Begin
    Read(A1);
    Read(a2);
    b1:=a1+nUm1+num2;
    B2:=A2+num1+NuM2;
    write(A1,b1);
    write(a2,B2);
End.
    """

code_invalid_identifier = """
Const num=100;
Var a1,b2,2b;
Begin
    Read(A1);
    b2:=a1+num;
    write(A1,B2);
End.
    """

code_undefined_symbol = """
Const num=100;
Var a1,b2;
Begin
    Read(A1);
    b1:=a1+num;
    write(A1,B2);
End.
    """


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
