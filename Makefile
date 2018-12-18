# $FreeBSD: head/sys/modules/acpi/acpi_ashafer/Makefile 314651 2017-03-04 10:10:17Z ashafer $

KMOD=   acpi_print
SRCS = \
	acpi_print.c \
	acpi_if.h \
	device_if.h \
	bus_if.h \
	opt_acpi.h

.include <bsd.kmod.mk>
