#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <hyperspace_navigator.hpp>
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

//TODO, Custom type casters for Map and Navigator, see: https://pybind11.readthedocs.io/en/stable/advanced/cast/custom.html
namespace hyperspace_navigator {

std::vector<std::vector<uint64_t>> fastestRoute(std::vector<float> space, const std::vector<uint64_t> space_layout) {
    SpaceMap map = SpaceMap(space.data(), SpaceLayout(space_layout));
    NavigationPath navigationPath = map.fastestRoute(map.spaceStart(), map.spaceEnd());
    return navigationPath.indexes();
}

float routeTime(std::vector<float> space, std::vector<std::vector<uint64_t>> indexes, const std::vector<uint64_t> space_layout) {
    SpaceMap map = SpaceMap(space.data(), SpaceLayout(space_layout));
    NavigationPath path = map.navigationPath(indexes);
    return map.time(path);
}

}

namespace py = pybind11;

PYBIND11_MODULE(hyperspace_navigator, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: hyperspace_navigator

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("fastestRoute", &hyperspace_navigator::fastestRoute, R"pbdoc(
        Calculates the fastest route given a space and its layout
        returns a navigationPath

    )pbdoc");

    m.def("routeTime", &hyperspace_navigator::routeTime, R"pbdoc(
        Given a navigationPath and a space it returns the time to navigate through this path in the space
    )pbdoc");


#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
