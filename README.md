# fl2json

Parses fluid files and outputs json.

## Dependencies
A C++17 capable compiler. This library uses nlohmann/json for json generation, and is grabbed automatically by the CMake script.

## Building
After cloning the repo:
```
cmake -Bbin
cmake --build bin --parallel
```

## Running
```
fl2json /path/to/fluid/file.fl > /path/to/json/file.json
```