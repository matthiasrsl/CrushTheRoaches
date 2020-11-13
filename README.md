# Crush The Roaches

This is a simple 2D game for Nintendo Game Boy Advance.

## Build

You will need devkitPro to compile on an Unix-like system:

1. Download devkitPro pacman ([.deb](https://github.com/devkitPro/pacman/releases/tag/v1.0.2))

2. Install:
```
sudo apt install gdebi
sudo gdebi devkitpro-pacman.amd64.deb 
dkp-pacman
sudo dkp-pacman -S gba-dev
```

3. Build the game
```
make build
```

## Run

To run the game on a computer You will need the mGBA emulator. Downloads are available on the [mGBA website](https://mgba.io/downloads.html)

Then, run the game:
```
make run
```
