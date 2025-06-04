#include "ssd1306.h"
#include "i2c.h"

// credit to @armlabs at https://github.com/armlabs/ssd1306_linux/tree/master

const char init_oled_type_file[] = "/tmp/.ssd1306_oled_type";
I2C i2c3(3, SSD1306_I2C_ADDR);
static uint8_t data_buf[1024];
static uint8_t max_lines = 0;
static uint8_t max_columns = 0;
static uint8_t global_x = 0;
static uint8_t global_y = 0;

uint8_t ssd1306_init()
{
    if (!i2c3.ok())
        return 1;
    // test i2c connection
    uint8_t cmd = SSD1306_COMM_CONTROL_BYTE;
    uint8_t result = 0;
    i2c3.write(&cmd, 1);
    i2c3.read(&result, 1);
    if (result == 0)
        return 1;
    return 0;
}

uint8_t ssd1306_end()
{
    return 0;
}

uint8_t ssd1306_oled_onoff(uint8_t onoff)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    if (onoff == 0)
        data_buf[1] = SSD1306_COMM_DISPLAY_OFF;
    else
        data_buf[1] = SSD1306_COMM_DISPLAY_ON;
    
    return i2c3.write(data_buf, 2);
}

uint8_t ssd1306_oled_horizontal_flip(uint8_t flip)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    if (flip == 0)
        data_buf[1] = SSD1306_COMM_HORIZ_NORM;
    else
        data_buf[1] = SSD1306_COMM_HORIZ_FLIP;
    
    return i2c3.write(data_buf, 2);
}

uint8_t ssd1306_oled_display_flip(uint8_t flip)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    if (flip == 0)
        data_buf[1] = SSD1306_COMM_DISP_NORM;
    else
        data_buf[1] = SSD1306_COMM_DISP_INVERSE;
    
    return i2c3.write(data_buf, 2);
}

// 128x32 please use value 32
// 128x64 please use value 64
uint8_t ssd1306_oled_multiplex(uint8_t row)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_MULTIPLEX;
    data_buf[2] = row - 1;
    
    return i2c3.write(data_buf, 3);
}

// offset range 0x00~0x3f
uint8_t ssd1306_oled_vert_shift(uint8_t offset)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_VERT_OFFSET;
    data_buf[2] = offset;
    
    return i2c3.write(data_buf, 3);
}

// default value for clk is 0x80
uint8_t ssd1306_oled_set_clock(uint8_t clk)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_CLK_SET;
    data_buf[2] = clk;
    
    return i2c3.write(data_buf, 3);
}

// default value for precharge is 0xf1
uint8_t ssd1306_oled_set_precharge(uint8_t precharge)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_PRECHARGE;
    data_buf[2] = precharge;
    
    return i2c3.write(data_buf, 3);
}

// default value for deselect is 0x40
uint8_t ssd1306_oled_set_deselect(uint8_t voltage)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_DESELECT_LV;
    data_buf[2] = voltage;
    
    return i2c3.write(data_buf, 3);
}

// default value for com pin is 0x02
uint8_t ssd1306_oled_set_com_pin(uint8_t value)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_COM_PIN;
    data_buf[2] = value;
    
    return i2c3.write(data_buf, 3);
}

// default value use SSD1306_PAGE_MODE
uint8_t ssd1306_oled_set_mem_mode(uint8_t mode)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_MEMORY_MODE;
    data_buf[2] = mode;
    
    return i2c3.write(data_buf, 3);
}

uint8_t ssd1306_oled_set_col(uint8_t start, uint8_t end)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_SET_COL_ADDR;
    data_buf[2] = start;
    data_buf[3] = end;
    
    return i2c3.write(data_buf, 4);
}

uint8_t ssd1306_oled_set_page(uint8_t start, uint8_t end)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_SET_PAGE_ADDR;
    data_buf[2] = start;
    data_buf[3] = end;
    
    return i2c3.write(data_buf, 4);
}

// default contrast value is 0x7f
uint8_t ssd1306_oled_set_constrast(uint8_t value)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_CONTRAST;
    data_buf[2] = value;
    
    return i2c3.write(data_buf, 3);
}

uint8_t ssd1306_oled_scroll_onoff(uint8_t onoff)
{
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    if (onoff == 0)
        data_buf[1] = SSD1306_COMM_DISABLE_SCROLL;
    else
        data_buf[1] = SSD1306_COMM_ENABLE_SCROLL;
    
    return i2c3.write(data_buf, 2);
}

uint8_t ssd1306_oled_set_X(uint8_t x)
{
    if (x >= max_columns)
        return 1;

    global_x = x;
    
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_LOW_COLUMN | (x & 0x0f);
    data_buf[2] = SSD1306_COMM_HIGH_COLUMN | ((x >> 4) & 0x0f);
    
    return i2c3.write(data_buf, 3);
}

uint8_t ssd1306_oled_set_Y(uint8_t y)
{
    if (y >= (max_lines / 8))
        return 1;

    global_y = y;
    
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_PAGE_NUMBER | (y & 0x0f);

    return i2c3.write(data_buf, 2);
}

uint8_t ssd1306_oled_set_XY(uint8_t x, uint8_t y)
{
    if (x >= max_columns || y >= (max_lines / 8))
        return 1;

    global_x = x;
    global_y = y;
    
    data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
    data_buf[1] = SSD1306_COMM_PAGE_NUMBER | (y & 0x0f);

    data_buf[2] = SSD1306_COMM_LOW_COLUMN | (x & 0x0f);
    
    data_buf[3] = SSD1306_COMM_HIGH_COLUMN | ((x >> 4) & 0x0f);
    
    return i2c3.write(data_buf, 4);
}

uint8_t ssd1306_oled_set_rotate(uint8_t degree)
{
    // only degree 0 and 180
    if (degree == 0)
    {
        data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
        data_buf[1] = SSD1306_COMM_HORIZ_FLIP;
        data_buf[2] = SSD1306_COMM_SCAN_REVS;
    
        return i2c3.write(data_buf, 3);
    }
    else if (degree == 180)
    {
        data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
        data_buf[1] = SSD1306_COMM_HORIZ_NORM;
        data_buf[2] = SSD1306_COMM_SCAN_NORM;
    
        return i2c3.write(data_buf, 3);
    }
    else
        return 1;
}

uint8_t ssd1306_oled_default_config(uint8_t oled_lines, uint8_t oled_columns)
{
    if (oled_lines != SSD1306_128_64_LINES && oled_lines != SSD1306_128_32_LINES && SSD1306_64_48_LINES)
        oled_lines = SSD1306_128_64_LINES;
        
    if (oled_columns != SSD1306_128_64_COLUMNS && oled_lines != SSD1306_128_32_COLUMNS && SSD1306_64_48_COLUMNS)
        oled_columns = SSD1306_128_64_COLUMNS;
        
    max_lines = oled_lines;
    max_columns = oled_columns;
    global_x = 0;
    global_y = 0;
    
    if (ssd1306_oled_save_resolution(max_columns, max_lines) != 0)
        return 1;
    
    uint16_t i = 0;
    data_buf[i++] = SSD1306_COMM_CONTROL_BYTE;  //command control byte
    data_buf[i++] = SSD1306_COMM_DISPLAY_OFF;   //display off
    data_buf[i++] = SSD1306_COMM_DISP_NORM;     //Set Normal Display (default)
    data_buf[i++] = SSD1306_COMM_CLK_SET;       //SETDISPLAYCLOCKDIV
    data_buf[i++] = 0x80;                       // the suggested ratio 0x80
    data_buf[i++] = SSD1306_COMM_MULTIPLEX;     //SSD1306_SETMULTIPLEX
    data_buf[i++] = oled_lines - 1;             // height is 32 or 64 (always -1)
    data_buf[i++] = SSD1306_COMM_VERT_OFFSET;   //SETDISPLAYOFFSET
    data_buf[i++] = 0;                          //no offset
    data_buf[i++] = SSD1306_COMM_START_LINE;    //SETSTARTLINE
    data_buf[i++] = SSD1306_COMM_CHARGE_PUMP;   //CHARGEPUMP
    data_buf[i++] = 0x14;                       //turn on charge pump
    data_buf[i++] = SSD1306_COMM_MEMORY_MODE;   //MEMORYMODE
    data_buf[i++] = SSD1306_PAGE_MODE;          // page mode
    data_buf[i++] = SSD1306_COMM_HORIZ_NORM;    //SEGREMAP  Mirror screen horizontally (A0)
    data_buf[i++] = SSD1306_COMM_SCAN_NORM;     //COMSCANDEC Rotate screen vertically (C0)
    data_buf[i++] = SSD1306_COMM_COM_PIN;       //HARDWARE PIN 
    if (oled_lines == 32)
        data_buf[i++] = 0x02;                       // for 32 lines
    else
        data_buf[i++] = 0x12;                       // for 64 lines or 48 lines
    data_buf[i++] = SSD1306_COMM_CONTRAST;      //SETCONTRAST
    data_buf[i++] = 0x7f;                       // default contract value
    data_buf[i++] = SSD1306_COMM_PRECHARGE;     //SETPRECHARGE
    data_buf[i++] = 0xf1;                       // default precharge value
    data_buf[i++] = SSD1306_COMM_DESELECT_LV;   //SETVCOMDETECT                
    data_buf[i++] = 0x40;                       // default deselect value
    data_buf[i++] = SSD1306_COMM_RESUME_RAM;    //DISPLAYALLON_RESUME
    data_buf[i++] = SSD1306_COMM_DISP_NORM;     //NORMALDISPLAY
    data_buf[i++] = SSD1306_COMM_DISPLAY_ON;    //DISPLAY ON             
    data_buf[i++] = SSD1306_COMM_DISABLE_SCROLL;//Stop scroll
    
    return i2c3.write(data_buf, i);
}

uint8_t ssd1306_oled_write_line(uint8_t size, char* ptr)
{
    if (ptr == NULL)
        return 1;

    uint16_t i = 0;
    uint16_t index = 0;
    uint8_t font_table_width = 0;
    const uint8_t* font_ptr = nullptr;

    data_buf[i++] = SSD1306_DATA_CONTROL_BYTE;

    while (ptr[index] != 0 && i < 1024)
    {
        char c = ptr[index];
        if ((uint8_t)c < 0x20 || (uint8_t)c > 0x7E)
            return 1;

        switch (size)
        {
        case SSD1306_FONT_SMALL:  // 5x7
            font_ptr = &font5x7[(c - 0x20) * 5];
            font_table_width = 5;
            break;

        case SSD1306_FONT_NORMAL:  // 8x8
            font_ptr = &font8x8[(c - 0x20) * 8];
            font_table_width = 8;
            break;

        default:
            return 1;
        }

        // Prevent overflow
        if (i + font_table_width >= 1024)
            return 1;

        for (uint8_t j = 0; j < font_table_width; ++j)
        {
            data_buf[i++] = font_ptr[j];
        }

        // Add spacing for small fonts
        if (size == SSD1306_FONT_SMALL)
        {
            if (i >= 1024)
                return 1;
            data_buf[i++] = 0x00;
        }

        index++;
    }
    
    return i2c3.write(data_buf, i);
}

uint8_t ssd1306_oled_write_string(uint8_t size, char* ptr)
{
    uint8_t rc = 0;
    
    if (ptr == 0)
        return 1;
    
    char* line = 0;
    char* cr = 0;
    char buf[20];
    
    line = ptr;
    do {
        memset(buf, 0, 20);
        cr = strstr(line, "\\n");
        if (cr != NULL)
        {
            strncpy(buf, line, cr - line);
        }
        else
        {
            strcpy(buf, line);
        }
        
        // set cursor position
        ssd1306_oled_set_XY(global_x, global_y);
        rc += ssd1306_oled_write_line(size, buf);
        
        if (cr != NULL)
        {
            line = &cr[2];
            global_x = 0;
            global_y++;
            if (global_y >= (max_lines / 8))
                global_y = 0;
        }
        else
            line = NULL;
                
    }while (line != NULL);
    
    return rc;
}

uint8_t ssd1306_oled_clear_line(uint8_t row)
{
    uint8_t i;
    if (row >= (max_lines / 8))
        return 1;
        
    ssd1306_oled_set_XY(0, row);
    data_buf[0] = SSD1306_DATA_CONTROL_BYTE;
    for (i = 0; i < max_columns; i++)
        data_buf[i+1] = 0x00;
        
    return i2c3.write(data_buf, 1 + max_columns);
}

uint8_t ssd1306_oled_clear_screen()
{
    uint8_t rc = 0;
    uint8_t i;
    
    for (i = 0; i < (max_lines / 8); i++)
    {
        rc += ssd1306_oled_clear_line(i);
    }
    
    return rc;
}

uint8_t ssd1306_oled_save_resolution(uint8_t column, uint8_t row)
{
    FILE* fp;
    
    fp = fopen(init_oled_type_file, "w");
    
    if (fp == NULL)
    {
        // file create failed
        return 1;
    }
    
    fprintf(fp, "%hhux%hhu", column, row);
    fclose(fp);
    
    return 0;
}

uint8_t ssd1306_oled_load_resolution()
{
    FILE* fp;
    
    fp = fopen(init_oled_type_file, "r");
    
    if (fp == NULL)
    {
        // file not exists
        return 1;
    }
    
    // file exists
    fscanf(fp, "%hhux%hhu", &max_columns, &max_lines);
    fclose(fp);
    
    return 0;
}
