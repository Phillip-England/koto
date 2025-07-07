

void kbg_hex(unsigned char c) {
    printf("HEX: 0x%02X\n", c);
}

void kbg_bin(unsigned char c) {
    printf("BIN: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (c >> i) & 1);
    }
    printf("\n");
}

void kbg_char(unsigned char c) {
    if (c == 0x00) {
        printf("CHAR: NULL TERMINATOR\n");
        return;
    }
    printf("CHAR: %c\n", c);
}
