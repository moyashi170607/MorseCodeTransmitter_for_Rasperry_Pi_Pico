#ifndef _MORSE_CODE_TRANSMITTER
#define _MORSE_CODE_TRANSMITTER

#include <stdio.h>
#include <string>
#include <algorithm>
#include <cctype>
#include "pico/stdlib.h"

//短音の長さ。長音や間隔の長さはこれをもとに設定される
#define CODE_UNIT 150

//文字とモールス信号の対応を表す構造体
struct CharaToMorseList
{
    char chara_code;
    char morse_code[6];
};

//モールス信号に変換・出力するクラス
class MorseCodeTransmitter
{
    private:
        //モールス信号対応表
        //1=短音 2=長音
        CharaToMorseList ctml[40] = {
            {'A',"12"},
            {'B',"2111"},
            {'C',"2121"},
            {'D',"211"},
            {'E',"1"},
            {'F',"1121"},
            {'G',"221"},
            {'H',"1111"},
            {'I',"11"},
            {'J',"1222"},
            {'K',"212"},
            {'L',"1211"},
            {'M',"22"},
            {'N',"21"},
            {'O',"222"},
            {'P',"1221"},
            {'Q',"2212"},
            {'R',"121"},
            {'S',"111"},
            {'T',"2"},
            {'U',"112"},
            {'V',"1112"},
            {'W',"122"},
            {'X',"2112"},
            {'Y',"2122"},
            {'Z',"2211"},
            {'0',"22222"},
            {'1',"12222"},
            {'2',"11222"},
            {'3',"11122"},
            {'4',"11112"},
            {'5',"11111"},
            {'6',"21111"},
            {'7',"22111"},
            {'8',"22211"},
            {'9',"22221"},
        };


        //文字をモールス信号にし、出力
        std::string CharaToMorseCode(char char_temp){
            std::string code;

            for(int i = 0; i < 40; i++){
                if(ctml[i].chara_code == char_temp){
                    code = ctml[i].morse_code;
                    return code;
                }
            }

            return "0";
        };

    public:
        //長音
        void DashCode(uint pin,uint buzzer_pin){
            gpio_put(pin,1);
            gpio_put(buzzer_pin,1);
            sleep_ms(CODE_UNIT*3);
            gpio_put(pin,0);
            gpio_put(buzzer_pin,0);
            sleep_ms(CODE_UNIT);
        };

        //短音
        void DotCode(uint pin,uint buzzer_pin){
            gpio_put(pin,1);
            gpio_put(buzzer_pin,1);
            sleep_ms(CODE_UNIT);
            gpio_put(pin,0);
            gpio_put(buzzer_pin,0);
            sleep_ms(CODE_UNIT);
        };

        //文字間の間隔
        void CharaBlankCode(uint pin){
            sleep_ms(CODE_UNIT*2);
        };

        //単語間の間隔
        void WordBlankCode(uint pin){
            sleep_ms(CODE_UNIT*6);
        };

        //文字列をモールス信号に変換,出力
        void PrintMorseCode(std::string plain_text,uint pin,uint buzzer_pin){
            std::transform(plain_text.begin(),plain_text.end(),plain_text.begin(),::toupper);


            for(int i=0; plain_text[i] != '\0'; i++){
                if(plain_text[i] == ' '){
                    WordBlankCode(pin);
                }else{
                    std::string code;
                    code = CharaToMorseCode(plain_text[i]);

                    if(code != "0"){
                        for(int l=0; l< code.length(); l++){
                            switch (code[l])
                            {
                                case '1':{
                                    DotCode(pin,buzzer_pin);
                                    break;
                                }
                                case '2':{
                                    DashCode(pin,buzzer_pin);
                                    break;
                                }
                                default:
                                    break;
                            }
                        }
                    }

                    CharaBlankCode(pin);
                }

            }
        };

        //SOSをモールス信号で出力　おまけ。
        //SOSは文字間の間隔を開けずに出力するのが正しいらしいので、それに合わせた
        void SOS_Code(uint pin, uint buzzer_pin){

            int i=0;
            for(i=0; i<3; i++){
                DotCode(pin,buzzer_pin);
            }
            for(i=0; i<3; i++){
                DashCode(pin,buzzer_pin);
            }
            for(i=0; i<3; i++){
                DotCode(pin,buzzer_pin);
            }
        };
};


#endif //_MORSE_CODE_TRANSMITTER