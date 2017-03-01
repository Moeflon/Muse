/**
 * @file dwenguinoLCD.h
 * @author Tom Neutens
 * @date 11/01/2017
 * @brief This file contains function declarations which allow you to communicate with the lcd screen on the Dwenguino board
 *
 * Before you can use the lcd you should call the initLCD() function. 
 * Afterwards you can either append or print characters or integers to the screen.
 * For more information on the dwenguino board visit:
 * @see http://www.dwengo.org/learn 
 */

#ifndef DWENGUINO_LCD_H_
#define DWENGUINO_LCD_H_


#include "dwenguinoBoard.h"
#include <avr/delay.h>

//	Properties
#define LCD_WIDTH		16
#define LCD_HEIGHT		2
#define LCD_LASTLINE	(LCD_HEIGHT - 1)
#define LCD_LASTPOS		(LCD_WIDTH - 1)

//	Macro's
#define backlightOn()	(LCD_BACKLIGHT_ON)
#define backlightOff()	(LCD_BACKLIGHT_OFF)

#define appendStringToLCD(message)	appendStringToLCD_((const char*)(message))


/**
 * @brief initializes the LCD screen
 * This function sets up the lcd for displaying the data we will send
 */
void initLCD(void);

/**
 * @brief clears the LCD screen
 * This function removes all the content from the LCD screen
 */
void clearLCD(void);

/**
 * @brief sends a command to the LCD
 * This function sends a low level command to the LCD. 
 * The command is represented as a byte and is transferred to the LCD screen through the PORTA register.
 * @param c command to be transfered to the LCD
 */
void commandLCD(const BYTE c);

/**
 * @brief Move the cursor on the screen
 * Sets the cursor to a specified line on a certain position.
 * @param l line number
 * @param p position in line
 */
void setCursorLCD(BYTE l, BYTE p);

/**
 * @brief Append a character to the LCD
 * Adds a character at the current cursor positon then moves the cursor to the next position
 * @param c the character to append	
 */
void appendCharToLCD(const char c);

/**
 * @brief Print character to LCD
 * Prints a character to a specified position.
 * @param s the character to print
 * @param l the line 
 * @param p the position in the line
 */
void printCharToLCD(const char s, BYTE l, BYTE p);

/**
 * @brief Append an integer to the lcd screen
 * Prints the integer at the current cursor position and moves the cursor to the position afther the printed integer.
 * @param i the integer to print
 */
void appendIntToLCD(int i);

/**
 * @brief Prints an integer to the LCD screen
 * Prints an integer to a specified line and position on the screen.
 * @param i the integer to print
 * @param l the line
 * @param p the position in the line
 */
void printIntToLCD(int i, BYTE l, BYTE p);


/**
 * @brief Stores the current line and position of the cursor
 */
struct lcd_info_type{
	unsigned char line; /**< line number lcd_info_type#a. */
	unsigned char pos; /**< position in the line lcd_info_type#b. */
};

//	Keeps track of current line number and character position.
extern struct lcd_info_type lcd_info;

#endif /* DWENGUINO_LCD_H_ */
