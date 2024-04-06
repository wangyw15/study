from pathlib import Path


def get_tests_path() -> Path:
    return Path(__file__).parent


def get_test_names() -> list[str]:
    tests_path = get_tests_path()
    return [p.stem[5:] for p in tests_path.glob("test_*.py")]
