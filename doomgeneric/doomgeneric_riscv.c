#include "doomgeneric.h"
#include "doomkeys_pref.h"
#include "system.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#define KEYQUEUE_SIZE 16

static struct
{
    uint8_t key;
    uint8_t pressed;

} key_queue[KEYQUEUE_SIZE] = {0};

static unsigned int kq_r_index = 0;
static unsigned int kq_w_index = 0;

#define PRESSED_KEYS_SIZE 10
static int pressed_keys[PRESSED_KEYS_SIZE] = {0};

static unsigned char convert_to_doom_key(int key)
{
    // switch (key)
    // {
    // case KEY_ENTER:
    //     key = DOOM_KEY_ENTER;
    //     break;
    // case KEY_ESCAPE:
    //     key = DOOM_KEY_ESCAPE;
    //     break;
    // case KEY_LEFT:
    //     key = DOOM_KEY_LEFTARROW;
    //     break;
    // case KEY_RIGHT:
    //     key = DOOM_KEY_RIGHTARROW;
    //     break;
    // case KEY_UP:
    //     key = DOOM_KEY_UPARROW;
    //     break;
    // case KEY_DOWN:
    //     key = DOOM_KEY_DOWNARROW;
    //     break;
    // case KEY_LEFT_CONTROL:
    // case KEY_RIGHT_CONTROL:
    //     key = DOOM_KEY_FIRE;
    //     break;
    // case KEY_SPACE:
    //     key = DOOM_KEY_USE;
    //     break;
    // case KEY_LEFT_SHIFT:
    // case KEY_RIGHT_SHIFT:
    //     key = DOOM_KEY_RSHIFT;
    //     break;
    // case KEY_LEFT_ALT:
    // case KEY_RIGHT_ALT:
    //     key = DOOM_KEY_LALT;
    //     break;
    // case KEY_F2:
    //     key = DOOM_KEY_F2;
    //     break;
    // case KEY_F3:
    //     key = DOOM_KEY_F3;
    //     break;
    // case KEY_F4:
    //     key = DOOM_KEY_F4;
    //     break;
    // case KEY_F5:
    //     key = DOOM_KEY_F5;
    //     break;
    // case KEY_F6:
    //     key = DOOM_KEY_F6;
    //     break;
    // case KEY_F7:
    //     key = DOOM_KEY_F7;
    //     break;
    // case KEY_F8:
    //     key = DOOM_KEY_F8;
    //     break;
    // case KEY_F9:
    //     key = DOOM_KEY_F9;
    //     break;
    // case KEY_F10:
    //     key = DOOM_KEY_F10;
    //     break;
    // case KEY_F11:
    //     key = DOOM_KEY_F11;
    //     break;
    // case KEY_EQUAL:
    //     key = DOOM_KEY_EQUALS;
    //     break;
    // case KEY_MINUS:
    //     key = DOOM_KEY_MINUS;
    //     break;
    // default:
    //     key = tolower(key);
    //     break;
    // }

    // return key;

    return 0;
}


static void handle_key_input(void)
{
    // for (;;)
    // {
    //     int key = GetKeyPressed();
    //     if (key)
    //     {
    //         for (int i = 0; i < PRESSED_KEYS_SIZE; i++)
    //         {
    //             if (!pressed_keys[i])
    //             {
    //                 pressed_keys[i] = key;
    //                 key_queue[kq_w_index].key = convert_to_doom_key(key); 
    //                 key_queue[kq_w_index].pressed = 1;
    //                 kq_w_index++;
    //                 kq_w_index %= KEYQUEUE_SIZE;
    //                 break;
    //             }
    //         }
    //     }
    //     else
    //     {
    //         break;
    //     }
    // }

    // for (int i = 0; i < PRESSED_KEYS_SIZE; i++)
    // {
    //     int key = pressed_keys[i];
    //     if (key)
    //     {
    //         if (IsKeyReleased(key))
    //         {
    //             pressed_keys[i] = 0;
    //             key_queue[kq_w_index].key = convert_to_doom_key(key); 
    //             key_queue[kq_w_index].pressed = 0;
    //             kq_w_index++;
    //             kq_w_index %= KEYQUEUE_SIZE;
    //         }
    //     }
    // }
}


void DG_Init(void)
{

}


void DG_DrawFrame(void)
{
    // DG_ScreenBuffer
    DISP_FLUSH();
}


void DG_SleepMs(uint32_t ms)
{

}


uint32_t DG_GetTicksMs()
{
    ((volatile uint8_t*)(RTC_FLAG_ADDR))[0] = 1;
    uint32_t ms = ((uint32_t*)(RTC_DATA_ADDR))[0];

    return ms;
}


int DG_GetKey(int *pressed, unsigned char *doomKey)
{
    // if (kq_r_index != kq_w_index)
    // {
    //     *doomKey = key_queue[kq_r_index].key;
    //     *pressed = key_queue[kq_r_index].pressed;
    //     kq_r_index++;
    //     kq_r_index %= KEYQUEUE_SIZE;
    //     return 1;
    // }

    return 0;
}


void DG_SetWindowTitle(const char *title)
{

}


int main(int argc, char **argv)
{
    doomgeneric_Create(argc, argv);

    for (;;)
    {
        doomgeneric_Tick();
    }

    return 0;
}