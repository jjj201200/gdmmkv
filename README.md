# Win64 MMKV Storage Plugin for Godot

This is an MMKV-based storage plugin designed for the Godot game engine, implemented in C++ and compiled as a DLL. It is integrated into Godot using the GDExtension system and provides basic interfaces for real-time data storage.

## Features

- High-performance storage powered by MMKV.
- Seamlessly integrates with the Godot engine through GDExtension.
- Simple APIs for storing and retrieving data efficiently.

## Installation

1. Clone this repository to your Godot project.
2. Compile the C++ code into a DLL (specific instructions can be found in the build directory).
3. Import the DLL into your Godot project using GDExtension.
4. Add `demo/bin` to your project settings.

## Usage

1. Call the provided APIs in your scripts to store or retrieve data.
2. Example:
   var storage = GDMMKV.new()
   storage.set_bool("bool", false)
   var result = storage.get_bool("bool")
   print(result)

## Compilation Instructions

1. Create a folder named `godot-cpp`.
2. Use Git to clone the specific branch of the [godot-cpp repository](https://github.com/godotengine/godot-cpp) corresponding to your target Godot version (e.g., 4.3) into the `godot-cpp` folder:
   ```bash
   $ git clone -b 4.3 https://github.com/godotengine/godot-cpp.git godot-cpp
   ```
3. Open a terminal in the `godot-cpp` directory and run the following command:
   ```bash
   $ scons -jN
   ```
   Replace `N` with the number of CPU cores available on your machine to optimize the build process.

## Dependencies

- Tencent's MMKV
- Godot 4.x with GDExtension support

## License

This plugin is licensed under the MIT License. For more details, see the LICENSE file.
