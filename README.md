# YADL - Yet Another Doom Launcher

> YADL is a small cross-platform GUI launcher for Doom and other Doom Engine-based games (Doom 2, Heretic, Hexen) and mods (currently WAD and PK3).

## Features
* Allows to easily switch between sourceports, IWADs, and mods (PWADs and PK3s).
* Automatically supports launching Windows sourceports on Linux (requires [Wine](https://www.winehq.org/)).
* Settings for skill level, compatibility level (if applicable), fast and co-op exclusive monsters.
* Warp directly to any level available.
* Automatically saves the last settings when closing.
* Stores info and custom command-line parameters for each sourceport and IWAD.
* Saves presets (settings and modlists), and allows the user to easily filter through them.

## Usage
### Sourceports and IWADs
The Ports/IWADs tab allows you to specify the location, name and additional command-line parameters for each sourceport and IWAD you wish to use, and automatically persists the data. Note that the launcher does not manage the files, but rather saves their path: if a sourceport or IWAD is inaccessible, it will trigger an error message when attempting to launch.

<p align="center">
    <img src="https://i.imgur.com/1lWpezD.png" alt="Sourceports and IWADs tab">
</p>

### Launching the game
Once you have your sourceports and IWADs set up, the Launcher tab allows you to choose which ones to launch, along with any mod files (PWAD and PK3, currently), and game settings such as skill level, compatibility level (for PrBoom compatible ports), fast-monsters, and any additional command-line parameters. It also allows the user to warp directly to any maps available in the loaded mods (currently only for PWADs). If no maps are found in the mod files, the map selection defaults to the IWAD's map list.

<p align="center">
    <img src="https://i.imgur.com/C5QzslQ.png" alt="Launcher tab">
</p>

### Saving presets
YADL also allows the user to save the current combination of IWAD, sourceport, settings and mods as a preset, under a given name. These presets are available in the Presets tab, and can easily be loaded back into the launcher. If your list of presets is large enough, you can also filter them using the search box at the bottom of the tab. Note that if you save a new preset with an already existing name, it will be overwritten.

<p align="center">
    <img src="https://i.imgur.com/lVv7UFZ.png" alt="Presets tab">
</p>

## Installation
### Pre-compiled binaries
Coming soon.

### Compiling from source
This project requires [Qt6](https://www.qt.io/) and qmake, and has been tested with Qt 6.2.0 LTS and newer. In order to compile it, clone the repository, open the command-line, and input:

```
$ cd <repo-folder>
$ mkdir build && cd build
$ qmake6 -makefile ../yadl.pro
$ make
```

Alternatively, one may use [Qt Creator](https://www.qt.io/product/development-tools) to open the project (by opening ```yadl.pro```) and build it directly from there.

## License
This is free software: you can modify and/or redistribute it under the terms of the Lesser GNU Public License version 3. More information can be found in [LICENSE](https://github.com/predros/yadl/blob/main/LICENSE), or on [GNU's website](https://www.gnu.org/licenses/lgpl-3.0.en.html).

## Links and additional info
* [Github repository](https://github.com/predros/yadl)
