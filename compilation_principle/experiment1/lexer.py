import re

_valid_identifier_pattern = r"[a-z_]\w*"
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
            if re.fullmatch(_valid_identifier_pattern, current_identifier):
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
        if not in_code_section:
            if lower_line == "begin":
                in_code_section = True
            continue
        if re.fullmatch(_procedure_end_pattern, lower_line):
            in_code_section = False
            continue
        for identifier in identifiers:
            if re.search(_use_identifier_pattern.format(identifier), lower_line):
                result[identifier] += 1
    return result


__all__ = [
    "get_defined_identifiers"
]
