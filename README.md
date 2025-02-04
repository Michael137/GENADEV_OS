# GENADEV_OS

#### _An AArch64 hobbyist OS for the Raspberry Pi 3 B+ made with ❤️ by the [German Low-Level discord server community](https://disboard.org/server/819953014953476126) written in C and AArch64 Assembly_

<a href="https://discord.gg/jPNNeZqMwR"> <img src="https://img.shields.io/discord/819953014953476126?label=discord"> <img src="https://img.shields.io/github/license/GENADEV/GENADEV_OS"> </a>

## Screenshots
<img src="https://github.com/GENADEV/GENADEV_OS/blob/main/screenshots/uart%20output.png"> </a>
<img src="https://github.com/GENADEV/GENADEV_OS/blob/main/screenshots/framebuffer.png"> </a>

## Emulation on Linux

- Packages you need
  - Debian based linux distributions:
    - git
    - qemu-system-arm
    - make
    - libncurses5
    - astyle
  - Arch based linux distributions:
    - git
    - qemu
    - qemu-arch-extra
    - make
    - ncurses
    - astyle

- To run it
  - git clone https://github.com/GENADEV/GENADEV_OS.git --recursive
  - cd GENADEV_OS
  - make setup (untar the cross compiler)
  - make run   (compile, link and run)
  - By default `make run` will use the uart0 for debugging output, you can change this to use the mini uart aswell via `make run_uart1`

## Contributing

For those interested in contributing, please refer to the [contributing guidelines](https://github.com/GENADEV/GENADEV_OS/blob/main/CONTRIBUTING.md).
