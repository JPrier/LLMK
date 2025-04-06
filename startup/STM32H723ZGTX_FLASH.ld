/* Linker script placeholder for STM32H723ZGTX */

MEMORY
{
  FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = 1024K
  RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 564K
}

SECTIONS
{
  .text :
  {
    *(.text)
  } > FLASH

  .data :
  {
    *(.data)
  } > RAM AT > FLASH

  .bss :
  {
    *(.bss)
  } > RAM
}
