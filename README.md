DWM
===========

This repository holds the source for my build of dwm.

It provides:

  * A simple working enviornment for people running Xorg
  * A base to work off of for a more featureful dwm build
  * An example of how [GoDSB](https://github.com/ChristianHering/GoDSB) can be used within dwm

Table of Contents:

  * [About](#about)
  * [Installing and Compiling from Source](#installing-and-compiling-from-source)
  * [Contributing](#contributing)
  * [License](#license)

About
-----

[Dwm](https://dwm.suckless.org/) is a dynamic, source based window manager for [X11](https://www.x.org/wiki/). It relys heavily on keybindings to do basic operations, and promotes workflow efficiency.

Installing and Compiling from Source
------------

If you're looking to compile from source, you'll need the following:

  * [Git](https://archlinux.org/packages/extra/x86_64/git/), [Make](https://archlinux.org/packages/core/x86_64/make/) and [GCC](https://archlinux.org/packages/core/x86_64/gcc/) installed from arch's [base-devel](https://archlinux.org/groups/x86_64/base-devel/) package group. Your distribution will likely have similar packages.
  * [Xlib header files](https://archlinux.org/packages/extra/x86_64/libx11/) on the system.
  * [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) if you want colored emoji rendering (not having this may induce crashes when emoji's are rendered unless you uncomment the 'iscol' block of code in drw.c)
  * [noto-fonts-emoji](https://archlinux.org/packages/extra/any/noto-fonts-emoji/) or [another font](https://archlinux.org/packages/community/any/ttf-joypixels/) that supports unicode emojis. Fonts can be changed in [config.h](config.h)

First build dwm so we can execute it on X startup:

  * `make clean install`

Add the following to your .xinitrc file:

  * `exec dbus-launch dwm`

Using 'dbus-launch' will allow tools like [flameshot](https://github.com/flameshot-org/flameshot) to work out of the box. You can run dwm without it, but may run into issues with some applications. (particularly screen capturing applications) Similar issues are encountered when using ssh-agent as well.

If you would like dwm to restart automatically on exit (useful during development) add this instead:

```Bash
while true; do
	exec dbus-launch dwm >/dev/null 2>&1
done
```

Then just quit out of your current enviornment and login with dwm! Win + T gets you a terminal; any other keybindings can be found in [config.h](config.h)

Contributing
------------

Contributions are always welcome. If you're interested in contributing, send me an email or submit a PR.

License
-------

Feel free to use this project in any way you like. Please refer to the [license](/docs/LICENSE) file for more information.
