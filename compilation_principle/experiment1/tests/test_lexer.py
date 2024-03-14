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
    result1 = lexer.get_defined_identifiers(code_normal)
    assert "num" in result1
    assert "a1" in result1
    assert "b2" in result1
    # assert result["num"] == 2
    # assert result["a1"] == 4
    # assert result["b2"] == 3


def test_get_defined_identifiers_multiline_var():
    result2 = lexer.get_defined_identifiers(code_multiline_var)
    assert "num" in result2
    assert "a1" in result2
    assert "a2" in result2
    assert "b2" in result2


def test_get_defined_identifiers_multiline_var_const():
    result3 = lexer.get_defined_identifiers(code_multiline_const)
    assert "num1" in result3
    assert "num2" in result3
    assert "num3" in result3
    assert "a1" in result3
    assert "b2" in result3


def test_get_defined_identifiers_mixed_multiline_var_const():
    result4 = lexer.get_defined_identifiers(code_mixed_multiline)
    assert "num1" in result4
    assert "num2" in result4
    assert "a1" in result4
    assert "a2" in result4
    assert "b1" in result4
    assert "b2" in result4


def test_get_defined_identifier_invalid_identifier():
    with pytest.raises(SyntaxError):
        lexer.get_defined_identifiers(code_invalid_identifier)
