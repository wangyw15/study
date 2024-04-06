import re
import enum

_procedure_end_pattern = r"end[;.]"
_use_identifier_pattern = r"([^\w]|){}([^\w]|)"


class SymbolType(enum.Enum):
    # operators
    PLUS = r"\+"
    MINUS = "-"
    TIMES = r"\*"
    SLASH = r"\/"
    # symbols
    LEFT_PARENTHESIS = r"\("
    RIGHT_PARENTHESIS = r"\)"
    EQUAL = "="
    PERIOD = r"\."
    BECOMES = ":="
    SEMICOLON = ";"
    COMMA = ","
    # keywords
    CONST = "const"
    VAR = "var"
    BEGIN = "begin"
    END = "end"
    # built-in functions
    READ = "read"
    WRITE = "write"
    # identifiers
    IDENTIFIER = r"[a-z_]\w*"
    NUMBER = r"\d+"


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
            if re.fullmatch(SymbolType.IDENTIFIER.value, current_identifier):
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
        if re.fullmatch(_procedure_end_pattern, lower_line):
            in_code_section = False
            continue
        # find identifier
        for identifier in identifiers:
            if re.search(_use_identifier_pattern.format(identifier), lower_line):
                result[identifier] += 1
    return result


def is_symbol_boundary(char: str, next_char: str) -> bool:
    boundary_chars = list("+-*/()=.:;,")
    return (
        re.fullmatch(SymbolType.IDENTIFIER.value, char)
        and next_char in boundary_chars
        or char in boundary_chars
        and re.fullmatch(SymbolType.IDENTIFIER.value, next_char)
        or re.fullmatch(SymbolType.NUMBER.value, char)
        and next_char in boundary_chars
        or char in boundary_chars
        and re.fullmatch(SymbolType.NUMBER.value, next_char)
        or char in boundary_chars
        and next_char in boundary_chars
        or char.isspace()
        or next_char.isspace()
    )


def get_symbols(code: str) -> list[tuple[SymbolType, str]]:
    result: list[tuple[SymbolType, str]] = []
    identifiers = get_defined_identifiers(code)

    symbols: list[str] = []
    # spilt symbols
    symbol_tmp = ""
    code = code + " "  # for enumerate
    for index, char in enumerate(code[:-1]):
        char: str
        if not char.isspace():
            symbol_tmp += char

        # detect word boundary
        if is_symbol_boundary(char, code[index + 1]):
            if symbol_tmp:
                symbols.append(symbol_tmp)
                symbol_tmp = ""

    # combine symbols
    symbols += [""]  # for last symbol
    for index, symbol in enumerate(symbols[:-1]):
        if symbol == ":" and symbols[index + 1] == "=":
            symbols[index] = ":="
            del symbols[index + 1]
    symbols.pop()  # remove last empty symbol

    # detect symbols
    for symbol in symbols:
        symbol_type = None
        if symbol.lower() in identifiers:
            symbol_type = SymbolType.IDENTIFIER
        else:
            for t in SymbolType:
                if re.fullmatch(t.value, symbol):
                    symbol_type = t
                    break
        if symbol_type:
            result.append((symbol_type, symbol))

    return result


__all__ = [
    "get_defined_identifiers",
    "count_identifiers",
    "get_symbols",
]
