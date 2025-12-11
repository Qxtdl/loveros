.global load_gdt
load_gdt:
    mov 4(%esp), %edi
    lgdt (%edi)
    ljmp $0x08, $flush

flush:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ret
