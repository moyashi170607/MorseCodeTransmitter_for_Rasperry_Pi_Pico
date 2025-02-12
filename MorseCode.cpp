#include <stdio.h>
#include <string>
#include "pico/stdlib.h"

//モールス信号に変換・出力するクラス
#include "MorseCodeTransmitter.hpp"




int main()
{
    //LEDに接続されるピン
    const uint RED_LED_PIN = 15;
    //アクティブブザーに接続されるピン
    const uint BUZZER_PIN = 16;
    //出力する内容
    const std::string Message = "Hello, World.";

    MorseCodeTransmitter mct;

    stdio_init_all();

    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN,GPIO_OUT);
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN,GPIO_OUT);

    while (true) {
        sleep_ms(2000);
        mct.PrintMorseCode(Message,RED_LED_PIN,BUZZER_PIN);
        sleep_ms(1000);

    }
}





