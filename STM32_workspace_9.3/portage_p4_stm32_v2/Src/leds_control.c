#include "leds_control.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"

#ifdef TEST_HEADER
#include TEST_HEADER
#endif

#ifndef NUMFER_OF_LEDS_PER_RING
#define NUMBER_OF_LEDS_PER_RING 24
#endif

#ifndef MAX_ROW
#define LINE_COUNT 7
#endif

#ifndef MAX_COL
#define COL_COUNT 7
#endif

#ifndef LC_OPEN
#define LC_OPEN open
#endif

#ifndef LC_WRITE
#define LC_WRITE write
#endif

#ifndef LC_CLOSE
#define LC_CLOSE close
#endif

#ifndef LC_READ
#define LC_READ read
#endif

#ifndef LC_SERIAL_PATH
#define LC_SERIAL_PATH "/tmp/puissance4/serial/ttyS1"
#endif

#define SIZE_OF_LED_COMMAND_BUFFER (10)
#define SIZE_OF_PLAYER_COMMAND_BUFFER (9)

extern UART_HandleTypeDef huart3;
extern osMessageQueueId_t queue_send_uartHandle;
extern osMessageQueueId_t queue_read_uartHandle;
//extern osMessageQueueId_t queue_read_uartHandle;

/**
 * @brief compute buffer to control led through serial link
 *
 * @param buffer Buffer to fill. Buffer must have enough memory: (4 + (nb leds per ring)*3) bytes
 * @param row Row number of led to control [1..7]
 * @param col Column number of led to control [1..7]
 * @param red Red value of RGB code
 * @param green Green value of RGB code
 * @param blue Blue value of RGB code
 */

static inline unsigned char toHexaHalfByte(const unsigned char i) {
  if (i < 9) {
    return '0' + i;
  }
  else if (i < 16) {
    return 'A' + (i - 10);
  }
  else {
    return 'X';
  }
}

static inline void encodeByte(char * const buffer, const unsigned char byte) {
  buffer[0] = toHexaHalfByte((byte >> 4) & 0x0F);
  buffer[1] = toHexaHalfByte(byte & 0x0F);
}



static void computeMessage(char * const buffer,
		const unsigned char row,
		const unsigned char col,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue) {

	buffer[0] = 'R';

	buffer[1] = toHexaHalfByte(row);
	buffer[2] = toHexaHalfByte(col);
	encodeByte(&(buffer[3]), red);
	encodeByte(&(buffer[5]), green);
	encodeByte(&(buffer[7]), blue);

	buffer[SIZE_OF_LED_COMMAND_BUFFER - 1] = '\n';
}


LedControlReturnCode setLedColor(const unsigned int row,
		const unsigned int col,
		const unsigned int red,
		const unsigned int green,
		const unsigned int blue) {
	if (row > LINE_COUNT || row == 0)
		return LCRC_ERROR_ROW;

	if (col > COL_COUNT || col == 0)
		return LCRC_ERROR_COL;

	if (red > 255 || green > 255 || blue > 255)
		return LCRC_ERROR_RGB_VALUE;

	const unsigned int finalRow = row - 1;
	const unsigned int finalCol = col - 1;
	char buffer[SIZE_OF_LED_COMMAND_BUFFER] = { 0 };
	computeMessage(buffer, finalRow, finalCol, red, green, blue);
	osMessageQueuePut(queue_send_uartHandle, buffer, 0, 10);



	return LCRC_OK;
}


char readbutton(char *pReadData, char DataSize)
{
	unsigned char buffer[SIZE_OF_PLAYER_COMMAND_BUFFER] = { 0 };

	//if(osMessageQueueGet(queue_read_uartHandle, buffer, 0, 10) == osOK)
	if (osMessageQueueGetCount(queue_read_uartHandle) > 0)
	{
		osMessageQueueGet(queue_read_uartHandle, buffer, 0, 10);
		memcpy(pReadData,buffer,SIZE_OF_PLAYER_COMMAND_BUFFER);
		return LCRC_OK;
	}
	return LCRC_ERROR_SERIAL_READ;
}



/*char readbutton(char *pReadData, char DataSize)
{

	unsigned char buffer[SIZE_OF_PLAYER_COMMAND_BUFFER] = { 0 };

	const HAL_StatusTypeDef nbOfReadBytes = HAL_UART_Receive(&huart3,(uint8_t *) pReadData, DataSize, 0xFFFF);

	if (nbOfReadBytes != SIZE_OF_PLAYER_COMMAND_BUFFER) {
		return LCRC_ERROR_SERIAL_READ;
	}

	if(nbOfReadBytes<=DataSize)
	{
		memcpy(pReadData,buffer,nbOfReadBytes);
	}
	return LCRC_OK;
}*/
