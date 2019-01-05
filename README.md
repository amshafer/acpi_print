# Printing the ACPI Namespace with FreeBSD

The ACPICA spec provides a way to access Plug-n-Play devices on a variety of systems. The FreeBSD ACPI driver uses this to detect what hardware is present on the system and provide drivers to match it. While the system might autodetect ACPI objects, names, and PnP id's, the programmer does not. This kernel module prints out the entire ACPI namespace (including hardware and unique ID's) so that developers can quickly tell the ACPI devices present on the system.

## Compile

FreeBSD kernel modules can be compile using `make` (specifically bmake). A quickstart set of commands is:
* cd acpi_print
* make
* kldload ./acpi_print.ko
* kldunload acpi_print

A list of ACPI objects and their ID's should hopefully be printed. Because this module doesn't do anything, it uses the default device attach methods which will result in `ENXIO` error codes being returned. Obviously this module is a bit of a hack and should never be used in anything important. Its one job is to show the user the ACPI tree and hopefully take a little mystery out of their desktop.

## Example /var/log/messages Output
```
Jan  5 17:39:45 modo kernel: Printing ACPI Namespace
Jan  5 17:39:45 modo kernel: -----------------------------------------------
Jan  5 17:39:45 modo kernel: \_SB_: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0: _HID=PNP0A08 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.IOH_: _HID=PNP0C01 _UID=10
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPE1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPE2: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPE3: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPE4: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPE5: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPE6: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPE7: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPE8: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPE9: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.NPEA: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.P0P1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.IELK: _HID=AWY0001 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.PIC_: _HID=PNP0000 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.DMAD: _HID=PNP0200 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.TMR_: _HID=PNP0100 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.RTC0: _HID=PNP0B00 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.SPKR: _HID=PNP0800 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.COPR: _HID=PNP0C04 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.UAR1: _HID=PNP0501 _UID=1
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.UAR2: _HID=PNP0501 _UID=2
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.FDC_: _HID=PNP0700 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.UAR3: _HID=PNP0501 _UID=3
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.SIO2: _HID=PNP0C02 _UID=5710
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.RMSC: _HID=PNP0C02 _UID=16
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.HPET: _HID=PNP0103 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.OMSC: _HID=PNP0C02 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.PS2K: _HID=PNP0303 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.PS2M: _HID=PNP0F03 _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.SIOR: _HID=PNP0C02 _UID=46
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.IPMI: _HID=PNP0C02 _UID=5
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SBRG.TPM_: _HID=PNP0C31 _UID=1
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.PCIE: _HID=PNP0C02 _UID=17
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SATA: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SATA.CHN0: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SATA.CHN0.DRV0: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SATA.CHN0.DRV1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SATA.CHN1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SATA.CHN1.DRV0: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SATA.CHN1.DRV1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SAT1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SAT1.CHN0: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SAT1.CHN0.DRV0: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SAT1.CHN0.DRV1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SAT1.CHN1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SAT1.CHN1.DRV0: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.SAT1.CHN1.DRV1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.USB0: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.USB1: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.USB2: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.USB5: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.EUSB: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.USB3: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.USB4: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.USB6: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.USBE: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.GBE_: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.P0P4: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.P0P5: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.P0P6: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.P0P7: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.P0P8: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.P0P9: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.PCI0.ITPM: _HID=INTC0102 _UID=1
Jan  5 17:39:45 modo kernel: \_SB_.SLPB: _HID=PNP0C0E _UID=0
Jan  5 17:39:45 modo kernel: \_SB_.RMEM: _HID=PNP0C01 _UID=1
Jan  5 17:39:45 modo kernel: \_SB_.PWRB: _HID=PNP0C0C _UID=170
Jan  5 17:39:45 modo kernel: \_SB_.LNKA: _HID=PNP0C0F _UID=1
Jan  5 17:39:45 modo kernel: \_SB_.LNKB: _HID=PNP0C0F _UID=2
Jan  5 17:39:45 modo kernel: \_SB_.LNKC: _HID=PNP0C0F _UID=3
Jan  5 17:39:45 modo kernel: \_SB_.LNKD: _HID=PNP0C0F _UID=4
Jan  5 17:39:45 modo kernel: \_SB_.LNKE: _HID=PNP0C0F _UID=5
Jan  5 17:39:45 modo kernel: \_SB_.LNKF: _HID=PNP0C0F _UID=6
Jan  5 17:39:45 modo kernel: \_SB_.LNKG: _HID=PNP0C0F _UID=7
Jan  5 17:39:45 modo kernel: \_SB_.LNKH: _HID=PNP0C0F _UID=8
Jan  5 17:39:45 modo kernel: \_TZ_: _HID=none _UID=0
Jan  5 17:39:45 modo kernel: -----------------------------------------------
```
