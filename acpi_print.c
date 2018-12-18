  /*-
 * Copyright (c) 2018 Austin Shafer <print@badlandsoftware.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * A kernel module to test reading ACPI information and exposing it
 * in the form of various sysctls
 *
 */

#include <sys/cdefs.h>

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/bus.h>
#include <sys/sbuf.h>
#include <sys/sysctl.h>

#include <contrib/dev/acpica/include/acpi.h>
#include <contrib/dev/acpica/include/accommon.h>
#include <dev/acpica/acpivar.h>

/*
 * Callback for printing ACPI object name
 * and Plug-n-Play numbers
 *
 * Called by AcpiWalkNamespace
 */
static ACPI_STATUS
acpi_print_name (ACPI_HANDLE handle, UINT32 level __unused,
		 void *context, void **retp __unused)
{
	ACPI_DEVICE_INFO *devinfo;	

	if (ACPI_FAILURE(AcpiGetObjectInfo(handle, &devinfo)))
		return AE_ERROR;

	printf("%s: ", acpi_name(handle));

	printf("_HID=%s _UID=%lu\n", (devinfo->Valid & ACPI_VALID_HID) ?
		 devinfo->HardwareId.String : "none",
		 (devinfo->Valid & ACPI_VALID_UID) ?
		 strtoul(devinfo->UniqueId.String, NULL, 10) : 0UL);

	AcpiOsFree(devinfo);
	return AE_OK;
}

/*
 * Walk and print the namespace but don't attach to anything
 * since this module is only for debugging
 */
static int
acpi_print_probe (device_t dev)
{
	ACPI_STATUS status;

	printf("Printing ACPI Namespace\n");
	printf("-----------------------------------------------\n");
	
	status = AcpiWalkNamespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT, 30,
				   acpi_print_name, NULL, NULL, NULL);
	if (ACPI_FAILURE(status)) {
		printf("Could not print the ACPI namespace: %s\n", AcpiFormatException(status));
		return ENXIO;
	}
	printf("-----------------------------------------------\n");
	return 0;
}
/*
 * Below are our structures and driver declarations
 */
static device_method_t acpi_print_methods[] = {
	DEVMETHOD(device_probe, acpi_print_probe),
	DEVMETHOD_END
};

static driver_t acpi_print_driver = {
	"acpi_print",
	acpi_print_methods,
	0
};

/* we depend on acpi for obvious reasons */
static devclass_t acpi_print_devclass;

DRIVER_MODULE(acpi_print, acpi, acpi_print_driver, acpi_print_devclass, 0, 0);
