import hyperspace_navigator as m
import pytest


@pytest.fixture
def space():
    return [0, 1, 3,
            5, 2, 8,
            1, 5, 6]


@pytest.fixture
def fastest_route():
    return [[0, 0], [1, 0], [1, 1], [1, 2], [2, 2]]


def test_2d_3x3_space(space, fastest_route):
    navigation_path = m.fastestRoute(space)
    assert m.__version__ == "0.0.1"
    assert len(navigation_path) == 5
    assert navigation_path == fastest_route


def test_get_navigation_time(space, fastest_route):
    navigation_time = m.routeTime(space, fastest_route)
    assert navigation_time is not None
    assert navigation_time == 14
