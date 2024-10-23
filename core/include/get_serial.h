#ifndef GET_SERIAL_H_
#define GET_SERIAL_H_

/* Contains unique serial number string (NUL terminated) after call to init_usb_serial */
extern char usb_serial[];

/* Fills unique_serial with the flash unique id */
extern void usb_serial_init(void);

#endif