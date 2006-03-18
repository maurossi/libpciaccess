/*
 * (C) Copyright IBM Corporation 2006
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * IBM AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * \file pciaccess_private.h
 * Functions and datastructures that are private to the pciaccess library.
 * 
 * \author Ian Romanick <idr@us.ibm.com>
 */


int pci_fill_capabilities_generic( struct pci_device * dev );

struct pci_system_methods {
    void (*destroy)( void );
    void (*destroy_device)( struct pci_device * dev );
    int (*read_rom)( struct pci_device * dev, void * buffer );    
    int (*probe)( struct pci_device * dev );
    int (*map)( struct pci_device * dev, unsigned region, int write_enable );
    int (*unmap)( struct pci_device * dev, unsigned region );
    
    int (*read)(struct pci_device * dev, void * data, pciaddr_t offset,
		pciaddr_t size, pciaddr_t * bytes_read );

    int (*write)(struct pci_device * dev, const void * data, pciaddr_t offset,
		pciaddr_t size, pciaddr_t * bytes_written );

    int (*fill_capabilities)( struct pci_device * dev );
};

struct pci_device_private {
    struct pci_device  base;
    const char * device_string;
    
    /**
     * \name PCI Capabilities
     */
    /*@{*/
    const struct pci_agp_info * agp;   /**< AGP capability information. */
    /*@}*/
};


/**
 * Base type for tracking PCI subsystem information.
 */
struct pci_system {
    /**
     * Platform dependent implementations of specific API routines.
     */
    const struct pci_system_methods * methods;

    /**
     * Number of known devices in the system.
     */
    size_t num_devices;

    /**
     * Array of known devices.
     */
    struct pci_device_private * devices;
};

extern struct pci_system * pci_sys;