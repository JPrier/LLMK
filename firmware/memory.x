MEMORY
{
  FLASH : ORIGIN = 0x08000000, LENGTH = 1024K
  RAM : ORIGIN = 0x24000000, LENGTH = 320K
}

_stack_start = ORIGIN(RAM) + LENGTH(RAM);
