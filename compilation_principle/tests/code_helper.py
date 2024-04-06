from pathlib import Path

test_code_path = Path(__file__).parent.parent / "test_codes"


def get_test_code(name: str) -> str:
    """
    Get test code by name
    :param name: test code name
    :return: test code
    """
    code_path = test_code_path / f"{name}.pl0"
    if not code_path.exists():
        raise FileNotFoundError(f"Test code {name} not found")
    with code_path.open("r") as f:
        return f.read()
