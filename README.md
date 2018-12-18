# Printing the ACPI Namespace with FreeBSD

The ACPICA spec provides a way to access Plug-n-Play devices on a variety of systems. The FreeBSD ACPI driver uses this to detect what hardware is present on the system and provide drivers to match it. While the system might autodetect ACPI objects, names, and PnP id's, the programmer does not. This kernel module prints out the entire ACPI namespace (including hardware and unique ID's) so that developers can quickly tell the ACPI devices present on the system.

## Compile

FreeBSD kernel modules can be compile using `make` (specifically bmake). A quickstart set of commands is:
* cd acpi_print
* make
* kldload ./acpi_print.ko
* kldunload acpi_print

A list of ACPI objects and their ID's should hopefully be printed. Because this module doesn't do anything, it uses the default device attach methods which will result in `ENXIO` error codes being returned. Obviously this module is a bit of a hack and should never be used in anything important. Its one job is to show the user the ACPI tree and hopefully take a little mystery out of their desktop.