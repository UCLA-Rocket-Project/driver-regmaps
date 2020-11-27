# driver-regmaps
A monorepo for some low-level drivers for various sensors.

## regmap
This is a reduced form of the Linux regmap abstraction, useful for devices
with a lot of complex options

## Drivers
Notes: Within each folder, there are files called `lowlevel` and `userlevel`.
Lowlevel files are nothing more than human-readable access to registers.

Userlevel files are meant to provide a more human interface to each device, by
storing state internally and returning usable values.
