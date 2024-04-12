import re

from compiler.types import TokenType, Token

_procedure_end_pattern = r"end[;.]"
_use_identifier_pattern = r"([^\w]|){}([^\w]|)"


def get_defined_identifiers(code: str) -> list[str]:
    identifiers: list[str] = []
    lines = code.split("\n")

    # for multiline definition
    identifier_definition = False
    for line in lines:
        # skip empty line
        if not line.strip():
            continue
        # ignores case for now
        lower_line = line.lower()
        # define only occurs before "begin"
        if lower_line.strip() == "begin":
            break
        # define statement
        if lower_line.startswith("const"):
            identifier_definition = True
            lower_line = lower_line[5:].strip()
        elif lower_line.startswith("var"):
            identifier_definition = True
            lower_line = lower_line[3:].strip()
        # skip if not in define statement
        if not identifier_definition:
            continue
        # definition statement ends at semicolon
        if lower_line.endswith(";"):
            identifier_definition = False
            lower_line = lower_line[:-1]
        # multiple identifiers
        current_identifiers = lower_line.split(",")
        for current_identifier in current_identifiers:
            # comma at EOL
            if not current_identifier.strip():
                continue
            # with init value
            if "=" in current_identifier:
                current_identifier = current_identifier.split("=")[0].strip()
            else:
                current_identifier = current_identifier.strip()
            # test if the identifier is valid
            if re.fullmatch(TokenType.IDENTIFIER.value, current_identifier, re.IGNORECASE):
                identifiers.append(current_identifier)
            else:
                raise SyntaxError("Invalid identifier: " + current_identifier)
    return identifiers


def count_identifiers(code: str) -> dict[str, int]:
    identifiers = get_defined_identifiers(code)
    # first appears in definition
    result: dict[str, int] = {i: 1 for i in identifiers}
    lines = code.split("\n")

    # define statement at start
    in_code_section = False
    for line in lines:
        # ignores case for now
        lower_line = line.lower().strip()
        # start code section
        if not in_code_section:
            if lower_line == "begin":
                in_code_section = True
            continue
        # end code section
        if re.fullmatch(_procedure_end_pattern, lower_line, re.IGNORECASE):
            in_code_section = False
            continue
        # find identifier
        for identifier in identifiers:
            if re.search(_use_identifier_pattern.format(identifier), lower_line, re.IGNORECASE):
                result[identifier] += 1
    return result


def is_token_boundary(char: str, next_char: str) -> bool:
    boundary_chars = list("+-*/()=.:;,")
    return (
        re.fullmatch(TokenType.IDENTIFIER.value, char, re.IGNORECASE)
        and next_char in boundary_chars
        or char in boundary_chars
        and re.fullmatch(TokenType.IDENTIFIER.value, next_char, re.IGNORECASE)
        or re.fullmatch(TokenType.NUMBER.value, char, re.IGNORECASE)
        and next_char in boundary_chars
        or char in boundary_chars
        and re.fullmatch(TokenType.NUMBER.value, next_char, re.IGNORECASE)
        or char in boundary_chars
        and next_char in boundary_chars
        or char.isspace()
        or next_char.isspace()
    )


def get_tokens(code: str) -> list[Token]:
    result: list[Token] = []

    tokens: list[str] = []
    # spilt codes
    symbol_tmp = ""
    code = code + " "  # for enumerate
    for index, char in enumerate(code[:-1]):
        char: str
        if not char.isspace():
            symbol_tmp += char

        # detect word boundary
        if is_token_boundary(char, code[index + 1]):
            if symbol_tmp:
                tokens.append(symbol_tmp)
                symbol_tmp = ""

    # combine multi-char tokens
    tokens.append("")  # for last token
    processed_symbols: list[str] = []
    for index, symbol in enumerate(tokens[:-1]):
        if symbol + tokens[index + 1] == ":=":
            processed_symbols.append(":=")
            continue
        elif tokens[index - 1] + symbol == ":=":
            continue
        if symbol:
            processed_symbols.append(symbol)
    tokens = processed_symbols

    # detect tokens
    for symbol in tokens:
        symbol_type = None
        for t in TokenType:
            if re.fullmatch(t.value, symbol, re.IGNORECASE):
                symbol_type = t
                break
        if not symbol_type:
            if re.fullmatch(TokenType.IDENTIFIER.value, symbol, re.IGNORECASE):
                symbol_type = TokenType.IDENTIFIER
            else:
                symbol_type = TokenType.UNKNOWN
        if symbol_type:
            result.append(Token(symbol_type, symbol))

    return result


__all__ = [
    "get_defined_identifiers",
    "count_identifiers",
    "get_tokens",
]
