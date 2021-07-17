#include <stdio.h>
#include <string.h>

#include "lcd/lcd.h"
#include "model.h"
#include "utils.h"
#define PIN 13  // PC=13
void showmenu();

#define RED_LED_PORT GPIOC
#define RED_LED_PIN GPIO_PIN_13
#define MAX_Q 300
void Inp_init(void) {
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

typedef struct {
    int xpos;
    // int ypos;
    //   int p_xpos;
    //   int p_ypos;
    int color;
    int live;
} Ball;

Ball ball[MAX_Q];
int time = 0;
int ptr = 0;
int score = 0;
int not_finish = 0;
u16 lcd[23][160];
char text[20];
int h_score = 0;
void DrawCover();
void fresh();
void Adc_init(void) {
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
    RCU_CFG0 |= (0b10 << 14) | (1 << 28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0) |= ADC_CTL1_ADCON;
}

void IO_init(void) {
    Inp_init();  // inport init
    Adc_init();  // A/D init
    Lcd_Init();  // LCD init
}

void hit_red(void) {
    int hit = 0;
    for (int i = 0; i < MAX_Q; i++) {
        if (ball[i].live && ball[i].color == 0) {
            if (ball[i].xpos - 23 >= 0 && ball[i].xpos - 23 <= 10) {
                hit = 1;
                ball[i].live = 0;
                score += 100;

                sprintf(text, "%d", score);
                LCD_ShowString(50, 24, (u8 *)text, RED);
            }  // speed
        }
    }
    // LCD_Address_Set(4, 54, 26, 76);
    if (!hit) {
        for (int i = 0; i < 23; i++)
            for (int j = 0; j < 23; j++)
                // LCD_DrawPoint(0, 0, hit1[i][j]);
                lcd[i][4 + j] = hitred[i][j];
    } else {
        for (int i = 0; i < 23; i++)
            for (int j = 0; j < 23; j++)
                // LCD_DrawPoint(0, 0, hit1[i][j]);
                lcd[i][4 + j] = hit1[i][j];
    }
    //   for (int i = 0; i < 80; i++)
    //     for (int j = 0; j < 160; j++)
    //       LCD_WR_DATA(play1[i][j]);
    //   for (int i = 0; i < 80; i++)
    //     for (int j = 0; j < 160; j++)
    //       LCD_WR_DATA(cover[i][j]);
}

void hit_blue(void) {
    int hit = 0;
    for (int i = 0; i < MAX_Q; i++) {
        if (ball[i].live && ball[i].color == 1) {
            if (ball[i].xpos - 23 >= 0 && ball[i].xpos - 23 <= 10) {
                hit = 1;
                ball[i].live = 0;
                score += 100;

                sprintf(text, "%d", score);
                LCD_ShowString(50, 24, (u8 *)text, RED);
            }  // speed
        }
    }
    // LCD_Address_Set(4, 54, 26, 76);
    if (!hit) {
        for (int i = 0; i < 23; i++)
            for (int j = 0; j < 23; j++)
                // LCD_DrawPoint(0, 0, hit1[i][j]);
                lcd[i][4 + j] = hitblue[i][j];
    } else {
        for (int i = 0; i < 23; i++)
            for (int j = 0; j < 23; j++)
                // LCD_DrawPoint(0, 0, hit1[i][j]);
                lcd[i][4 + j] = hit1[i][j];
    }
    //   for (int i = 0; i < 80; i++)
    //     for (int j = 0; j < 160; j++)
    //       LCD_WR_DATA(play1[i][j]);
    //   for (int i = 0; i < 80; i++)
    //     for (int j = 0; j < 160; j++)
    //       LCD_WR_DATA(cover[i][j]);
}

void update() {
    for (int i = 0; i < MAX_Q; i++) {
        if (ball[i].live) {
            ball[i].xpos -= 4;  // speed
        }
    }
    for (int i = 0; i < 38; i++) {
        if (eva[i][0] == time) {
            ball[ptr].color = eva[i][1];
            ball[ptr].live = 1;
            ball[ptr].xpos = 160;
            ptr++;
            // ball[ptr].ypos = 54;
        }
    }
    for (int k = 299; k >= 0; k--) {
        if (ball[k].live) {
            if (ball[k].xpos <= 25) {
                ball[k].live = 0;
            } else {
                // LCD_Address_Set(ball[k].xpos - 22, 54, ball[k].xpos, 76);
                for (int i = 0; i < 23; i++)
                    for (int j = 0; j < 23; j++) {
                        // LCD_DrawPoint(0, 0, hit1[i][j]);
                        if (ball[k].color) {
                            lcd[i][ball[k].xpos + j - 23] = blue1[i][j];
                        } else {
                            lcd[i][ball[k].xpos + j - 23] = red1[i][j];
                        }
                    }
            }
        }
    }
    // if (score)
    //   LCD_ShowString(50, 24, (u8 *)text, RED);
}

void end() {
    int flag = 1;
    if (score >= h_score) h_score = score;
    LCD_Clear(BLACK);
    LCD_ShowString(0, 0, (u8 *)("YOUR SCORE:"), RED);
    LCD_ShowString(0, 16, (u8 *)text, WHITE);
    sprintf(text, "%d", h_score);
    LCD_ShowString(0, 32, (u8 *)("HIGHEST SCORE:"), GBLUE);
    LCD_ShowString(0, 48, (u8 *)text, WHITE);
    while (flag) {
        if (Get_BOOT0()) {
            flag = 0;
            DrawCover();
        }
    }
}

void get(i, j) { LCD_WR_DATA(play1[i][j]); }

void play(void) {
    LCD_Clear(BLACK);
    gpio_bit_write(GPIOC, GPIO_PIN_13, SET);
    delay_1ms(1000);
    gpio_bit_write(GPIOC, GPIO_PIN_13, RESET);
    while (not_finish) {
        for (int i = 54; i <= 76; i++)
            for (int j = 0; j < 160; j++) lcd[i - 54][j] = play1[i][j];
        update();
        if (Get_Button(0))
            hit_red();
        else if (Get_Button(1))
            hit_blue();
        LCD_Address_Set(0, 0, 159, 79);
        for (int i = 0; i < 23; i++)
            for (int j = 0; j < 160; j++) LCD_WR_DATA(play1[i][j]);
        LCD_Address_Set(0, 23, 46, 39);
        thisloop();  // this loop
        LCD_WR_DATA(play1[i][j]);
        LCD_Address_Set(0, 40, 159, 49);
        for (int i = 40; i < 50; i++)
            for (int j = 0; j < 160; j++) LCD_WR_DATA(play1[i][j]);
        LCD_ShowString(50, 24, (u8 *)text, RED);
        LCD_Address_Set(0, 50, 159, 79);
        for (int i = 50; i < 54; i++)
            for (int j = 0; j < 160; j++) LCD_WR_DATA(play1[i][j]);
        for (int i = 54; i < 77; i++)
            for (int j = 0; j < 160; j++) LCD_WR_DATA(lcd[i - 54][j]);
        for (int i = 77; i < 80; i++)
            for (int j = 0; j < 160; j++) LCD_WR_DATA(play1[i][j]);

        delay_1ms(20);
        time++;
        if (time == 622) {
            end();
        }
    }
}

int set_led_on(uint32_t gpio, int pin) {
    *(uint32_t *)(gpio + 0x14) = (1 << pin);
    return 0;
}
int set_led_off(uint32_t gpio, int pin) {
    *(uint32_t *)(gpio + 0x0c) |= (1 << pin);
    return 0;
}
// 画封面
void DrawCover() {
    LCD_Clear(BLACK);
    LCD_Address_Set(0, 0, 159, 79);
    for (int i = 0; i < 80; i++)
        for (int j = 0; j < 160; j++) LCD_WR_DATA(cover[i][j]);
    //   LCD_ShowString(10, 55, (u8 *)("L PLAY"), 0xDE1208);
    //   LCD_ShowString(50, 55, (u8 *)("R SCOREBOARD"), 0x237679);
    fresh();
    int flag = 1;
    //   while (flag) {
    //     if (Get_Button(15)) { // TODO: Fix LB and RB
    //       flag = 0;
    //       play();
    //     } else {
    //     }
    //     delay_1ms(1);
    //   }

    while (flag) {
        if (Get_Button(0)) {  // TODO: Fix LB and RB
            flag = 0;
            not_finish = 1;
            play();
        } else {
        }
        delay_1ms(1);
    }
}

void DrawScoreBoard() {}

void fresh() {
    for (int i = 0; i < MAX_Q; i++) {
        ball[i].xpos = 0;
        // ball[i].ypos = 0;
        ball[i].live = 0;
        ball[i].color = 0;
    }
    time = 0;
    ptr = 0;
    score = 0;
    not_finish = 0;
}

void start() {}

int main(void) {
    //*(uint32_t *)(GPIOC + 0x04) |= (0x1 << (PIN % 8 * 4)); // PC13 OUT
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_init(RED_LED_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, RED_LED_PIN);

    srand(get_timer_value());
    IO_init();  // init OLED
                // YOUR CODE HERE
    DrawCover();
}
