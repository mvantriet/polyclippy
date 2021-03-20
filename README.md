# PolyClippy
CPP lib providing polygon clipping functions using the [Sutherland–Hodgman algorithm](https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm).

## Build

### Dependencies
1. cmake
2. build-essentials (linux), MinGW (windows), Xcode (OSX)

### Build scripts
Call the rebuild.sh script in the [scripts](scripts/) folder.
```sh
# builds a release build for darwin. Artifacts are in the dist folder
./scripts/rebuild.sh darwin release 
```

## Test
Call the test.sh script in the [scripts](scripts/) folder.
```sh
# builds a debug build for darwin and runs ctest
./scripts/test.sh darwin debug
```

## Install
Install the library using the install.sh script in the [scripts](scripts/) folder. This script builds the project and calls make install. The library and header files will be put in /usr/local, therefore you need to run this script as sudo.
```sh
# builds a release build for darwin and runs make install
sudo ./scripts/install.sh darwin release
```

## Usage
First install the library as per instructions in the Section above. 

An example program (polyclippyExample.cpp) using PolyClippy is shown below.

```cpp
#include <iostream>
#include "polyclippy/Polygon.h"

int main(void) {
    Polygon* p_subject_polygon;
	Polygon* p_clip_polygon;
	Polygon* p_result_polygon;
	unsigned int i;

	std::cout << "polyclippy example" << std::endl;

	p_subject_polygon = new Polygon(3);
	p_clip_polygon = new Polygon(3);
	p_subject_polygon->add_edge(0,0,6,0,0);
	p_subject_polygon->add_edge(6,0,6,3,1);
	p_subject_polygon->add_edge(6,3,0,0,2);

	p_clip_polygon->add_edge(2,2,8,2,0);
	p_clip_polygon->add_edge(8,2,8,5,1);
	p_clip_polygon->add_edge(8,5,2,2,2);

	p_result_polygon = p_subject_polygon->intersect(p_clip_polygon);
	std::cout << "Result polygon contains " << p_result_polygon->get_nof_edges() << " edges" << std::endl;
	for (i = 0; i < p_result_polygon->get_nof_edges(); i++)
	{
		Edge* p = p_result_polygon->get_edge(i);
		std::cout << "E(" << i << ") ( " << p->getP1()->getX() << "," << p->getP1()->getY() << ") - (" << p->getP2()->getX() << "," << p->getP2()->getY() << ")" << std::endl;
	}
}
```

In order to build and run the example use the command below. If you are getting linking errors check if the installation was succesfull (see te above Install section).
```sh
g++ -o polyclippyExample ./polyclippyExample.cpp -lpolyclippy
./polyclippyExample
```

This will render output as follows:
```sh
polyclippy example
Result polygon contains 3 edges
E(0) ( 6,2) - (6,3)
E(1) ( 6,3) - (4,2)
E(2) ( 4,2) - (6,2)
```

## Examples
See the test suite in the [test folder](test/) folder of this repo.

## Contributing
See [CONTRIBUTING](CONTRIBUTING.md).