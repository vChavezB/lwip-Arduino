# lwIP Arduino

This port allows to integrate [lwIP](https://savannah.nongnu.org/projects/lwip/) with the Arduino platform. The motivation of this port, is to easily integrate a TCP/IP stack with any Mac-PHY chip in the Arduino platform.


## Port Information

- LwIP version: v2.1.3
- Commit: [124dc0a64ef5d7c14a27e3115e5888df6559cb72](http://git.savannah.gnu.org/cgit/lwip.git/commit/?id=124dc0a64ef5d7c14a27e3115e5888df6559cb72)

## Port specific changes

- Relative includes for source files. Arduino does not incluude an easy way to include directories in their build system.
- Integrated Arduino SDK for implementation, to make it compatible with any Arduino board.
- Changed extension of apps/http/fsdata.c to ".c_" and changed as well the macro in HTTPD_FSDATA_FILE. Arduino build system compiles .c and .cpp files by default. However, this file is intended to be only included by fs.c.

## How to Use

Refer to the examples folder to check how you could integrate lwIP with a MAC-PHY chip. It requires that the user already has implemented the low-level access to the MAC-PHY chip to send/recieve ethernet frames and update the link status.


## Notes

- Currently the port is intended to work with bare metal systems. I.e., the [OS Layer](https://www.nongnu.org/lwip/2_0_x/group__sys__os.html) is not implemented. The reason is that Arduino does not have an OS abstraction layer.
- Not compatible with ESP32 core, as ESP32 already includes lwIP and will create conflicts with the headers of this library.


