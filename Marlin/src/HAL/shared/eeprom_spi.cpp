/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Description: functions for SPI connected external EEPROM.
 * Not platform dependent.
 */

#include "../../inc/MarlinConfig.h"

#if ENABLED(SPI_EEPROM)

#include "../HAL.h"

#include "../../lcd/extui/lib/mks_ui/W25Qxx.h"

#define CMD_WREN  6   // WREN
#define CMD_READ  2   // WRITE
#define CMD_WRITE 2   // WRITE

uint8_t eeprom_read_byte(uint8_t* pos) {

  
  uint8_t v;
  #if 1
  //W25QXX.SPI_FLASH_SectorErase(0);
  //W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&v,(uint32_t)*pos,1);
  W25QXX.SPI_FLASH_BufferRead((uint8_t *)&v,(uint32_t)pos,1);
  return v;
  #else
  uint8_t eeprom_temp[3];

  // set read location
  // begin transmission from device
  eeprom_temp[0] = CMD_READ;
  eeprom_temp[1] = ((unsigned)pos>>8) & 0xFF; // addr High
  eeprom_temp[2] = (unsigned)pos& 0xFF;       // addr Low
  WRITE(SPI_EEPROM1_CS, HIGH);
  WRITE(SPI_EEPROM1_CS, LOW);
  spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 3);

  v = spiRec(SPI_CHAN_EEPROM1);
  WRITE(SPI_EEPROM1_CS, HIGH);
  return v;
  #endif
}

void eeprom_read_block(void* dest, const void* eeprom_address, size_t n) {
  #if 1
  W25QXX.SPI_FLASH_BufferRead((uint8_t *)dest,*((uint32_t *)eeprom_address),n);
  #else
  uint8_t eeprom_temp[3];

  // set read location
  // begin transmission from device
  eeprom_temp[0] = CMD_READ;
  eeprom_temp[1] = ((unsigned)eeprom_address>>8) & 0xFF; // addr High
  eeprom_temp[2] = (unsigned)eeprom_address& 0xFF;       // addr Low
  WRITE(SPI_EEPROM1_CS, HIGH);
  WRITE(SPI_EEPROM1_CS, LOW);
  spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 3);

  uint8_t *p_dest = (uint8_t *)dest;
  while (n--)
    *p_dest++ = spiRec(SPI_CHAN_EEPROM1);
  WRITE(SPI_EEPROM1_CS, HIGH);
  #endif
}

void eeprom_write_byte(uint8_t* pos, uint8_t value) {
  #if 1
  W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&value,(uint32_t)pos,1);
  #else
  uint8_t eeprom_temp[3];

  /*write enable*/
  eeprom_temp[0] = CMD_WREN;
  WRITE(SPI_EEPROM1_CS, LOW);
  spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 1);
  WRITE(SPI_EEPROM1_CS, HIGH);
  delay(1);

  /*write addr*/
  eeprom_temp[0] = CMD_WRITE;
  eeprom_temp[1] = ((unsigned)pos>>8) & 0xFF;  //addr High
  eeprom_temp[2] = (unsigned)pos & 0xFF;       //addr Low
  WRITE(SPI_EEPROM1_CS, LOW);
  spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 3);

  spiSend(SPI_CHAN_EEPROM1, value);
  WRITE(SPI_EEPROM1_CS, HIGH);
  delay(7);   // wait for page write to complete
  #endif
}

void eeprom_update_block(const void* src, void* eeprom_address, size_t n) {

  #if 1
  W25QXX.SPI_FLASH_BufferWrite((uint8_t *)src,*((uint32_t *)eeprom_address),n);
  #else
  uint8_t eeprom_temp[3];

  /*write enable*/
  eeprom_temp[0] = CMD_WREN;
  WRITE(SPI_EEPROM1_CS, LOW);
  spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 1);
  WRITE(SPI_EEPROM1_CS, HIGH);
  delay(1);

  /*write addr*/
  eeprom_temp[0] = CMD_WRITE;
  eeprom_temp[1] = ((unsigned)eeprom_address>>8) & 0xFF;  //addr High
  eeprom_temp[2] = (unsigned)eeprom_address & 0xFF;       //addr Low
  WRITE(SPI_EEPROM1_CS, LOW);
  spiSend(SPI_CHAN_EEPROM1, eeprom_temp, 3);

  spiSend(SPI_CHAN_EEPROM1, (const uint8_t*)src, n);
  WRITE(SPI_EEPROM1_CS, HIGH);
  delay(7);   // wait for page write to complete
  #endif
}

#endif // SPI_EEPROM
