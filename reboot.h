void doReboot() {
    // send reboot command
    SCB_AIRCR = 0x05FA0004;
}
