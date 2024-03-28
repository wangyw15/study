import lexer

code = """
Const num=100;
Var a1,b2;
Begin
    Read(A1);
    b2:=a1+num;
    write(A1,B2);
End.
    """

result = lexer.count_identifiers(code)
for identifier, count in result.items():
    print(f"({identifier}, {count})")
