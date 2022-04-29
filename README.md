# lwIP Arduino

This port allows to use [lwIP](https://savannah.nongnu.org/projects/lwip/) with any Arduino board. The motivation of this port, is to integrate a TCP/IP stack in combination with any other Ethernet PHY-MAC. 	

## Port Information

- LwIP version: v2.1.3
- Commit: [124dc0a64ef5d7c14a27e3115e5888df6559cb72](http://git.savannah.gnu.org/cgit/lwip.git/commit/?id=124dc0a64ef5d7c14a27e3115e5888df6559cb72)

## Port specific changes

- Relative includes for source files. Arduino does not incluude an easy way to include directories in their build system.
- Integrated Arduino SDK for implemmentation, to make it compatible with any Arduino board.


## Notes

Currently the port is intended to work with bare metal systems. I.e., the [OS Layer](https://www.nongnu.org/lwip/2_0_x/group__sys__os.html) is not implemented. The reason is that Arduino does not have an OS abstraction layer.


